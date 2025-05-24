#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()

const int INF = 1e9+5;
const int MAXN = 2e5+5;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, k; cin >> n >> k;
  vector<ll> a(n);
  for(int i=0; i<n; i++) cin >> a[i];

  sort(all(a));

  ll m = n / k;
  ll p = (k + 1) / 2;
  ll ans = 0;

  for(int i=0; i<n; ) {
    int j = i + 1;
    while(j < n && a[j] == a[i]) j++;
    ll freq = j - i;
    ll le = j; 
    ll l  = i;

    if(le / m >= p && (n - l) >= p) {
      ans += freq;
    }

    // cerr << "val=" << a[i] << " freq=" << freq << "\n";
    i = j;
  }

  printf("%lld\n", ans);
  return 0;
}
