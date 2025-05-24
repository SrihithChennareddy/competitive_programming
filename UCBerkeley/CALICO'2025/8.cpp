#include <iostream>
// #include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include <limits>
#include <string>
#include <cmath>

#define f first
#define s second
#define pb push_back

using namespace std;
using ll = long long;

int main() {
  int t;
  cin >> t;

  while (t --)
  {
    ll n;
    cin >> n;

    ll x = ceil((1 + sqrt(8 * n + 1)) / 2);
    // cout << "got x " << x << endl;

    vector<ll> to_sub;
    ll diff = (x * (x - 1)) / 2 - n;
    // cout << "got diff " << diff << endl;
    while (diff > 0)
    {
      ll y = floor((1 + sqrt(8 * diff + 1)) / 2);
      // cout << "got y " << y << endl;
      diff -= y * (y - 1) / 2;
      to_sub.push_back(y);
    }

    for (ll us : to_sub)
    {
      x -= us;
      while (us --)
      {
        cout << 'u';
      }
      cout << 'w';
    }

    while (x --)
    {
      cout << "uw";
    }
    
    cout << endl;
  }
}
