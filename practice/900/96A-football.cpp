#include <iostream>
#include <string>
using namespace std;

int main() {

    // Used s to store player positions.
    string s;
    cin >> s;

    // Used streak to track consecutive players.
    int streak = 1;

    // Processed the string.
    for (int i = 1; i < s.size(); i++) {

        if (s[i] == s[i - 1]) {
            streak++;
        } else {
            streak = 1;
        }

        // Returned YES if dangerous situation found.
        if (streak >= 7) {
            cout << "YES\n";
            return 0;
        }
    }

    // Returned NO if no dangerous situation exists.
    cout << "NO\n";

    return 0;
}