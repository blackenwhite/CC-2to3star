/**
 * problem: https://www.codechef.com/practice/course/3to4stars/LP3TO401/problems/COSTEMP?tab=statement
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

ll n, m;

ll dirs[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

vector<vector<ll>> adj;
vector<ll> subtree_sz;
vector<ll> dp;

void print(vector<ll>& v) {
    cout << "printing array ---> \n";
    for (auto it : v) {
        cout << it << " ";
    }
    cout << "\n";
}

void dfs(ll node, ll par) {
    subtree_sz[node] = 1;
    for (auto it : adj[node]) {
        if (it != par) {
            dfs(it, node);
            subtree_sz[node] += subtree_sz[it];
            dp[node] += dp[it] + subtree_sz[it];
        }
    }
}

void reroot(ll node, ll par) {
    for (auto it : adj[node]) {
        if (it != par) {
            dp[it] = dp[node] + n - 2 * subtree_sz[it];
            reroot(it, node);
        }
    }
}

void solve() {
    cin >> n;
    adj.resize(n);
    subtree_sz.resize(n);
    dp.resize(n);

    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, -1);

    // after the first dfs we have the inDP for each node; however after this point we need only
    // dp[0], basically the root considering which we have done the first dfs. Now we start
    // re-rooting

    reroot(0, -1);

    for (auto it : dp) {
        cout << it << " ";
    }
    cout << "\n";
}

signed main() {
    ll t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
