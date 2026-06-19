#include <iostream>
#include <vector>
 
using namespace std;
 
int main() {
 
    int n;
    cin >> n;
 
    vector<int> negative;
    vector<int> positive;
    vector<int> zero;
 
    for (int i = 0; i < n; i++) {
 
        int x;
        cin >> x;
 
        if (x < 0) {
            negative.push_back(x);
        }
        else if (x > 0) {
            positive.push_back(x);
        }
        else {
            zero.push_back(x);
        }
    }
 
    vector<int> set1;
    vector<int> set2;
    vector<int> set3;
 
    // Used one negative number for set 1.
    set1.push_back(negative.back());
    negative.pop_back();
 
    // If there are no positive numbers,
    // used two negatives to create a positive product.
    if (positive.empty()) {
 
        set2.push_back(negative.back());
        negative.pop_back();
 
        set2.push_back(negative.back());
        negative.pop_back();
    }
    else {
 
        set2 = positive;
    }
 
    // Put remaining numbers into set 3.
    for (int x : negative) {
        set3.push_back(x);
    }
 
    for (int x : zero) {
        set3.push_back(x);
    }
 
    cout << set1.size();
    for (int x : set1) {
        cout << " " << x;
    }
    cout << '
';
 
    cout << set2.size();
    for (int x : set2) {
        cout << " " << x;
    }
    cout << '
';
 
    cout << set3.size();
    for (int x : set3) {
        cout << " " << x;
    }
    cout << '
';
 
    return 0;
}