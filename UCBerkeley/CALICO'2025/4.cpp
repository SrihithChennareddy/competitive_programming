#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<pair<int, int>> pos(N * M + 1);  
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                int val;
                cin >> val;
                pos[val] = {i, j};
            }
        }
        int cur_x = 0, cur_y = 0;
        int tot = 0;
        for (int k = 1; k <= N * M; ++k) {
            auto [x, y] = pos[k];
            int dx = abs(cur_x - x);
            dx = min(dx, N - dx);
            int dy = abs(cur_y - y);
            dy = min(dy, M - dy);
            tot += dx + dy;
            cur_x = x;
            cur_y = y;
        }
        cout << tot << '\n';
    }
    return 0;
}
