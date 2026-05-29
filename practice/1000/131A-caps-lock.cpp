#include <bits/stdc++.h>
using namespace std;

int main() {

    // Used s to store the input word.
    string s;
    cin >> s;

    // Used ok to check if case needs changing.
    bool ok = true;

    // Checked if every character after first is uppercase.
    for (int i = 1; i < s.size(); i++) {

        // Marked false if lowercase character found.
        if (islower(s[i])) {
            ok = false;
        }
    }

    // Changed all character cases if condition passed.
    if (ok) {

        // Looped through every character.
        for (int i = 0; i < s.size(); i++) {

            // Converted uppercase to lowercase.
            if (isupper(s[i])) {
                s[i] = tolower(s[i]);
            }

            // Converted lowercase to uppercase.
            else {
                s[i] = toupper(s[i]);
            }
        }
    }

    // Printed final word.
    cout << s << "\n";

    return 0;
}
