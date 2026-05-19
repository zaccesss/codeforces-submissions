// Codeforces 59A - Word
// https://codeforces.com/problemset/problem/59/A
// Solution by zac
//
// This code counts how many uppercase and lowercase letters are in the word.
// Then it changes the whole word to the case that appears more often.
// If both counts are the same, Codeforces wants the word in lowercase.

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

int main() {
    string word;
    cin >> word; // Read the word

    int uppercase = 0; // Counter for uppercase letters
    int lowercase = 0; // Counter for lowercase letters

    // Loop through every character in the word
    for (char c : word) {
        if (isupper(static_cast<unsigned char>(c))) {
            uppercase++; // Add 1 if the character is uppercase
        } else {
            lowercase++; // Otherwise, it is lowercase
        }
    }

    // If there are more uppercase letters, convert the whole word to uppercase
    if (uppercase > lowercase) {
        transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
            return static_cast<char>(toupper(c));
        });
    } else {
        // If lowercase is more common, or counts are tied, convert to lowercase
        transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
            return static_cast<char>(tolower(c));
        });
    }

    cout << word << endl; // Print the final converted word
    return 0; // Program finished successfully
}
