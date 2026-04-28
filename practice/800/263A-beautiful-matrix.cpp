#include <bits/stdc++.h>
using namespace std;
int main() {
    for (int i = 0; i < 5; i++)        // loop through rows
        for (int j = 0; j < 5; j++) {  // loop through columns
            int x; cin >> x;            // read each value
            if (x == 1)                 // found the 1
                cout << abs(i - 2) + abs(j - 2); // distance to centre (index 2,2)
        }
}