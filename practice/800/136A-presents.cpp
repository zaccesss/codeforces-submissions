// Codeforces Round #136 (Div. 2) - Problem A: Presents

#include <bits/stdc++.h>
using namespace std;

int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int n;
        // read number of people / size of permutation
        if (!(cin >> n)) return 0;

        // p[i] = recipient of present given by person i (1-indexed)
        vector<int> p(n + 1);
        for (int i = 1; i <= n; ++i) cin >> p[i];

        // q[x] will hold the giver of present x (inverse permutation)
        vector<int> q(n + 1);
        for (int i = 1; i <= n; ++i) q[p[i]] = i;

        // output q[1..n] separated by spaces
        for (int i = 1; i <= n; ++i) {
                if (i > 1) cout << ' ';
                cout << q[i];
        }
        cout << '\n';
        return 0;
}
