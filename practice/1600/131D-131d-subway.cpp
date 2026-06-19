#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);

    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);

        deg[u]++;
        deg[v]++;
    }

    queue<int> q;
    vector<bool> removed(n + 1, false);

    // Remove leaves
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            q.push(i);
            removed[i] = true;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (removed[v]) continue;

            deg[v]--;

            if (deg[v] == 1) {
                removed[v] = true;
                q.push(v);
            }
        }
    }

    vector<int> dist(n + 1, -1);

    // Cycle nodes
    queue<int> bfs;

    for (int i = 1; i <= n; i++) {
        if (!removed[i]) {
            dist[i] = 0;
            bfs.push(i);
        }
    }

    while (!bfs.empty()) {
        int u = bfs.front();
        bfs.pop();

        for (int v : adj[u]) {
            if (dist[v] != -1) continue;

            dist[v] = dist[u] + 1;
            bfs.push(v);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << dist[i] << ' ';
    }

    cout << '\n';
    return 0;
}