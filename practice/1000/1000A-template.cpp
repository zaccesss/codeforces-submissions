// practice/1000/1000A-template.cpp
// C++ template stub added by GitHub Copilot for a 1000-level practice problem.
// Replace the body of `solve()` with the problem-specific solution.

#include <bits/stdc++.h>
using namespace std;

void solve() {
    // Example template: read n, then n integers, print their sum.
    long long n;
    if (!(cin >> n)) return;
    long long sum = 0;
    for (long long i = 0; i < n; ++i) {
        long long x; cin >> x; sum += x;
    }
    cout << sum << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // If the problem has multiple test cases, uncomment next line:
    // cin >> T;
    while (T--) solve();
    return 0;
}
