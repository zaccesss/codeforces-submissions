#include <bits/stdc++.h>  // includes all standard libraries
using namespace std;       // avoids writing std:: prefix everywhere

int main() {
    int m, n;
    cin >> m >> n;               // read grid dimensions
    cout << (m * n) / 2 << endl; // max dominoes = total squares / 2
    return 0;  // ends program
}  