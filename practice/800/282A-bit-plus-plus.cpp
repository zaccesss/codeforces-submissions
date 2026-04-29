#include <bits/stdc++.h>  // includes all standard libraries
using namespace std;       // avoids writing std:: prefix everywhere

int main() {
    int n;
    cin >> n;  // read how many operations there are

    int x = 0;
    while (n--) {
        string operation;
        cin >> operation;

        if (operation.find('+') != string::npos) {
            x++;  // ++X or X++ increases x
        } else {
            x--;  // --X or X-- decreases x
        }
    }

    cout << x << endl;
    return 0;  // program finished successfully
}
