#include <bits/stdc++.h>
using namespace std;

int main() {

    // Used k to store required flower growth.
    int k;
    cin >> k;

    // Returned 0 if no growth was needed.
    if (k == 0) {
        cout << 0 << "\n";
        return 0;
    }

    // Used months to store monthly growth values.
    vector<int> months(12);

    // Read all monthly growth values.
    for (int i = 0; i < 12; i++) {
        cin >> months[i];
    }

    // Sorted growth values in descending order.
    sort(months.begin(), months.end(), greater<int>());

    // Used total to track accumulated growth.
    int total = 0;

    // Used count to track months used.
    int count = 0;

    // Looped through sorted growth values.
    for (int growth : months) {

        // Added current month's growth.
        total += growth;

        // Increased month count.
        count++;

        // Returned answer once target was reached.
        if (total >= k) {
            cout << count << "\n";
            return 0;
        }
    }

    // Printed -1 if target growth was impossible.
    cout << -1 << "\n";

    return 0;
}
