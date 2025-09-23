/*
Polo, the Penguin, has a lot of tests tomorrow at the university.

He knows that there are N different questions that will be on the tests. For each question i (i = 1..N), he knows C[i] - the number of tests that will contain this question, P[i] - the number of points that he will get for correctly answering this question on each of tests and T[i] - the amount of time (in minutes) that he needs to spend to learn this question.

Unfortunately, the amount of free time that Polo has is limited to W minutes. Help him to find the maximal possible total number of points he can get for all tests if he studies for no more than W minutes.

Input
The first line of the input contains an integer T denoting the number of test cases. The description of T test cases follows. The first line of each test case contains the pair of integers N and W, separated by a space. The following N lines contain three space-separated integers C[i], P[i] and T[i] (i = 1..N).

Output
For each test case, output a single line containing the answer to the corresponding test case.

Constraints
1 ≤ T ≤ 100
1 ≤ N ≤ 100
1 ≤ C[i], P[i], T[i] ≤ 100
1 ≤ W ≤ 100
*/

/**
 * problem:
 * author: Nabajyoti
 */
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#define ff first
#define ss second

using ll = long long int;
using pii = pair<ll, ll>;
using vii = vector<vector<ll>>;
const ll N = 1e1 + 5;
const ll mod = 1e9 + 7;
ll inf = 1e18;
const int nn = 20;

ll __gcd(ll a, ll b) {
    if (a == 0) return b;
    return __gcd(b % a, a);
}

ll mult(ll a, ll b)  // O(1)
{
    return ((a % mod) * (b % mod)) % mod;
}

ll dirs[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

void print(vector<ll>& v) {
    cout << "printing array ---> \n";
    for (auto it : v) {
        cout << it << " ";
    }
    cout << "\n";
}

ll n;
vector<vector<ll>> grid;

void solve() {
    ll n, W;
    cin >> n >> W;

    vector<ll> v(n);
    vector<ll> time(n);
    for (ll i = 0; i < n; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        v[i] = a * b;
        time[i] = c;
    }

    vector<vector<ll>> dp(n + 1, vector<ll>(W + 1));

    for (int i = n - 1; i >= 0; i--) {
        for (ll j = 0; j <= W; j++) {
            ll ans = 0;
            if (j >= time[i]) {
                ll opt1 = v[i] + dp[i + 1][j - time[i]];
                ans = max(ans, opt1);
            }
            ll opt2 = dp[i + 1][j];
            ans = max(ans, opt2);
            dp[i][j] = ans;
        }
    }

    cout << dp[0][W] << "\n";
}

signed main() {
    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
