#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;  // read the two strings

    // Convert both strings to lowercase so comparison becomes case-insensitive.
    for (char &ch : a) {
        ch = tolower(ch);
    }
    for (char &ch : b) {
        ch = tolower(ch);
    }

    // Print -1 if a < b, 1 if a > b, otherwise 0.
    if (a < b) {
        cout << -1 << '\n';
    } else if (a > b) {
        cout << 1 << '\n';
    } else {
        cout << 0 << '\n';
    }

    return 0;  // program finished successfully
}