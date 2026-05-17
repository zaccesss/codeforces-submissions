// Solution for Codeforces 43A - Football

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0; // number of goals scored in the match

    map<string, int> goals; // goals[team] stores how many times that team scored
    string winner;          // team with the highest goal count seen so far
    int best = 0;           // highest goal count seen so far

    for (int i = 0; i < n; ++i) {
        string team;
        cin >> team; // team that scored this goal

        int current = ++goals[team]; // update this team's total goals
        if (current > best) {
            best = current;  // new highest score
            winner = team;   // remember the current leader
        }
    }

    cout << winner << '\n'; // print the team that scored the most goals
    return 0;
}
