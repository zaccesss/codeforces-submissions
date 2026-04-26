#include <bits/stdc++.h>  // imports everything we need
using namespace std;       // so we don't have to write std::cout every time

int main() {
    int n;
    cin >> n;              // read how many words there are
    while (n--) {          // loop n times, counting down
        string s;
        cin >> s;          // read each word
        if (s.size() > 10) {  // if the word is longer than 10 letters
            cout << s[0] << s.size() - 2 << s[s.size() - 1] << endl;
            // print: first letter + number of middle letters + last letter
        } else {
            cout << s << endl;  // word is short enough, print it as is
        }
    }
    return 0;  // program finished successfully
}