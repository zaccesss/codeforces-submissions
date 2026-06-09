#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {

    // Used encoded to store the encrypted password.
    string encoded;
    cin >> encoded;

    // Used mapping to store code -> digit.
    unordered_map<string, char> mapping;

    // Read digit encodings.
    for (int digit = 0; digit <= 9; digit++) {
        string code;
        cin >> code;

        mapping[code] = char('0' + digit);
    }

    // Decoded the password.
    for (int i = 0; i < 80; i += 10) {

        string block = encoded.substr(i, 10);

        cout << mapping[block];
    }

    cout << '\n';

    return 0;
}