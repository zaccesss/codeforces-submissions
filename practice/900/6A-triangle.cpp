#include <iostream>
#include <algorithm>
using namespace std;

int main() {

    // Used array to store stick lengths.
    int a[4];

    // Read all stick lengths.
    for (int i = 0; i < 4; i++) {
        cin >> a[i];
    }

    bool segment = false;

    // Checked every combination of three sticks.
    for (int i = 0; i < 4; i++) {

        int sides[3];
        int idx = 0;

        // Built current triple.
        for (int j = 0; j < 4; j++) {
            if (j != i) {
                sides[idx++] = a[j];
            }
        }

        // Sorted the three sides.
        sort(sides, sides + 3);

        // Returned triangle if possible.
        if (sides[0] + sides[1] > sides[2]) {
            cout << "TRIANGLE\n";
            return 0;
        }

        // Marked segment if degenerate triangle exists.
        if (sides[0] + sides[1] == sides[2]) {
            segment = true;
        }
    }

    // Returned segment if found.
    if (segment) {
        cout << "SEGMENT\n";
    }
    else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}