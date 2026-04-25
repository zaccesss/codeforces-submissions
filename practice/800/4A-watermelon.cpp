#include <bits/stdc++.h>
using namespace std;

int main() {
    int w;        // declare a variable w to store the watermelon weight
    cin >> w;     // read the input number into w

    if (w % 2 == 0 && w > 2) {  // if w is even AND greater than 2
        cout << "YES" << endl;   // print YES
    } else {
        cout << "NO" << endl;    // otherwise print NO
    }

    return 0;  // end the program
}