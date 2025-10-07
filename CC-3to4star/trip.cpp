/*
You are starting out on a long (really long) trip. On the way, there are N gas stations, the locations of which are given as a_1,a_2,...,a_N. Initially you are located at the gas station at a_1, and your destination is at location a_N. Your car can only store enough fuel to travel atmost M units without refilling. You can stop at any station and refill the car by any amount. Now you wish to plan your trip such that the number of intermediate stops needed to reach the destination is minimum, and also how many ways are there to plan your trip accordingly.

Input :
The first line two space seperated integers N and M. N lines follow, and the ith line has the value a_i (0 <= a_i <= 1000000000). The input will be such that a solution will always exist.
Output :
Output two space seperated integers : The least number of stops, and the number of ways to plan the trip which uses the least number of stops. Output this value modulo 1000000007.
Constraints :
2 <= N <= 1000000
1 <= M <= 1000
a_1 < a_2 < .. < a_N
*/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
const int MOD = 1e9 + 7;

struct Node {
    long long val; // dp value
    long long ways; // number of ways with that dp
};

struct SegTree {
    int n;
    vector<Node> tree;

    SegTree(int n) {
        this->n = n;
        tree.assign(4 * n, {INF, 0});
    }

    Node merge(Node a, Node b) {
        if (a.val < b.val) return a;
        if (b.val < a.val) return b;
        return {a.val, (a.ways + b.ways) % MOD};
    }

    void update(int idx, Node val, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (idx <= tm) update(idx, val, 2 * v, tl, tm);
        else update(idx, val, 2 * v + 1, tm + 1, tr);
        tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }

    void update(int idx, Node val) {
        update(idx, val, 1, 0, n - 1);
    }

    Node query(int l, int r, int v, int tl, int tr) {
        if (l > r) return {INF, 0};
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return merge(
            query(l, min(r, tm), 2 * v, tl, tm),
            query(max(l, tm + 1), r, 2 * v + 1, tm + 1, tr)
        );
    }

    Node query(int l, int r) {
        return query(l, r, 1, 0, n - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long M;
    cin >> N >> M;

    vector<long long> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    // DP arrays
    vector<long long> dp(N, INF);
    vector<long long> ways(N, 0);

    dp[0] = 0;
    ways[0] = 1;

    SegTree st(N);
    st.update(0, {0, 1});

    for (int i = 1; i < N; i++) {
        // find leftmost j such that a[i] - a[j] <= M
        int L = lower_bound(a.begin(), a.end(), a[i] - M) - a.begin();
        int R = i - 1;

        Node q = st.query(L, R);
        if (q.val != INF) {
            dp[i] = q.val + 1;
            ways[i] = q.ways % MOD;
        }

        st.update(i, {dp[i], ways[i]});
    }

    cout << dp[N - 1]-1 << " " << ways[N - 1] % MOD << "\n";
    return 0;
}
