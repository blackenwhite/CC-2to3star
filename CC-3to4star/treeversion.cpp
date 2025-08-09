/**
 * problem: 
You are given a rooted tree with 
N
N nodes (numbered 
1
1 through 
N
N); the root is node 
1
1. For each valid 
i
i, node 
i
i has weight 
w
i
w 
i
​
 , which is either 
0
0 or 
1
1.

We want to traverse the tree using depth first search. The order in which the nodes are visited is not uniquely defined, since we may visit the children of each node in an arbitrary order. Formally, the pseudocode of DFS-traversal is:

function DFS(node n):
	node n is visited
	for each node s (s is a son of n) in some order:
		call DFS(s)
	return
call DFS(root)
For each possible DFS-traversal of the tree, consider the sequence of weights of nodes in the order in which they are visited; each node is visited exactly once, so this sequence has length 
N
N. Calculate the number of inversions for each such sequence. The minimum of these numbers is the treeversion of our tree.

Find the treeversion of the given tree.

Input
The first line of the input contains a single integer 
T
T denoting the number of test cases. The description of 
T
T test cases follows.
The first line of each test case contains a single integer 
N
N.
The second line contains 
N
N space-separated integers 
w
1
,
w
2
,
…
,
w
N
w 
1
​
 ,w 
2
​
 ,…,w 
N
​
 .
Each of the following 
N
−
1
N−1 lines contains two space-separated integers 
x
x and 
y
y denoting that nodes 
x
x and 
y
y are connected by an edge.
Output
For each test case, print a single line containing one integer — the treeversion of the given tree.

Constraints
 
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

void print(vector<ll> &v) {
    cout << "printing array ---> \n";
    for (auto it : v) {
        cout << it << " ";
    }
    cout << "\n";
}

vector<ll> weights;
vector<ll> count0;
vector<ll> count1;
vector<vector<ll>> adj;  // adjacency list
vector<ll> dp;

void dfs(ll node, ll par) {
    if (weights[node] == 0) {
        count0[node]++;
    } else {
        count1[node]++;
    }

    for (auto it : adj[node]) {
        if (it != par) {
            dfs(it, node);
            count0[node] += count0[it];
            count1[node] += count1[it];
        }
    }
}

void dfs2(ll node, ll par) {
    vector<pii> count;  // {count0[child], count1[child]}
    for (auto it : adj[node]) {
        if (it != par) {
            dfs2(it, node);
            dp[node] += dp[it];
            count.push_back({count1[it], count0[it]});
        }
    }
    ll lateral_inversions = 0;
    ll sum1 = (weights[node] == 1) ? 1 : 0;  // sum of ones seen till now
    sort(count.begin(), count.end(), [](const pii &a, const pii &b) {
        // sorting the children greedily
        return a.ff * b.ss < a.ss * b.ff;
    });

    for (auto it : count) {
        lateral_inversions += it.ss * sum1;
        sum1 += it.ff;
    }
    dp[node] += lateral_inversions;
}

void solve() {
    weights.clear();
    count0.clear();
    count1.clear();
    adj.clear();
    dp.clear();

    cin >> n;
    weights.resize(n + 1);
    dp.resize(n + 1);
    for (ll i = 1; i <= n; i++) {
        cin >> weights[i];
    }

    count0.resize(n + 1);
    count1.resize(n + 1);

    adj.resize(n + 1);
    for (ll i = 1; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfs(1, 0);

    // print(count0);
    // print(count1);
    dfs2(1, 0);
    cout << dp[1] << "\n";
}

signed main() {
    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
