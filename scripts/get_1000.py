import json, urllib.request, sys

try:
    with urllib.request.urlopen('https://codeforces.com/api/problemset.problems') as f:
        data = json.load(f)
except Exception as e:
    print('ERR', e)
    sys.exit(1)

probs = [p for p in data['result']['problems'] if p.get('rating') == 1000]
seen = set()
unique = []
for p in probs:
    key = (p.get('contestId'), p.get('index'))
    if key in seen:
        continue
    seen.add(key)
    unique.append(p)

unique.sort(key=lambda x: (x.get('contestId', 0), x.get('index', '')))
for p in unique[:60]:
    tags = ','.join(p.get('tags', []))
    print(f"{p.get('contestId')} {p.get('index')} | {p.get('name')} | tags: {tags}")
print(f"Total 1000-rated problems found: {len(unique)}")
