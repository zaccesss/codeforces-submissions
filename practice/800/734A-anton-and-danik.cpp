// Codeforces 734A - Anton and Danik
// https://codeforces.com/problemset/problem/734/A
// Solution by zac
//
// This code counts how many games Anton and Danik won.
// Then it prints the player with more wins, or "Friendship" if tied.

#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n; // Read how many games were played

    string games;
    cin >> games; // Read the string of winners

    int anton_wins = 0; // Counter for Anton's wins
    int danik_wins = 0; // Counter for Danik's wins

    // Loop through each game result
    for (char winner : games) {
        if (winner == 'A') {
            anton_wins++; // Anton won this game
        } else {
            danik_wins++; // Danik won this game
        }
    }

    // Compare the win counts and print the result
    if (anton_wins > danik_wins) {
        cout << "Anton" << endl;
    } else if (danik_wins > anton_wins) {
        cout << "Danik" << endl;
    } else {
        cout << "Friendship" << endl;
    }

    return 0; // Program finished successfully
}
