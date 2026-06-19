#include <iostream>
#include <cmath>
using namespace std;

int main() {
    long long A, B, n;
    cin >> A >> B >> n;

    // A=0: 0*X^n = 0 for all X, so any X works when B=0
    if (A == 0) {
        cout << (B == 0 ? "0" : "No solution");
        return 0;
    }

    // brute force X in [-1000, 1000] — safe range since |B/A| <= 1000
    // and for n>=2 the valid X is bounded by 1000^(1/n) anyway
    for (long long x = -1000; x <= 1000; x++) {
        long long val = A;
        bool too_big = false;
        for (int i = 0; i < n; i++) {
            val *= x;
            // once |val| > 10^15 it can only grow; early exit avoids overflow
            if (val > 1e15 || val < -1e15) { too_big = true; break; }
        }
        if (!too_big && val == B) {
            cout << x;
            return 0;
        }
    }

    cout << "No solution";
    return 0;
}
