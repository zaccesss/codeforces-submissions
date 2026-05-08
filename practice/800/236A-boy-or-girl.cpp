#include <bits/stdc++.h>
using namespace std;

int main() {
    string name;
    cin >> name;  // read the input name

    set<char> unique_letters;  // will store only unique letters
    for (char ch : name) {
        unique_letters.insert(ch);  // set only keeps one of each letter
    }

    // If the number of unique letters is even, print "CHAT WITH HER!"
    // If odd, print "IGNORE HIM!"
    if (unique_letters.size() % 2 == 0) {
        cout << "CHAT WITH HER!" << '\n';
    } else {
        cout << "IGNORE HIM!" << '\n';
    }
    return 0;
}
