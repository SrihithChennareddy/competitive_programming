#include <iostream>

#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <unordered_set>
#include <stack>
#include <ext/pb_ds/assoc_container.hpp>
#include <random>
#include <chrono>
#include <bitset>
#include <iterator>
#include <complex>
#include <functional>

using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define ld long double
#define f first
#define s second
template <class T>
using iset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename U>
bool emin(T &a, const U &b) { return b < a ? a = b, true : false; }
template <typename T, typename U>
bool emax(T &a, const U &b) { return b > a ? a = b, true : false; }
typedef uint64_t hash_t;
ll const inf = (ll) 1e15 + 7;
int const M = (int) 1e9 + 7;




void solve() {

    int n, m; cin >> n >> m; 
    string z; cin >> z; 
    pair<int, int> cur = {0, 0}; int ind = 0; 
    vector<pair<int, int>> a(n * m); 
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int x; cin >> x; x--; 
            a[x] = {i, j}; 
        }
    }
    ll an = 0; 
    auto dis = [&](auto x, auto y) {
        return min(n + min(x.f, y.f) - max(x.f, y.f), abs(y.f - x.f)) 
            + min(m + min(x.s, y.s) - max(x.s, y.s), abs(y.s - x.s));
    };
    for(int i = 0; i < n * m; i++) {
        int v = 0; 
        while(dis(cur, a[i]) > v) {
            if(z[ind] == 'U') cur.f = (cur.f - 1 + n) % n; 
            if(z[ind] == 'D') cur.f = (cur.f + 1 + n) % n; 
            if(z[ind] == 'L') cur.s = (cur.s - 1 + m) % m; 
            if(z[ind] == 'R') cur.s = (cur.s + 1 + m) % m; 
            v++; 
            ind = (ind + 1) % z.size(); 
        }
        cur = a[i]; 
        an += v; 
    }
    cout << an << endl;
}
int main() {
    int t; cin >> t; 
    while(t--) solve(); 
}
