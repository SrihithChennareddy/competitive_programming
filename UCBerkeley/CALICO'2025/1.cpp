#include <iostream>
#include <string>

using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        long long tot = 0; 
        long long curr = 1;

        for (int i = 0; i < n; ++i) {
            if (s[i] == 'T') {
                tot += curr;
                curr = 1; 
            } else {
                curr *= 2; 
            }
        }
        cout << tot << endl;
    }
    return 0;
}
