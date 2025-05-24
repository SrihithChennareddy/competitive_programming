#include <iostream>
// #include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cmath>

#define f first
#define s second
#define pb push_back

using namespace std;

using ll = long long;
template <int MOD, int RT>
struct mint
{
  static const int mod = MOD;
  static constexpr mint rt() { return RT; } // primitive root
  int v;
  explicit operator int() const { return v; }
  mint() : v(0) {}
  mint(ll _v) : v(int(_v % MOD)) { v += (v < 0) * MOD; }
  mint &operator+=(mint o)
  {
    if ((v += o.v) >= MOD)
      v -= MOD;
    return *this;
  }
  mint &operator-=(mint o)
  {
    if ((v -= o.v) < 0)
      v += MOD;
    return *this;
  }
  mint &operator*=(mint o)
  {
    v = int((ll)v * o.v % MOD);
    return *this;
  }
  friend mint pow(mint a, ll p)
  {
    return p == 0 ? 1 : pow(a * a, p / 2) * (p & 1 ? a : 1);
  }
  friend mint inv(mint a)
  {
    return pow(a, MOD - 2);
  }
  friend mint operator+(mint a, mint b) { return a += b; }
  friend mint operator-(mint a, mint b) { return a -= b; }
  friend mint operator*(mint a, mint b) { return a *= b; }
};
using mi = mint<(int)1e9 + 7, 5>;

#define v vector
using vl = v<mi>;
using vvl = v<vl>;
using vvvl = v<vvl>;

void solve_testcase()
{
  int n;
  cin >> n;

  vector<int> vals(n);
  for (auto &val : vals)
    cin >> val;

  vvvl dp = vvvl(n, vvl(n, vl(6))); // dp[start][end] gives [0 no parens, 1 no parens, 0s0, 1s0, 0s1, 1s1]
  for (int i = 0; i < n; i++)
  {
    int val = vals[i];
    if (val == 0)
    {
      dp[i][i][0] = 1;
      // dp[i][i][2] = 1;
    }
    else
    {
      dp[i][i][1] = 1;
      // dp[i][i][3] = 1;
    }
    dp[i][i][2] = 1;
    dp[i][i][5] = 1;
  }

  for (int l = 2; l <= n; l++)
  {
    for (int start = 0; start + l - 1 < n; start++)
    {
      int end = start + l - 1;
      int val = vals[end];
      mi nz = dp[start][end - 1][0], no = dp[start][end - 1][1];
      mi nzs0 = dp[start][end - 1][2], nos0 = dp[start][end - 1][3];
      mi nzs1 = dp[start][end - 1][4], nos1 = dp[start][end - 1][5];
      if (val == 0)
      {
        dp[start][end][0] += 3 * nz + no;
        dp[start][end][1] += 2 * no;
        dp[start][end][2] += 3 * nzs0 + nos0;
        dp[start][end][3] += 2 * nos0;
        dp[start][end][4] += 3 * nzs1 + nos1;
        dp[start][end][5] += 2 * nos1;
      }
      else
      {
        dp[start][end][0] += nz + no;
        dp[start][end][1] += 2 * nz + 2 * no;
        dp[start][end][2] += nzs0 + nos0;
        dp[start][end][3] += 2 * nzs0 + 2 * nos0;
        dp[start][end][4] += nzs1 + nos1;
        dp[start][end][5] += 2 * nzs1 + 2 * nos1;
      }
    }
  }

  // for (int l = 2; l <= n; l++)
  // {
  //   for (int start = 0; start + l - 1 < n; start++)
  //   {
  //     int end = start + l - 1;
  //     int val = vals[end];

  //     if (val == 0)
  //     {
  //       dp[start][end][2] += 3 * dp[start][end - 1][2] + dp[start][end - 1][3];
  //       dp[start][end][3] += 2 * dp[start][end - 1][3];
  //     }
  //     else
  //     {
  //       dp[start][end][2] += dp[start][end - 1][2] + dp[start][end - 1][3];
  //       dp[start][end][3] += 2 * dp[start][end - 1][2] + 2 * dp[start][end - 1][3];
  //     }
      
  //     for (int eparen = end; eparen > start; eparen--)
  //     {
  //       mi nz = dp[eparen][end][0], no = dp[eparen][end][1], snz = dp[start][eparen - 1][0], sno = dp[start][eparen - 1][1];
  //       dp[start][end][2] += 3 * snz * nz + snz * no + sno * nz + sno * no;
  //       dp[start][end][3] += 2 * sno * no + 2 * snz * no + 2 * sno * nz;
  //     }

  //     dp[start][end][2] += dp[start][end][0];
  //     dp[start][end][3] += dp[start][end][1];
  //   }
  // }
  mi ans = 0;
  for (int start = 0; start < n; start ++)
  {
    for (int end = start; end < n; end ++)
    {
      mi lz, lo;
      mi z = dp[start][end][0], o = dp[start][end][1];
      if (start == 0)
      {
        lz = z;
        lo = o;
      }
      else
      {
        mi llz = dp[0][start - 1][0], llo = dp[0][start - 1][1];
        lz = 3 * llz * z + llz * o + llo * z + llo * o;
        lo = 2 * llo * o + 2 * llz * o + 2 * llo * z;
      }

      if (end == n - 1)
      {
        ans += lo;
      }
      else
      {
        ans += dp[end][n - 1][3] * lz + dp[end][n - 1][5] * lo;
      }
    }
  }

  cout << (int) ans << endl;
}

int main()
{
  int t;
  cin >> t;

  while (t--)
    solve_testcase();
}
