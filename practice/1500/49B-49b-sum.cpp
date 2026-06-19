#include <bits/stdc++.h>
using namespace std;
 
// interpret the decimal digits of n as digits in the given basee
long long interpret(int n, int base) {
    string s = to_string(n);
    long long val = 0;
    for (char c : s) val = val * base + (c - '0');
    return val;
}
 
int numDigits(long long n, int base) {
    int cnt = 0;
    while (n > 0) { n /= base; cnt++; }
    return cnt;
}
 
int main() {
    int a, b;
    cin >> a >> b;
 
    // minimum valid base = max digit in a or b + 1
    string sa = to_string(a), sb = to_string(b);
    int minBase = 1;
    for (char c : sa + sb) minBase = max(minBase, c - '0' + 1);
 
    int ans = 1;
    // for large bases the sum shrinks to 1-2 digits quickly; 10000 is safe
    for (int p = minBase; p <= 10000; p++) {
        long long sum = interpret(a, p) + interpret(b, p);
        ans = max(ans, numDigits(sum, p));
    }
 
    cout << ans << "\n";
} // done