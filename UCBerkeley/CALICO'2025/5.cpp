#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll countUwuPairs(const string &input) {
    ll totalUCount = 0;
    for (char ch : input)
        if (ch == 'u')
            totalUCount++;
    
    ll totalPairs = totalUCount * (totalUCount - 1) / 2;
    
    ll invalidPairs = 0;
    ll currentSegmentUCount = 0;
    for (char ch : input) {
        if (ch == 'w') {
            invalidPairs += currentSegmentUCount * (currentSegmentUCount - 1) / 2;
            currentSegmentUCount = 0;
        } else if (ch == 'u') {
            currentSegmentUCount++;
        }
    }
    invalidPairs += currentSegmentUCount * (currentSegmentUCount - 1) / 2;
    
    return totalPairs - invalidPairs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCount;
    cin >> testCount;
    while (testCount--) {
        string message;
        cin >> message;
        cout << countUwuPairs(message) << "\n";
    }
    return 0;
}
