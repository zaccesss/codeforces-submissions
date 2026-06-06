#include <bits/stdc++.h>
using namespace std;

int main() {
    string currentTime, sleepTime;
    cin >> currentTime >> sleepTime;

    int ch = stoi(currentTime.substr(0, 2));
    int cm = stoi(currentTime.substr(3, 2));

    int sh = stoi(sleepTime.substr(0, 2));
    int sm = stoi(sleepTime.substr(3, 2));

    // Converted times to minutes
    int current = ch * 60 + cm;
    int sleep = sh * 60 + sm;

    // Calculated bedtime
    int bedtime = current - sleep;

    if (bedtime < 0) {
        bedtime += 1440;
    }

    // Converted back to hours and minutes
    int hours = bedtime / 60;
    int minutes = bedtime % 60;

    cout << setw(2) << setfill('0') << hours << ":"
         << setw(2) << setfill('0') << minutes << '\n';

    return 0;
}