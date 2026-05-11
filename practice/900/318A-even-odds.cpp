// Codeforces 318A - Even Odds
// Minimal header; inline comments kept in logic below.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    if (!(cin >> n >> k)) return 0;

    long long odd_count = (n + 1) / 2;
    long long result;
    if (k <= odd_count) {
        result = 2 * k - 1; // k-th odd
    } else {
        result = 2 * (k - odd_count); // corresponding even
    }

    cout << result << '\n';
    return 0;
}
