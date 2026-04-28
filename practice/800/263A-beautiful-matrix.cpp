#include <bits/stdc++.h>
using namespace std;
int main() {
    for (int i = 0; i < 5; i++)        // loop through each row
        for (int j = 0; j < 5; j++) {  // loop through each column
            int x; cin >> x;            // read current cell value
            if (x == 1)                 // found the 1
                // minimum moves = manhattan distance to centre (index 2,2)
                cout << abs(i - 2) + abs(j - 2);
        }
}