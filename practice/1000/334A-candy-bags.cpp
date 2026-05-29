#include <bits/stdc++.h>
using namespace std;

int main() {

    // Used n to store number of brothers.
    int n;
    cin >> n;

    // Used left and right pointers for smallest and largest bags.
    int left = 1;
    int right = n * n;

    // Looped through every brother.
    for (int i = 0; i < n; i++) {

        // Gave each brother n / 2 pairs of bags.
        for (int j = 0; j < n / 2; j++) {

            // Printed smallest remaining bag.
            cout << left << " ";

            // Printed largest remaining bag.
            cout << right << " ";

            // Moved both pointers.
            left++;
            right--;
        }

        // Moved to next brother line.
        cout << "\n";
    }

    return 0;
}
