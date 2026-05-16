// Codeforces 617A - Elephant
// https://codeforces.com/problemset/problem/617/A
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    // Read the target position; exit quietly if no input provided.
    if (!(cin >> n)) return 0;

    // Compute and print the minimum number of moves.
    cout << (n + 4) / 5 << '\n';
    return 0;
}
