#include <bits/stdc++.h>
using namespace std;

int main() {

    // Used n to store number of columns.
    int n;
    cin >> n;

    // Used heights to store column heights.
    vector<int> heights(n);

    // Read all column heights.
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    // Sorted heights in ascending order.
    sort(heights.begin(), heights.end());

    // Printed sorted heights.
    for (int i = 0; i < n; i++) {
        cout << heights[i];

        if (i < n - 1) {
            cout << " ";
        }
    }

    cout << "\n";

    return 0;
}