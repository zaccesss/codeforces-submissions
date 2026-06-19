const CF_API = 'https://codeforces.com/api';
const GH_API = 'https://api.github.com';
const SYNC_INTERVAL_MINUTES = 1;
const PROBLEMS_CACHE_TTL_MS = 86_400_000; // 24 h

// ---------- helpers ----------------------------------------------------------

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
  if (lang.includes('C++'))        return 'C++';
  if (lang.includes('Python'))     return 'Python';
  if (lang.includes('Java'))       return 'Java';
  if (lang.includes('JavaScript')) return 'JavaScript';
  return lang.split(' ')[0];
};

const slugify = (name) =>
  name.toLowerCase().replace(/[^a-z0-9]+/g, '-').replace(/(^-|-$)/g, '');

// ---------- CF problem metadata (rating) -------------------------------------

let _cfMeta = null;
let _cfMetaTime = 0;

const getCFMeta = async () => {
  if (_cfMeta && Date.now() - _cfMetaTime < PROBLEMS_CACHE_TTL_MS) return _cfMeta;
  const res = await fetch(`${CF_API}/problemset.problems`);
  const { status, result } = await res.json();
  if (status !== 'OK') return null;
  const map = {};
  for (const p of result.problems) {
    map[`${p.contestId}-${p.index}`] = p.rating ?? null;
  }
  _cfMeta = map;
  _cfMetaTime = Date.now();
  return map;
};

// ---------- code extraction via hidden tab + scripting -----------------------

function extractCodeFromPage() {
  const selectors = [
    'pre#program-source-text',
    'pre.prettyprint',
    '.source pre',
    '#program-source-text',
  ];
  for (const sel of selectors) {
    const el = document.querySelector(sel);
    const text = el && (el.innerText || el.textContent);
    if (text && text.trim().length > 10) return text;
  }
  return null;
}

const fetchSubmissionCode = (contestId, submId) =>
  new Promise((resolve) => {
    const url = `https://codeforces.com/contest/${contestId}/submission/${submId}`;

    chrome.tabs.create({ url, active: false, pinned: true, index: 0 }, (tab) => {
      if (!tab) { resolve(null); return; }
      const tabId = tab.id;
      let done = false;

      const finish = (code) => {
        if (done) return;
        done = true;
        chrome.tabs.onUpdated.removeListener(onUpdated);
        chrome.tabs.remove(tabId).catch(() => {});
        resolve(code);
      };

      const onUpdated = async (id, info) => {
        if (id !== tabId || info.status !== 'complete') return;
        try {
          const [{ result }] = await chrome.scripting.executeScript({
            target: { tabId },
            func: extractCodeFromPage,
          });
          finish(result ?? null);
        } catch {
          finish(null);
        }
      };

      chrome.tabs.onUpdated.addListener(onUpdated);
      setTimeout(() => finish(null), 12_000);
    });
  });

// ---------- GitHub push ------------------------------------------------------

const ghHeaders = (token) => ({
  Authorization: `token ${token}`,
  Accept: 'application/vnd.github+json',
  'Content-Type': 'application/json',
});

const pushFile = async (token, repo, filePath, content, message) => {
  const url = `${GH_API}/repos/${repo}/contents/${filePath}`;
  let sha;
  try {
    const check = await fetch(url, { headers: ghHeaders(token) });
    if (check.ok) sha = (await check.json()).sha;
  } catch { /* file doesn't exist yet */ }

  const body = {
    message,
    content: btoa(unescape(encodeURIComponent(content))),
    ...(sha && { sha }),
  };

  const res = await fetch(url, { method: 'PUT', headers: ghHeaders(token), body: JSON.stringify(body) });
  return res.ok;
};

// ---------- main sync --------------------------------------------------------

const sync = async () => {
  const { cfHandle, githubToken, githubRepo } = await chrome.storage.sync.get([
    'cfHandle', 'githubToken', 'githubRepo',
  ]);
  if (!cfHandle || !githubToken || !githubRepo) return;

  let submissions;
  try {
    const res = await fetch(`${CF_API}/user.status?handle=${cfHandle}&from=1&count=50`);
    const { status, result } = await res.json();
    if (status !== 'OK') return;
    submissions = result.filter(s => s.verdict === 'OK');
  } catch (e) {
    console.warn('[cf-sync] CF API error:', e.message);
    return;
  }

  // Deduplicate: keep only the latest accepted submission per problem
  const latestPerProblem = new Map();
  for (const sub of submissions) {
    const key = `${sub.contestId}-${sub.problem.index}`;
    if (!latestPerProblem.has(key)) latestPerProblem.set(key, sub);
  }

  const { synced = {} } = await chrome.storage.local.get('synced');
  const meta = await getCFMeta();
  let changed = false;

  for (const [problemKey, sub] of latestPerProblem) {
    // Skip if we already pushed this exact submission
    if (synced[problemKey] === sub.id) continue;

    const { contestId, problem: { index, name }, programmingLanguage: lang, id: submId } = sub;
    const ext   = langExt(lang);
    const label = langLabel(lang);
    const rating = meta?.[`${contestId}-${index}`] ?? 'unrated';
    const slug   = `${contestId}${index}-${slugify(name)}`;
    const path   = `practice/${rating}/${slug}.${ext}`;
    const msg    = `[Codeforces] Practice ${rating} - ${name} - ${label}`;

    console.log(`[cf-sync] Fetching code for ${slug} (submission ${submId})...`);
    const code = await fetchSubmissionCode(contestId, submId);
    if (!code) {
      console.warn(`[cf-sync] Could not get code for ${slug} — are you logged in to Codeforces?`);
      continue;
    }

    const ok = await pushFile(githubToken, githubRepo, path, code, msg);
    if (ok) {
      synced[problemKey] = submId;
      changed = true;
      console.log(`[cf-sync] ✅ Pushed ${path}`);
    } else {
      console.warn(`[cf-sync] ❌ GitHub push failed for ${path}`);
    }
  }

  if (changed) await chrome.storage.local.set({ synced });
};

// ---------- lifecycle --------------------------------------------------------

const setupAlarm = () =>
  chrome.alarms.create('cfSync', { periodInMinutes: SYNC_INTERVAL_MINUTES });

chrome.alarms.onAlarm.addListener(({ name }) => { if (name === 'cfSync') sync(); });
chrome.runtime.onInstalled.addListener(() => { setupAlarm(); sync(); });
chrome.runtime.onStartup.addListener(() => { setupAlarm(); sync(); });

chrome.storage.onChanged.addListener((changes, area) => {
  if (area === 'sync' && (changes.cfHandle || changes.githubToken || changes.githubRepo)) {
    sync();
  }
});

chrome.runtime.onMessage.addListener((msg, _, respond) => {
  if (msg.action === 'sync') {
    sync().then(() => respond({ ok: true })).catch(e => respond({ ok: false, error: e.message }));
    return true;
  }
  if (msg.action === 'clearSynced') {
    chrome.storage.local.remove('synced').then(() => respond({ ok: true }));
    return true;
  }
});
