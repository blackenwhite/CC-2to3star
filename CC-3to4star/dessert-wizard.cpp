/*
It's finally summer in Chefland! So our chef is looking forward to prepare some of the best "beat-the-heat" dishes to attract more customers. He summons the Wizard of Dessert to help him with one such dish.

The wizard provides the chef with a sequence of N ingredients where the ith ingredient has a delish value of D[i]. The preparation of the dish takes place in two phases.

Phase 1 : The chef chooses two indices i and j and adds the ingredients i, i+1, ..., j to his dish. He also finds the sum of the delish value in this range i.e D[i] + D[i+1] + ... + D[j].

Phase 2 : The chef chooses two more indices k and l and adds the ingredients k, k+1, ..., l to his dish. He also finds the sum of the delish value in this range i.e D[k] + D[k+1] + ... + D[l].

Note that 1 ≤ i ≤ j < k ≤ l ≤ N.


The total delish value of the dish is determined by the absolute difference between the values obtained in the two phases. Obviously, the chef wants to maximize the total delish value for his dish. So, he hires you to help him.

Input
First line of input contains an integer
T
denoting the number of test cases. For each test case, the first line contains an integer
N
denoting the number of ingredients. The next line contains
N
space separated integers where the
ith
integer represents the delish value
D[i]
of the
ith
ingredient.
Output
Print the maximum delish value of the dish that the chef can get.

Constraints
1 ≤ T ≤ 50
2 ≤ N ≤ 10000
-1000000000 (−109) ≤ D[i] ≤ 1000000000 (109)

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
using vl = vector<ll>;

template <typename T>
class LazySGT {
   private:
    const ll sz;
    vector<T> tree;
    vector<T> lazy;

    void build(int v, int l, int r, const vector<T>& a) {
        if (l == r) {
            tree[v] = a[r];
            return;
        }

        ll m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }

    /** applies lazy update to tree[v], places update at lazy[v] */
    void apply(int v, int len, const T mult) {
        tree[v] = (tree[v] * mult) % mod;
        lazy[v] = (lazy[v] * mult) % mod;
    }

    T merge(T a, T b) { return (a + b) % mod; }

    void push_down(int v, int l, int r) {
        int m = (l + r) / 2;
        apply(2 * v, m - l + 1, lazy[v]);
        apply(2 * v + 1, r - m, lazy[v]);
        lazy[v] = 1;
    }

    void range_update(int v, int l, int r, int ql, int qr, const T& x) {
        if (qr < l || ql > r) return;
        if (l >= ql && r <= qr) {
            apply(v, r - l + 1, x);
            return;
        }
        push_down(v, l, r);
        int m = (l + r) / 2;
        range_update(2 * v, l, m, ql, qr, x);
        range_update(2 * v + 1, m + 1, r, ql, qr, x);
        tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }

    T range_query(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        if (l >= ql && r <= qr) return tree[v];
        push_down(v, l, r);
        int m = (l + r) / 2;
        return merge(range_query(2 * v, l, m, ql, qr), range_query(2 * v + 1, m + 1, r, ql, qr));
    }

   public:
    LazySGT(const vector<T>& a) : sz(a.size()), tree(4 * sz), lazy(4 * sz, 1) {
        build(1, 0, sz - 1, a);
    }

    void range_update(int ql, int qr, T add) { range_update(1, 0, sz - 1, ql, qr, add); }

    T range_sum(int ql, int qr) { return range_query(1, 0, sz - 1, ql, qr); }

    void printTree() {
        cout << "Printing tree ---> \n";
        for (ll i = 1; i < tree.size(); i++) {
            cout << tree[i] << "(" << lazy[i] << ")" << ", ";
        }
        cout << "\n";
    }
};

// ----- end of utilities ------ //

ll n;
vl arr;

vl minDpRight;  // minDpRight[i] = min({minDpRight[i], minDpRight[i+1], .... })
vl maxDPRight;

ll computeOpt1() {
    ll ans = -inf;
    ll minCur = arr[n - 1];  // minCur:= minimum contiguous sum from i to the right
    minDpRight[n - 1] = arr[n - 1];
    for (ll i = n - 2; i >= 0; i--) {
        ll temp = minCur + arr[i];
        minCur = min(temp, arr[i]);
        minDpRight[i] = min(minCur, minDpRight[i + 1]);
    }

    ll maxCur = -inf;

    for (ll i = 0; i < n - 1; i++) {
        ll temp = maxCur + arr[i];
        maxCur = max(temp, arr[i]);
        ll tempAns = maxCur - minDpRight[i + 1];
        ans = max(ans, tempAns);
    }

    return ans;
}

ll computeOpt2() {
    ll ans = -inf;
    ll maxCur = arr[n - 1];
    maxDPRight[n - 1] = maxCur;

    for (ll i = n - 2; i >= 0; i--) {
        ll temp = maxCur + arr[i];
        maxCur = max(temp, arr[i]);
        maxDPRight[i] = max(maxCur, maxDPRight[i + 1]);
    }

    ll minCur = inf;
    for (ll i = 0; i < n - 1; i++) {
        minCur = min(minCur + arr[i], arr[i]);
        ll tempAns = abs(minCur - maxDPRight[i + 1]);
        ans = max(ans, tempAns);
    }

    return ans;
}

void solve() {
    cin >> n;
    arr.resize(n);
    minDpRight.assign(n, inf);
    maxDPRight.assign(n, -inf);
    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
    }

    ll ans = -inf;

    // compute left max dp
    // leftMaxDP[j] := max subset sum for some i,j (i<=j) w
    ll opt1 = computeOpt1();
    ll opt2 = computeOpt2();

    cout << max(opt1, opt2) << "\n";
}

signed main() {
    ll t;
    cin >> t;
    while (t--) {
        solve();
    }
}
