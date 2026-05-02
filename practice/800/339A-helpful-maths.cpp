#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;                 // input comes like: 3+2+1
    cin >> s;                 // read the whole expression as one string

    vector<char> nums;        // we'll store only the numbers here
    for (char ch : s) {       // go through each character in the string
        if (ch != '+') {      // skip '+' and keep digits only
            nums.push_back(ch);
        }
    }

    sort(nums.begin(), nums.end());  // sort digits from smallest to biggest

    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > 0) {          // add '+' before every number except first one
            cout << "+";
        }
        cout << nums[i];      // print current sorted digit
    }
    cout << '\n';             // move to next line at the end

    return 0;                  // program finished successfully
}