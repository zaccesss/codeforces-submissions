// Codeforces A - Codehorses T-shirts
// Solution by zac
// Implementation of the Hungarian algorithm for minimum-cost perfect matching in a bipartite graph.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // faster IO
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0; // number of T-shirts in each list

    vector<string> a(n), b(n); // a = previous year, b = current year
    for (int i = 0; i < n; ++i) cin >> a[i]; // read previous list
    for (int i = 0; i < n; ++i) cin >> b[i]; // read current list

    const int INF = 1000000000; // large value representing impossible match (different lengths)
    // cost[i][j] = number of differing characters to change a[i] into b[j], or INF if lengths differ
    vector<vector<int>> cost(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i].size() != b[j].size()) continue; // cannot transform if lengths differ
            int d = 0; // Hamming distance between strings of equal length
            for (size_t k = 0; k < a[i].size(); ++k) {
                if (a[i][k] != b[j][k]) ++d; // count differing characters
            }
            cost[i][j] = d; // minimal number of replacements to convert a[i] to b[j]
        }
    }

    // We need a minimum-cost perfect matching between a[] and b[].
    // Use the Hungarian algorithm on an n x n cost matrix.
    int N = n;
    vector<int> u(N+1), v(N+1), p(N+1), way(N+1);
    for (int i = 1; i <= N; ++i) {
        p[0] = i; // start matching with row i (1-based in algorithm)
        int j0 = 0; // current column in augmenting path
        vector<int> minv(N+1, INF); // min reduced cost for each column
        vector<char> used(N+1, false); // whether column is used in current phase
        do {
            used[j0] = true; // mark column j0 as visited
            int i0 = p[j0];  // the row currently matched to column j0
            int delta = INF; // minimum value to add to potentials
            int j1 = 0;      // column to move to
            // try to improve minv for all free columns
            for (int j = 1; j <= N; ++j) if (!used[j]) {
                // reduced cost for assigning row i0 to column j
                int cur = cost[i0-1][j-1] - u[i0] - v[j];
                if (cur < minv[j]) {
                    minv[j] = cur; // update minimal reduced cost for column j
                    way[j] = j0;   // remember path (previous column)
                }
                // find the column with the smallest minv to continue
                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }
            // update potentials by delta
            for (int j = 0; j <= N; ++j) {
                if (used[j]) {
                    u[p[j]] += delta; // increase potential for matched rows
                    v[j] -= delta;    // decrease potential for used columns
                } else {
                    minv[j] -= delta; // decrease the minv by delta for unused columns
                }
            }
            j0 = j1; // move to next column
        } while (p[j0] != 0); // while we haven't reached a free column
        // augmenting: update matching along the found path
        do {
            int j1 = way[j0];  // previous column on the path
            p[j0] = p[j1];     // move matching forward
            j0 = j1;           // step to previous column
        } while (j0 != 0);
    }

    // build assignment: assign[row] = column
    vector<int> assign(N+1);
    for (int j = 1; j <= N; ++j) assign[p[j]] = j;

    // compute total minimal cost (sum of character replacements)
    long long ans = 0;
    for (int i = 1; i <= N; ++i) {
        int j = assign[i]; // column assigned to row i
        if (cost[i-1][j-1] >= INF) continue; // should not happen as problem guarantees transformability
        ans += cost[i-1][j-1]; // add cost of transforming a[i-1] to b[j-1]
    }

    cout << ans << '\n'; // print minimal number of seconds (character replacements)
    return 0;
}
