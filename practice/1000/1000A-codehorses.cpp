// Codeforces A - Codehorses T-shirts
// Solution by zac

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<string> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    const int INF = 1000000000;
    vector<vector<int>> cost(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i].size() != b[j].size()) continue;
            int d = 0;
            for (size_t k = 0; k < a[i].size(); ++k) if (a[i][k] != b[j][k]) ++d;
            cost[i][j] = d;
        }
    }

    // Hungarian algorithm (minimum assignment)
    int N = n;
    vector<int> u(N+1), v(N+1), p(N+1), way(N+1);
    for (int i = 1; i <= N; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(N+1, INF);
        vector<char> used(N+1, false);
        do {
            used[j0] = true;
            int i0 = p[j0];
            int delta = INF, j1 = 0;
            for (int j = 1; j <= N; ++j) if (!used[j]) {
                int cur = cost[i0-1][j-1] - u[i0] - v[j];
                if (cur < minv[j]) { minv[j] = cur; way[j] = j0; }
                if (minv[j] < delta) { delta = minv[j]; j1 = j; }
            }
            for (int j = 0; j <= N; ++j) {
                if (used[j]) { u[p[j]] += delta; v[j] -= delta; }
                else minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }

    vector<int> assign(N+1);
    for (int j = 1; j <= N; ++j) assign[p[j]] = j;

    long long ans = 0;
    for (int i = 1; i <= N; ++i) {
        int j = assign[i];
        if (cost[i-1][j-1] >= INF) continue; // shouldn't happen due to problem guarantee
        ans += cost[i-1][j-1];
    }

    cout << ans << '\n';
    return 0;
}
