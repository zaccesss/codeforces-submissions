// Solution for Codeforces 230A - Dragons

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int s, n;
    if (!(cin >> s >> n)) return 0;

    // store pairs of (required_strength, bonus)
    vector<pair<int,int>> dragons;
    dragons.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        dragons.emplace_back(x, y);
    }

    // sort by required strength so we try the easiest dragons first
    sort(dragons.begin(), dragons.end());

    for (auto &d : dragons) {
        int required = d.first;
        int bonus = d.second;
        // must be strictly greater
        if (s <= required) {
            cout << "NO\n";
            return 0;
        }
        s += bonus; // gain bonus after victory
    }

    cout << "YES\n";
    return 0;
}
