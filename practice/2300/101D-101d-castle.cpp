#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Child {
    int v;
    ll cost;
    ll sz;
    ll w;
};

const int N = 100000 + 5;

vector<pair<int,int>> g[N];

ll sz[N];
double dp[N];
ll costSub[N];

void dfs(int u, int p) {
    sz[u] = 1;

    vector<Child> children;

    for (auto [v, w] : g[u]) {
        if (v == p) continue;

        dfs(v, u);

        sz[u] += sz[v];

        children.push_back({
            v,
            costSub[v] + 2LL * w,
            sz[v],
            w
        });
    }

    sort(children.begin(), children.end(),
         [](const Child& a, const Child& b) {
             return a.cost * b.sz < b.cost * a.sz;
         });

    ll cur = 0;
    dp[u] = 0;

    for (auto &c : children) {
        dp[u] += dp[c.v];
        dp[u] += (double)c.sz * (cur + c.w);

        cur += c.cost;
    }

    costSub[u] = cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int a, b, t;
        cin >> a >> b >> t;

        g[a].push_back({b, t});
        g[b].push_back({a, t});
    }

    dfs(1, 0);

    cout << fixed << setprecision(15)
         << dp[1] / (n - 1) << '\n';

    return 0;
}