#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0; // read the required amount

    // denominations in descending order
    int coins[] = {100, 20, 10, 5, 1};

    int ans = 0; // count of bills used
    for (int c : coins) {
        ans += n / c; // take as many of this bill as possible
        n %= c;       // reduce remaining amount
    }

    cout << ans << '\n';
    return 0;
}
