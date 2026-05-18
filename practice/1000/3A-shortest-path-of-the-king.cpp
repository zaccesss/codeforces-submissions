// Solution for Codeforces 3A - Shortest Path of the King

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string start, finish;
    if (!(cin >> start >> finish)) return 0;

    int dx = finish[0] - start[0]; // file difference
    int dy = finish[1] - start[1]; // rank difference

    int moves = max(abs(dx), abs(dy)); // diagonal moves cover both axes

    cout << moves << '\n';
    while (dx != 0 || dy != 0) {
        string step;

        if (dx > 0) {
            step += 'R'; // move right
            --dx;
        } else if (dx < 0) {
            step += 'L'; // move left
            ++dx;
        }

        if (dy > 0) {
            step += 'U'; // move up
            --dy;
        } else if (dy < 0) {
            step += 'D'; // move down
            ++dy;
        }

        cout << step << '\n';
    }

    return 0;
}
