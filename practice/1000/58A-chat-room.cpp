// Solution for Codeforces 58A - Chat room

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    const string target = "hello";
    int matched = 0; // number of target letters matched in order

    for (char ch : s) {
        // take this character only when it is the next needed letter
        if (matched < (int)target.size() && ch == target[matched]) {
            ++matched;
        }
    }

    // if every letter in "hello" was found in order, Vasya said hello
    cout << (matched == (int)target.size() ? "YES" : "NO") << '\n';
    return 0;
}
