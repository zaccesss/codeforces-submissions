// Runs on:
//   codeforces.com/contest/{id}/my      — post-submit redirect, live verdict table
//   codeforces.com/contest/{id}/submission/{submId} — individual submission view

// In-memory dedupe for this page session. Persistent dedupe lives in
// chrome.storage.local (background.js). This prevents duplicate messages when
// both the initial row scan and the MutationObserver fire for the same row.
const pushed = new Set();

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

// credentials:'include' sends CF session cookies so the fetched page shows
// the actual source code (CF hides code on submission pages when logged out)
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
  chrome.runtime.sendMessage(
    { action: 'push', contestId, index, name, lang, submId, code },
    // Remove from Set on failure so a page reload can retry
    (res) => { if (!res?.ok) pushed.delete(key); }
  );
};

// ── /contest/{id}/my  — submission list ──────────────────────────────────────

const contestId = location.pathname.match(/\/contest\/(\d+)/)?.[1];

const processRow = async (row) => {
  if (!row.querySelector('.verdict-accepted, [class*="verdict-format-accepted"]')) return;

  const submLink = row.querySelector('td:first-child a[href*="/submission/"]');
  const submId   = subIdFromHref(submLink?.href);
  if (!submId) return;

  const probLink = row.querySelector('td a[href*="/problem/"]');
  const index    = probLink?.href?.match(/\/problem\/([A-Z0-9]+)/i)?.[1];
  const name     = probLink?.textContent?.trim();
  if (!index || !name) return;

  const langCell = row.querySelector('.source-code-cell, td:nth-child(5)');
  const lang     = langCell?.textContent?.trim() || 'C++';

  // The /my list view never shows the actual code — only the submission detail
  // page does. We fetch it here (same-origin, cookies auto-included).
  const doc  = await fetchCFPage(`https://codeforces.com/contest/${contestId}/submission/${submId}`);
  const code = doc && readCode(doc);
  if (!code) return;

  push({ contestId, index, name, lang, submId, code });
};

if (contestId && /\/my(\?|$)/.test(location.pathname + location.search)) {
  // Handle already-accepted rows visible on page load (refresh / revisit)
  document.querySelectorAll('table tr').forEach(processRow);

  // CF updates verdict cells by mutating existing text nodes, not by replacing
  // DOM elements, so we need characterData:true to catch those in-place changes
  new MutationObserver((mutations) => {
    for (const m of mutations) {
      for (const node of [...m.addedNodes]) {
        if (node.nodeType !== 1) continue;
        const rows = node.tagName === 'TR' ? [node] : [...node.querySelectorAll('tr')];
        rows.forEach(processRow);
      }
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
  if (document.querySelector('.verdict-accepted, [class*="verdict-format-accepted"]')) {
    const code     = readCode(document);
    const lang     = document.querySelector('.lang, .source-code-cell')?.textContent?.trim() || 'C++';
    const probLink = document.querySelector('a[href*="/problem/"]');
    const index    = probLink?.href?.match(/\/problem\/([A-Z0-9]+)/i)?.[1];
    const name     = probLink?.textContent?.trim();

    if (code && index && name) push({ contestId, index, name, lang, submId, code });
  }
}
