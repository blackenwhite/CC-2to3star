/*
Abdullah has recently moved to Tolland. In Tolland, there are 
N
N cities (numbered 
1
1 through 
N
N) connected by 
N
−
1
N−1 bidirectional roads such that it is possible to visit any city from any other city. For each city 
i
i, there is a toll value 
T
L
i
TL 
i
​
 .

Abdullah lives in city 
X
X. He has planned a tour of Tolland lasting for 
2
N
2N days. For each 
i
i (
1
≤
i
≤
N
1≤i≤N), on the 
2
i
−
1
2i−1-th day, he travels from city 
X
X to city 
i
i, and on the 
2
i
2i-th day, he travels from city 
i
i back to city 
X
X.

In Tolland, there are also special discount coupons. For each city 
c
c and positive integer 
v
v, there is a discount coupon for city 
c
c with value 
v
v. All discount coupons may be bought anywhere in Tolland; the cost of each discount coupon is twice its value.

When travelling from any city 
i
i to any (not necessarily different) city 
j
j, Abdullah must pay a toll exactly once in each city on the path between them (including 
i
i and 
j
j); even if he passed through some cities before, he must pay the toll in these cities as well. For any city 
i
i, the toll is 
T
L
i
TL 
i
​
  when not using any discount coupons; however, if Abdullah bought some discount coupons for city 
i
i, he may use some or all of them to decrease this toll to 
m
a
x
 
(
0
,
T
L
i
−
V
)
max(0,TL 
i
​
 −V), where 
V
V is the sum of values of coupons for city 
i
i used by Abdullah. Each coupon may be used at most once per day, but they do not expire when used and the same coupon may be used on multiple days. On each day, Abdullah may use any coupons he wants, but a coupon for city 
i
i may only be used to decrease the toll in city 
i
i.

Abdullah has a travel budget: on each day, he must not spend more than 
K
K units of money on paying tolls. Before the start of the tour, he may choose to buy any number of discount coupons, for any cities and with any values (possibly different ones for different cities); the cost of coupons is not included in the budget for any day of the tour. Help Abdullah find the minimum total amount of money he must spend on discount coupons so that on each day during the tour, he will be able to stay within his budget by using the coupons he bought.

Input
The first line of the input contains a single integer 
T
T denoting the number of test cases. The description of 
T
T test cases follows.
The first line of each test case contains three space-separated integers 
N
N, 
X
X and 
K
K.
The second line contains 
N
N space-separated integers 
T
L
1
,
T
L
2
,
…
,
T
L
N
TL 
1
​
 ,TL 
2
​
 ,…,TL 
N
​
 .
Each of the next 
N
−
1
N−1 lines contains two space-separated integers 
U
U and 
V
V denoting that cities 
U
U and 
V
V are connected by a bidirectional road.
Output
For each test case, print a single line containing one integer ― the minimum amount of money Abdullah should spend on coupons.

Constraints
1
≤
T
≤
100
1≤T≤100
1
≤
N
≤
10
4
1≤N≤10 
4
 
1
≤
K
≤
10
13
1≤K≤10 
13
 
1
≤
X
,
U
,
V
≤
N
1≤X,U,V≤N
1
≤
T
L
i
≤
10
9
1≤TL 
i
​
 ≤10 
9
  for each valid 
i
i
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
const ll N = 1e5 + 5;
const ll mod = 1e9 + 7;
ll inf = 1e18;
const int nn = 20;

ll __gcd(ll a, ll b) {
    if (a == 0) return b;
    return __gcd(b % a, a);
}

ll n, X, K;
vector<ll> tl;
vector<ll> sum;
vector<ll> contri;

ll dirs[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

void print(vector<ll>& v) {
    cout << "printing array ---> \n";
    for (auto it : v) {
        cout << it << " ";
    }
    cout << "\n";
}

vector<vector<ll>> adj;  // adjacency list

void dfs1(ll node, ll par) {
    sum[node] = sum[par] + tl[node];
    contri[node] = max(0LL, sum[node] - K);
    for (auto it : adj[node]) {
        if (it != par) {
            dfs1(it, node);
            contri[node] = max(contri[node], contri[it]);  // M[u]
        }
    }
}

void dfs2(ll node, ll par, ll allocAbove, ll& ans) {
    ll need = max(0LL, contri[node] - allocAbove);
    ll r = min(tl[node], need);
    ans += r;
    ll newAllocAbove = allocAbove + r;
    for (auto it : adj[node]) {
        if (it != par) {
            dfs2(it, node, newAllocAbove, ans);
        }
    }
}

void solve() {
    cin >> n >> X >> K;
    tl.assign(n + 1, 0);
    for (ll i = 1; i <= n; i++) {
        cin >> tl[i];
    }
    adj.assign(n + 1, {});
    for (ll i = 1; i < n; i++) {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    sum.assign(n + 1, 0);
    contri.assign(n + 1, 0);
    dfs1(X, 0);

    ll ans = 0;
    dfs2(X, 0, 0, ans);
    cout << ans * 2 << "\n";
}

signed main() {
    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
