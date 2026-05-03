#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, m, a;    // n = rows, m = cols of the square, a = flagstone size
    cin >> n >> m >> a;   // read all three values from input

    // To cover a row of length n using tiles of size a, we need ceil(n/a) tiles.
    // Integer ceiling trick: ceil(x/y) = (x + y - 1) / y — avoids floating point.
    long long tilesPerRow = (n + a - 1) / a;  // how many tiles fit across the rows
    long long tilesPerCol = (m + a - 1) / a;  // how many tiles fit across the columns

    // Total tiles = tiles needed for rows * tiles needed for columns
    cout << tilesPerRow * tilesPerCol << '\n';

    return 0;  // program finished successfully
}
