#include <bits/stdc++.h>
using namespace std;

int main() {

    // Used n to store number of cars.
    int n;
    cin >> n;

    // Used goodCars to store good car indices.
    vector<int> goodCars;

    // Processed each car.
    for (int i = 0; i < n; i++) {

        // Used good to track whether current car is good.
        bool good = true;

        // Read collision results for current row.
        for (int j = 0; j < n; j++) {

            int x;
            cin >> x;

            // Marked car as bad if it turned over.
            if (x == 1 || x == 3) {
                good = false;
            }
        }

        // Added car index if it was good.
        if (good) {
            goodCars.push_back(i + 1);
        }
    }

    // Printed number of good cars.
    cout << goodCars.size() << "\n";

    // Printed good car indices.
    for (int car : goodCars) {
        cout << car << " ";
    }

    cout << "\n";

    return 0;
}