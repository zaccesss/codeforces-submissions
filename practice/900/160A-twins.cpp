// Codeforces 160A - Twins
// https://codeforces.com/problemset/problem/160/A
// Solution by zac

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> coins(n);
    int total = 0;

    for (int i = 0; i < n; i++) {
        cin >> coins[i];
        total += coins[i];
    }

    sort(coins.rbegin(), coins.rend()); // take the biggest coins first

    int taken_sum = 0;
    for (int i = 0; i < n; i++) {
        taken_sum += coins[i];

        // Stop once our chosen coins are worth more than the remaining coins.
        if (taken_sum > total - taken_sum) {
            cout << i + 1 << '\n';
            return 0;
        }
    }

    return 0;
}
