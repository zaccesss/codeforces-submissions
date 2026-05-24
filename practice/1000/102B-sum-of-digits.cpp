// Codeforces 102B - Sum of Digits
// https://codeforces.com/problemset/problem/102/B
// Solution by zac
//
// This code repeatedly sums the digits of a number until it has a single digit.

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Optimize input/output operations for competitive programming
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    // If the number is already a single digit, 0 operations are needed
    if (s.length() == 1) {
        cout << 0 << "\n";
        return 0;
    }

    // Step 1: Perform the first sum of digits from the large string
    long long sum = 0;
    for (char c : s) {
        sum += (c - '0');
    }
    
    int operations = 1;

    // Step 2: Keep summing digits of the resulting integer until it becomes a single digit (< 10)
    while (sum >= 10) {
        long long current_sum = 0;
        long long temp = sum;
        while (temp > 0) {
            current_sum += temp % 10;
            temp /= 10;
        }
        sum = current_sum;
        operations++;
    }

    // Output the total operations count
    cout << operations << "\n";

    return 0;
}
