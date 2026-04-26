#include <bits/stdc++.h>  // imports everything we need
using namespace std;       // so we don't have to write std:: every time

int main() {
    int n;
    cin >> n;              // read number of problems
    int count = 0;         // start counter at 0
    while (n--) {          // loop n times
        int p, v, t;
        cin >> p >> v >> t;  // read each friend's answer (0 or 1)
        if (p + v + t >= 2) count++;  // if 2 or more are sure, count it
    }
    cout << count << endl;  // print the result
    return 0;
}
