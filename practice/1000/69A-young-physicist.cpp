// Solution for Codeforces 69A - Young Physicist

#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    // The body is in equilibrium only if the net force is zero in every axis.
    int sx = 0, sy = 0, sz = 0;
    for (int i = 0; i < n; ++i) {
        int x, y, z;
        cin >> x >> y >> z;

        // Add each force vector component-wise.
        sx += x;
        sy += y;
        sz += z;
    }

    // If all three sums cancel out, the forces are balanced.
    cout << (sx == 0 && sy == 0 && sz == 0 ? "YES" : "NO") << '\n';
    return 0;
}
