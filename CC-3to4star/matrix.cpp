/**
 * problem: Matrix

 You are given a matrix A that consists of N rows and M columns. Every number in the matrix is either zero or one. Calculate the number of such triples (i, j, h) where for all the pairs (x, y), where both x and y belong to [1; h] if y >= x, A[i+x-1][j+y-1] equals to one. Of course, the square (i, j, i+h-1, j+h-1) should be inside of this matrix. In other words, we're asking you to calculate the amount of square submatrices of a given matrix which have ones on and above their main diagonal.

Input
The first line of the input consists of two integers - N and M.
The following N lines describe the matrix. Each line consists of M characters that are either zero or one.

Output
Output should consist of a single integer - the answer to the problem.

Example
Input:
2 3
011
111
Output:
6

Key insights: The insight to precompute the up array, representing consecutive 1s going upwards, was crucial for achieving the optimal 
O
(
N
∗
M
)
O(N∗M) solution. This emphasizes the importance of careful observation and looking for patterns in the input data.
The realization that the size of a valid square at (i, j) is limited by both the square at (i-1, j-1) and the consecutive 1s going up (up[i][j]) is key to the DP recurrence.leetcode
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

void print(vvl& v) {
    cout << "printing array-->\n";
    for (auto it : v) {
        for (auto x : it) {
            cout << x << " ";
        }
        cout << "\n";
    }
}

ll n, m;
vvl mat;
vvl pref;

ll getPrefixSum(ll col, ll startrow, ll endrow) {
    if (startrow > 0)
        return pref[endrow][col] - pref[startrow - 1][col];
    else
        return pref[endrow][col];
}

void solve() {
    cin >> n >> m;
    mat.assign(n, vl(m));
    pref.assign(n, vl(m));

    for (ll i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (ll j = 0; j < m; j++) {
            mat[i][j] = s[j] - '0';
        }
    }
    // print(mat);
    for (ll j = 0; j < m; j++) {
        for (ll i = 0; i < n; i++) {
            pref[i][j] = mat[i][j] + (i > 0 ? pref[i - 1][j] : 0);
        }
    }

    // Precompute: up[i][j] = number of consecutive 1s going up from (i,j)
    ll result = 0;
    vector<vector<int>> up(n, vector<int>(m));
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (mat[i][j] == 1) {
                up[i][j] = (i > 0 ? up[i-1][j] : 0) + 1;
            } else {
                up[i][j] = 0;
            }
        }
    }

    // Now DP
    vector<vector<int>> dp(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 0) {
                dp[i][j] = 0;
            } else if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                // Maximum square is limited by:
                // 1. The square at (i-1, j-1)
                // 2. The consecutive 1s going up in column j
                dp[i][j] = min(dp[i-1][j-1] + 1, up[i][j]);
            }
            result += dp[i][j];
        }
    }
    cout << result << "\n";
}

signed main() {
    ll t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
