const $ = (id) => document.getElementById(id);

const setStatus = (msg, cls = '') => {
  const el = $('status');
  el.textContent = msg;
  el.className = cls;
};

chrome.storage.sync.get(['cfHandle', 'githubToken', 'githubRepo'], (data) => {
  if (data.cfHandle)    $('cfHandle').value    = data.cfHandle;
  if (data.githubToken) $('githubToken').value = data.githubToken;
  if (data.githubRepo)  $('githubRepo').value  = data.githubRepo;
});

$('btnSave').addEventListener('click', () => {
  const config = {
    cfHandle:    $('cfHandle').value.trim(),
    githubToken: $('githubToken').value.trim(),
    githubRepo:  $('githubRepo').value.trim(),
  };
  if (!config.cfHandle || !config.githubToken || !config.githubRepo) {
    setStatus('Fill in all three fields.', 'err');
    return;
  }
  chrome.storage.sync.set(config, () => setStatus('Saved.', 'ok'));
});

$('btnClear').addEventListener('click', () => {
  chrome.runtime.sendMessage({ action: 'clearSynced' }, () => setStatus('History cleared.', 'ok'));
});
