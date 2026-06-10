#include <iostream>
#include <string>
using namespace std;

int main() {

    // Used x and y as input strings.
    string x, y;
    cin >> x >> y;

    // Checked if a solution exists.
    for (int i = 0; i < x.size(); i++) {

        if (y[i] > x[i]) {
            cout << -1 << '\n';
            return 0;
        }
    }

    // Used y itself as the answer.
    cout << y << '\n';

    return 0;
}