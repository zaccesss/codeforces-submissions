// Codeforces 25A - IQ Test
// https://codeforces.com/problemset/problem/25/A
// Solution by zac

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // count how many are odd vs even to find the minority parity
    int odds = 0, evens = 0;
    for (int x : a) {
        if (x % 2 == 0) evens++;
        else odds++;
    }

    // the number that does not share the majority parity is the answer
    int minority = (odds < evens) ? 1 : 0; // 1 = odd, 0 = even

    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == minority) {
            cout << i + 1 << '\n';
            return 0;
        }
    }

    return 0;
}
