// Runs on:
//   codeforces.com/contest/{id}/my      — post-submit redirect, live verdict table
//   codeforces.com/contest/{id}/submission/{submId} — individual submission view

const pushed = new Set(); // dedupe within a page session

// ── helpers ──────────────────────────────────────────────────────────────────

const subIdFromHref = (href) => href?.match(/\/submission\/(\d+)/)?.[1];

const readCode = (root) => {
  for (const sel of ['pre#program-source-text', 'pre.prettyprint', '.source pre']) {
    const el = root.querySelector(sel);
    const text = el && (el.innerText || el.textContent);
    if (text?.trim()) return text;
  }
  return null;
};

// Fetch a CF page (same-origin, session cookies included automatically)
const fetchCFPage = async (url) => {
  const res = await fetch(url, { credentials: 'include' });
  if (!res.ok) return null;
  const html = await res.text();
  return new DOMParser().parseFromString(html, 'text/html');
};

const push = ({ contestId, index, name, lang, submId, code }) => {
  const key = `${contestId}-${index}`;
  if (pushed.has(key)) return;
  pushed.add(key);
  chrome.runtime.sendMessage({ action: 'push', contestId, index, name, lang, submId, code },
    (res) => { if (!res?.ok) pushed.delete(key); }
  );
};

// ── /contest/{id}/my  — submission list ──────────────────────────────────────

const contestId = location.pathname.match(/\/contest\/(\d+)/)?.[1];

const processRow = async (row) => {
  // Only act on accepted rows
  if (!row.querySelector('.verdict-accepted, [class*="verdict-format-accepted"]')) return;

  const submLink = row.querySelector('td:first-child a[href*="/submission/"]');
  const submId   = subIdFromHref(submLink?.href);
  if (!submId) return;

  // Problem cell: link href ends in /problem/INDEX  or  text like "300A"
  const probLink = row.querySelector('td a[href*="/problem/"]');
  const index    = probLink?.href?.match(/\/problem\/([A-Z0-9]+)/i)?.[1];
  const name     = probLink?.textContent?.trim();
  if (!index || !name) return;

  const langCell = row.querySelector('.source-code-cell, td:nth-child(5)');
  const lang     = langCell?.textContent?.trim() || 'C++';

  // Fetch the submission page to get the actual code
  const doc  = await fetchCFPage(`https://codeforces.com/contest/${contestId}/submission/${submId}`);
  const code = doc && readCode(doc);
  if (!code) return;

  push({ contestId, index, name, lang, submId, code });
};

if (contestId && /\/my(\?|$)/.test(location.pathname + location.search)) {
  // Process any rows already on the page (refresh / revisit)
  document.querySelectorAll('table tr').forEach(processRow);

  // Watch for verdict cells being updated by CF's live polling
  new MutationObserver((mutations) => {
    for (const m of mutations) {
      for (const node of [...m.addedNodes]) {
        if (node.nodeType !== 1) continue;
        const rows = node.tagName === 'TR' ? [node] : [...node.querySelectorAll('tr')];
        rows.forEach(processRow);
      }
      // Handle CF updating an existing cell's text in place
      if (m.target?.closest?.('td.verdict-accepted, [class*="verdict-format-accepted"]')) {
        const row = m.target.closest('tr');
        if (row) processRow(row);
      }
    }
  }).observe(document.body, { childList: true, subtree: true, characterData: true });
}

// ── /contest/{id}/submission/{submId}  — direct view ─────────────────────────

const submId = location.pathname.match(/\/submission\/(\d+)/)?.[1];

if (contestId && submId && !location.pathname.endsWith('/my')) {
  // Only act if verdict is Accepted
  if (document.querySelector('.verdict-accepted, [class*="verdict-format-accepted"]')) {
    const code = readCode(document);
    const lang = document.querySelector('.lang, .source-code-cell')?.textContent?.trim() || 'C++';

    // Problem info from breadcrumb or title
    const probLink = document.querySelector('a[href*="/problem/"]');
    const index    = probLink?.href?.match(/\/problem\/([A-Z0-9]+)/i)?.[1];
    const name     = probLink?.textContent?.trim();

    if (code && index && name) push({ contestId, index, name, lang, submId, code });
  }
}
