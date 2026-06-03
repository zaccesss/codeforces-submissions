#include <bits/stdc++.h>
using namespace std;

int main() {

    // Used s to store lever description.
    string s;
    cin >> s;

    // Used pivot to store position of '^'.
    int pivot = s.find('^');

    // Used long long because torques can be large.
    long long leftTorque = 0;
    long long rightTorque = 0;

    // Processed every position on the lever.
    for (int i = 0; i < s.size(); i++) {

        // Skipped empty positions and pivot.
        if (s[i] == '=' || s[i] == '^') {
            continue;
        }

        // Converted digit character to weight.
        int weight = s[i] - '0';

        // Added contribution to left side.
        if (i < pivot) {
            leftTorque += 1LL * weight * (pivot - i);
        }

        // Added contribution to right side.
        else if (i > pivot) {
            rightTorque += 1LL * weight * (i - pivot);
        }
    }

    // Compared both torques.
    if (leftTorque > rightTorque) {
        cout << "left\n";
    }
    else if (rightTorque > leftTorque) {
        cout << "right\n";
    }
    else {
        cout << "balance\n";
    }

    return 0;
}