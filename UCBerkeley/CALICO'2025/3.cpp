#include <bits/stdc++.h>
using namespace std;

struct Competitor {
    string name;
    int power;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<string> names(N);
        for (int i = 0; i < N; ++i) {
            cin >> names[i];
        }
        vector<int> powers(N);
        for (int i = 0; i < N; ++i) {
            cin >> powers[i];
        }
        vector<Competitor> current;
        for (int i = 0; i < N; ++i) {
            current.push_back({names[i], powers[i]});
        }
        while (current.size() > 1) {
            vector<Competitor> next;
            for (size_t i = 0; i < current.size(); i += 2) {
                Competitor a = current[i];
                Competitor b = current[i + 1];
                if (a.power > b.power) {
                    a.power += b.power;
                    next.push_back(a);
                } else if (b.power > a.power) {
                    b.power += a.power;
                    next.push_back(b);
                } else {
                    Competitor merged;
                    merged.name = a.name + b.name;
                    merged.power = a.power + b.power;
                    next.push_back(merged);
                }
            }
            current = move(next);
        }
        cout << current[0].name << '\n';
    }
    return 0;
}
