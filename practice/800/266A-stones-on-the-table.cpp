#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;  // read the number of stones and their colors

    int removals = 0;  // count how many stones must be removed

    // If two neighboring stones have the same color,
    // we need to remove one of them.
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) {
            removals++;
        }
    }

    cout << removals << '\n';
    return 0;
}