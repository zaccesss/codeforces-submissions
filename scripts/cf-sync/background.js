const CF_API = 'https://codeforces.com/api';
const GH_API = 'https://api.github.com';
const META_TTL = 86_400_000; // 24 h

// ── CF problem metadata (rating lookup) ──────────────────────────────────────

let _meta = null;
let _metaAt = 0;

// Fetches the full CF problemset once and caches it for 24 h.
// problemset.problems returns ~10 k problems in one shot and is CDN-cached on
// CF's end, so it's cheap. We use it to map contestId+index → rating so
// solutions land in the correct practice/<rating>/ folder.
const getCFMeta = async () => {
  if (_meta && Date.now() - _metaAt < META_TTL) return _meta;
  try {
    const res  = await fetch(`${CF_API}/problemset.problems`);
    const data = await res.json();
    if (data.status !== 'OK') return _meta; // keep stale cache on API error
    const map = {};
    for (const p of data.result.problems) map[`${p.contestId}-${p.index}`] = p.rating ?? null;
    _meta   = map;
    _metaAt = Date.now();
  } catch { /* network failure — keep stale cache */ }
  return _meta;
};

// ── helpers ───────────────────────────────────────────────────────────────────

const langExt = (lang) => {
  if (lang.includes('C++'))        return 'cpp';
  if (lang.includes('Python'))     return 'py';
  if (lang.includes('Java'))       return 'java';
  if (lang.includes('JavaScript')) return 'js';
  if (/\bC\b/.test(lang))          return 'c';
  if (lang.includes('Rust'))       return 'rs';
  return 'txt';
};

const langLabel = (lang) => {
  if (lang.includes('C++'))    return 'C++';
  if (lang.includes('Python')) return 'Python';
  if (lang.includes('Java'))   return 'Java';
  return lang.split(' ')[0];
};

const slugify = (name) =>
  name.toLowerCase().replace(/[^a-z0-9]+/g, '-').replace(/(^-|-$)/g, '');

// ── GitHub push ───────────────────────────────────────────────────────────────

const ghHeaders = (token) => ({
  Authorization: `token ${token}`,
  Accept: 'application/vnd.github+json',
  'Content-Type': 'application/json',
});

const pushToGitHub = async (token, repo, filePath, content, message) => {
  const url = `${GH_API}/repos/${repo}/contents/${filePath}`;

  // GitHub's Contents API requires the current file SHA when updating an
  // existing file — omitting it returns 409 Conflict. New files don't need it.
  let sha;
  try {
    const check = await fetch(url, { headers: ghHeaders(token) });
    if (check.ok) sha = (await check.json()).sha;
  } catch { /* file doesn't exist yet, sha stays undefined */ }

  const res = await fetch(url, {
    method: 'PUT',
    headers: ghHeaders(token),
    body: JSON.stringify({
      message,
      // encodeURIComponent → unescape converts UTF-8 to binary string so btoa
      // can base64-encode it without choking on non-ASCII chars in problem names
      content: btoa(unescape(encodeURIComponent(content))),
      ...(sha && { sha }),
    }),
  });
  return res.ok;
};

// ── message handler ───────────────────────────────────────────────────────────

const handlePush = async ({ contestId, index, name, lang, submId, code }) => {
  const cfg = await chrome.storage.sync.get(['githubToken', 'githubRepo']);
  if (!cfg.githubToken || !cfg.githubRepo) return { ok: false, error: 'not configured' };

  const { synced = {} } = await chrome.storage.local.get('synced');
  const key = `${contestId}-${index}`;
  // Store submId per problem so if the user solves it again with a better
  // solution, the new submId won't match and we push the updated code.
  if (synced[key] === submId) return { ok: true, skipped: true };

  const meta   = await getCFMeta();
  // Some CF problems have no rating (null) — 'unrated' keeps them together
  const rating = meta?.[`${contestId}-${index}`] ?? 'unrated';
  const ext    = langExt(lang);
  const label  = langLabel(lang);
  const slug   = `${contestId}${index}-${slugify(name)}`;
  const path   = `practice/${rating}/${slug}.${ext}`;
  const msg    = `[Codeforces] Practice ${rating} - ${name} - ${label}`;

  const ok = await pushToGitHub(cfg.githubToken, cfg.githubRepo, path, code, msg);
  if (ok) {
    synced[key] = submId;
    await chrome.storage.local.set({ synced });
    console.log(`[cf-sync] pushed ${path}`);
  }
  return { ok };
};

// ── lifecycle ─────────────────────────────────────────────────────────────────

chrome.runtime.onMessage.addListener((msg, _, respond) => {
  if (msg.action === 'push') {
    handlePush(msg).then(respond);
    return true; // must return true to keep the message channel open for async respond
  }
  if (msg.action === 'clearSynced') {
    chrome.storage.local.remove('synced').then(() => respond({ ok: true }));
    return true;
  }
  if (msg.action === 'sync') {
    respond({ ok: true, note: 'content-script mode — submit on CF to trigger sync' });
  }
});

// Pre-warm the CF metadata cache on startup so the first push after install
// doesn't have to wait for a ~10 k problem fetch before writing to GitHub
chrome.runtime.onInstalled.addListener(() => getCFMeta());
chrome.runtime.onStartup.addListener(() => getCFMeta());
