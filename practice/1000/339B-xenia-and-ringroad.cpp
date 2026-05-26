// Codeforces 339B - Xenia and Ringroad
// https://codeforces.com/problemset/problem/339/B
// Solution by zac

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m; // n houses on the ring, m tasks in order

    long long current = 1; // Xenia starts at house 1
    long long time = 0;    // total time spent moving

    for (long long i = 0; i < m; i++) {
        long long target;
        cin >> target; // next house that must be visited

        if (target >= current) {
            // move forward directly without wrapping
            time += target - current;
        } else {
            // wrap from n back to 1, then continue to target
            time += (n - current) + target;
        }

        current = target; // we are now standing at this house
    }

    cout << time << '\n';
    return 0;
}
