// Solution for Codeforces 5A - Chat Servers Outgoing Traffic

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    int online = 0;
    long long traffic = 0;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        if (line[0] == '+') {
            ++online; // user entered the chat
        } else if (line[0] == '-') {
            --online; // user left the chat
        } else {
            // A message has the form "name:text"; only text length counts.
            size_t colon = line.find(':');
            traffic += 1LL * online * (line.size() - colon - 1);
        }
    }

    cout << traffic << '\n';
    return 0;
}
