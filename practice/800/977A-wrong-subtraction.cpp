#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;  // n is the current number, k is how many operations to apply

    // Apply exactly k operations from the statement.
    while (k--) {
        if (n % 10 == 0) {
            n /= 10;  // if last digit is 0, remove that digit
        } else {
            n--;      // otherwise subtract 1
        }
    }

    cout << n << '\n';
    return 0;
}
