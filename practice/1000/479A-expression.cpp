// Solution for Codeforces 479A - Expression

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    // Optimise standard I/O operations for performance
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;
    if (!(cin >> a >> b >> c)) return 0;

    // Evaluate all 6 possible expressions using '+' and '*' with brackets:
    int ans1 = a + b + c;
    int ans2 = a * b * c;
    int ans3 = (a + b) * c;
    int ans4 = a * (b + c);
    int ans5 = a + b * c;
    int ans6 = a * b + c;

    // Find the maximum value among all configurations
    int max_ans = max({ans1, ans2, ans3, ans4, ans5, ans6});

    cout << max_ans << '\n';

    return 0;
}
