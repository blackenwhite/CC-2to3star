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

ll n;

void solve() {
    cin >> n;
    vector<ll> v(n);
    v[0] = 3;
    ll sum = 3;
    for (ll i = 1; i < n; i++) {
        if ((sum + 3) % 9 == 0) {
            v[i] = 9;
            sum += 9;
        } else {
            v[i] = 3;
            sum += 3;
        }
    }
    for (ll i = 0; i < n; i++) {
        cout << v[i];
    }
    cout << "\n";
}

signed main() {
    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
