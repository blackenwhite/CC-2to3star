/**
 * problem: Girl Friend and String Gift

 Chef's Girl Friend has given him a unique gift. She has given him a string S. Chef being a gentleman wants to return her gift in a unique way. He wants to break the string he has received into some number of substrings so that each substring is a palindrome. However he does not want break the string into too many substrings, otherwise the average size of his strings will become small. What is the minimum number of substrings in which the given string can be broken so that each substring is a palindrome.

Tips:
Refer http://en.wikipedia.org/wiki/Palindrome for the definition of a "palindrome"

Input
Input description.

The first line of the input contains an integer T denoting the number of test cases. The description of T test cases follows:
The first line of each test case contains a single integer N denoting the number of alphabets in the given string. The second line contains the given string.
Output
For each test case output a single integer the answer to the given test case. Print answer for each test case on a separate line.

Constraints
All characters in the given string are upper case English alphabets.

1 ≤ T ≤ 10
1 ≤ |S| ≤ 5000
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
using vvl = vector<vector<ll>>;
using vl = vector<ll>;
const ll N = 1e6 + 2;
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
string s;

void solve() {
    cin >> n;
    cin >> s;

    vector<vector<bool>> pal(n, vector<bool>(n, false));
    for (ll i = 0; i < n; i++) pal[i][i] = true;
    for (ll len = 2; len <= n; len++) {
        for (ll i = 0; i + len - 1 < n; i++) {
            ll j = i + len - 1;
            if (s[i] == s[j]) {
                if (len == 2)
                    pal[i][j] = true;
                else
                    pal[i][j] = pal[i + 1][j - 1];
            }
        }
    }

    vector<ll> dp(n + 1);
    dp[n] = 0;
    for (ll i = n - 1; i >= 0; i--) {
        ll ans = inf;
        for (ll j = i; j < n; j++) {
            if (pal[i][j]) {
                ll temp = 1 + dp[j + 1];
                ans = min(ans, temp);
            }
        }
        dp[i] = ans;
    }

    cout << dp[0] << "\n";
}

signed main() {
    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
