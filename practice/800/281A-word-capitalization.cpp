#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;  // read the word

    // Capitalize only the first character (if it is a lowercase letter).
    s[0] = toupper(s[0]);

    cout << s << '\n';  // print the updated word
    return 0;
}