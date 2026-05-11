// Codeforces 318A - Even Odds

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    long long n, k; // n = upper bound, k = position
    if (!(cin >> n >> k)) return 0; // read input

    long long odd_count = (n + 1) / 2; // count of odd numbers

    long long result;
    if (k <= odd_count) {
        result = 2 * k - 1; // k-th odd
    } else {
        result = 2 * (k - odd_count); // k-th even
    }

    cout << result << '\n'; // output answer
    return 0; // done
}
