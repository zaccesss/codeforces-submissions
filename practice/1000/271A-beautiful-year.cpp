// Codeforces 271A - Beautiful Year
// https://codeforces.com/problemset/problem/271/A
// Solution by zac

#include <bits/stdc++.h>
using namespace std;

// A year is "beautiful" if all 4 of its digits are distinct.
bool isBeautiful(int y) {
    int digits[4];
    for (int i = 3; i >= 0; i--) {
        digits[i] = y % 10;
        y /= 10;
    }
    // Use a set to check for duplicates.
    set<int> s(digits, digits + 4);
    return s.size() == 4;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int y;
    cin >> y;

    // Increment until we find the next beautiful year.
    y++;
    while (!isBeautiful(y)) y++;

    cout << y << '\n';
    return 0;
}
