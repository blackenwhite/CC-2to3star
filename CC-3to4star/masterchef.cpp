/*
Chef loves to prepare delicious dishes. He has prepared N dishes numbered from 1 to N for this year's MasterChef contest. He has presented all the N dishes to a panel of judges. Judging panel consists of M judges numbered from 1 to M. Rating for each dish was decided by voting from all the judges. Rating for the dishes has been given by a 1-indexed array A where Ai denotes rating of the ith dish.

Some dishes prepared by chef are extraordinary delicious, but unfortunately, some are not. Chef has been given a chance to improve the total rating of his dishes. By total rating of dishes, we mean the sum of the ratings of his dishes. Each of the M judges has administrative power to remove some (zero or more) dishes from a specified range. The ith judge takes Ci rupees for removing each dish of Chef's choice from the dishes numbered from Li to Ri (both inclusive). Once a dish is removed by any of the M judges it will not be considered for calculating total rating of the dishes. Chef has spent a large portion of his money preparing mouth watering dishes and has only K rupees left for now. Now chef is worried about maximizing total rating of his dishes by dropping some of the N dishes.

Please Help chef by finding the maximum total rating he can achieve such that the total expenditure does not exceed his budget of K rupees.

Input
First line of input contains a single integer T denoting the number of test cases.
First line of each test case contains three space separated integers N, K and M denoting the number of dishes prepared by chef, chef's budget, and number of judges in judging panel respectively.
Next line of each test case contains N space separated integers where ith integer denotes the rating received by the ith dish.
Next M lines of each test case contain three space separated integers each: L, R and C, where the integers in the ith line denotes the value of Li, Ri and Ci respectively.
Output
For each test case, print a single integer in a line corresponding to the answer.

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

ll n, K, m;
vector<ll> A, L, R, C;

void solve() {
    cin >> n >> K >> m;
    A.assign(n, 0);

    for (ll i = 0; i < n; i++) {
        cin >> A[i];
    }

    // build min cost array with sweep line
    vector<multiset<ll>> add(n), deduct(n);
    for (ll i = 0; i < m; i++) {
        ll l, r, c;
        cin >> l >> r >> c;
        add[--l].insert(c);
        if (r < n) deduct[r].insert(c);
    }

    vector<ll> minCost(n, inf);
    multiset<ll> cur;
    for (ll i = 0; i < n; i++) {
        for (auto x : add[i]) cur.insert(x);
        for (auto x : deduct[i]) cur.erase(cur.find(x));
        if (!cur.empty()) minCost[i] = *cur.begin();
    }

    // rolling DP arrays
    vector<ll> next(K + 1, 0), curDp(K + 1, 0);

    for (ll i = n - 1; i >= 0; i--) {
        for (ll j = 0; j <= K; j++) {
            ll ans = A[i] + next[j]; // keep dish i
            if (j >= minCost[i] && minCost[i] <= K) {
                ans = max(ans, next[j - minCost[i]]); // remove dish i
            }
            curDp[j] = ans;
        }
        swap(curDp, next);
    }

    cout << next[K] << "\n";
}

signed main() {
    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
