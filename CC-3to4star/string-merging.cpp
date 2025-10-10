/**

For a string S, let's define a function F(S) as the minimum number of blocks consisting of consecutive identical characters in S. In other words, F(S) is equal to 1 plus the number of valid indices i such that Si ≠ Si+1.

You are given two strings A and B with lengths N and M respectively. You should merge these two strings into one string C with length N+M. Specifically, each character of C should come either from A or B; all characters from A should be in the same relative order in C as in A and all characters from B should be in the same relative order in C as in B.

Compute the minimum possible value of F(C).

Input
The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
The first line of each test case contains two space-separated integers N and M.
The second line contains a single string A with length N.
The third line contains a single string B with length M.
Output
For each test case, print a single line containing one integer — the minimum possible value of F(C).

Constraints
1 ≤ T ≤ 100
1 ≤ N, M ≤ 5,000
1 ≤ sum of N in all test cases ≤ 5,000
1 ≤ sum of M in all test cases ≤ 5,000
strings A, B consist only of lowercase English letters
 * problem: String Merge with Minimum Blocks
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

ll n, m;
string A, B;
ll dp[5001][5001][2];

void solve() {
    cin >> n >> m;
    cin >> A >> B;

    // Initialize DP table with infinity
    for (ll i = 0; i <= n; i++) {
        for (ll j = 0; j <= m; j++) {
            dp[i][j][0] = dp[i][j][1] = inf;
        }
    }

    // Base case: both strings exhausted
    dp[n][m][0] = dp[n][m][1] = 0;

    // Fill DP table backwards
    for (ll i = n; i >= 0; i--) {
        for (ll j = m; j >= 0; j--) {
            if (i == n && j == m) continue; // Already initialized

            // When only B is exhausted (j == m), must take from A
            if (j == m && i < n) {
                // First character from A
                if (i == 0 && j == 0) {
                    dp[i][j][0] = 1 + dp[i + 1][j][0];
                } else {
                    // Previous was from A (k=0)
                    char last_char = (i > 0) ? A[i - 1] : '\0';
                    if (i > 0 && A[i] == last_char) {
                        dp[i][j][0] = dp[i + 1][j][0];
                    } else {
                        dp[i][j][0] = 1 + dp[i + 1][j][0];
                    }
                    
                    // Previous was from B (k=1)
                    last_char = (j > 0) ? B[j - 1] : '\0';
                    if (j > 0 && A[i] == last_char) {
                        dp[i][j][1] = dp[i + 1][j][0];
                    } else {
                        dp[i][j][1] = 1 + dp[i + 1][j][0];
                    }
                }
                continue;
            }

            // When only A is exhausted (i == n), must take from B
            if (i == n && j < m) {
                // First character from B
                if (i == 0 && j == 0) {
                    dp[i][j][1] = 1 + dp[i][j + 1][1];
                } else {
                    // Previous was from A (k=0)
                    char last_char = (i > 0) ? A[i - 1] : '\0';
                    if (i > 0 && B[j] == last_char) {
                        dp[i][j][0] = dp[i][j + 1][1];
                    } else {
                        dp[i][j][0] = 1 + dp[i][j + 1][1];
                    }
                    
                    // Previous was from B (k=1)
                    last_char = (j > 0) ? B[j - 1] : '\0';
                    if (j > 0 && B[j] == last_char) {
                        dp[i][j][1] = dp[i][j + 1][1];
                    } else {
                        dp[i][j][1] = 1 + dp[i][j + 1][1];
                    }
                }
                continue;
            }

            // Both strings have characters remaining
            for (ll k = 0; k < 2; k++) {
                if (i == 0 && j == 0) {
                    // Starting position - pick first character
                    ll ans = min(1 + dp[1][0][0], 1 + dp[0][1][1]);
                    dp[i][j][k] = ans;
                    continue;
                }

                ll ans = inf;
                char last_char = (k == 0) ? A[i - 1] : B[j - 1];

                // Option 1: Take from A
                if (i < n) {
                    if (A[i] == last_char) {
                        ans = min(ans, dp[i + 1][j][0]);
                    } else {
                        ans = min(ans, 1 + dp[i + 1][j][0]);
                    }
                }

                // Option 2: Take from B
                if (j < m) {
                    if (B[j] == last_char) {
                        ans = min(ans, dp[i][j + 1][1]);
                    } else {
                        ans = min(ans, 1 + dp[i][j + 1][1]);
                    }
                }

                dp[i][j][k] = ans;
            }
        }
    }
    
    // Answer: start from position 0,0 and take minimum of starting with A or B
    cout << min(dp[0][0][0], dp[0][0][1]) << "\n";
}

signed main() {
    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
