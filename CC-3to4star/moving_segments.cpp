/*
I need help with a problem:
"""N line segments (numbered 11 through NN) are placed on the xx-axis. For each valid ii, the ii-th segment starts at x=Lix=Li and ends at x=Rix=Ri.
At the time t=0t=0, all segments start moving; for each valid ii, the ii-th segment starts moving with speed ViVi. You need to assign a direction - left or right - to the movement of each segment, i.e. choose a sign for each ViVi (not necessarily the same for all segments). The resulting movement must satisfy the following condition: at the time t=1010000t=1010000, there are no two segments that touch or intersect.
Decide if it is possible to assign directions to the segments in such a way that the above condition is satisfied.
Input
* The first line of the input contains a single integer TT denoting the number of test cases. The description of TT test cases follows.
* The first line of each test case contains a single integer NN.
* NN lines follow. For each ii (1≤i≤N1≤i≤N), the ii-th of these lines contains three space-separated integers LiLi, RiRi and ViVi.
Output
For each test case, print a single line containing the string "YES" if it is possible to assign the directions in a valid way or "NO" if it is impossible.
Constraints
* 1≤T≤1001≤T≤100
* 1≤N≤1,0001≤N≤1,000
* 1≤Li<Ri≤1091≤Li<Ri≤109 for each valid ii
* 1≤Vi≤1091≤Vi≤109 for each valid ii
* the sum of NN over all test cases does not exceed 2,0002,000""" . I think this can be solved using bipartiteness of a graph. AM I correct or wrong?
*/
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct Segment {
    long long l, r, v;
};

class BipartiteChecker {
private:
    vector<vector<int>> adj;
    vector<int> color;
    int n;
    
public:
    BipartiteChecker(int size) : n(size) {
        adj.resize(n);
        color.resize(n, -1);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    bool isBipartite() {
        // Check each connected component
        for (int start = 0; start < n; start++) {
            if (color[start] == -1) {
                if (!bfsColor(start)) {
                    return false;
                }
            }
        }
        return true;
    }
    
private:
    bool bfsColor(int start) {
        queue<int> q;
        q.push(start);
        color[start] = 0;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbor : adj[node]) {
                if (color[neighbor] == -1) {
                    // Color with opposite color
                    color[neighbor] = 1 - color[node];
                    q.push(neighbor);
                } else if (color[neighbor] == color[node]) {
                    // Same color for adjacent nodes -> not bipartite
                    return false;
                }
            }
        }
        return true;
    }
};

bool segmentsIntersectAtT0(const Segment& a, const Segment& b) {
    // Two segments [a.l, a.r] and [b.l, b.r] intersect if:
    // NOT (a.r < b.l OR b.r < a.l)
    return !(a.r < b.l || b.r < a.l);
}

bool shouldAddEdge(const Segment& a, const Segment& b) {
    // Add edge if: abs(Va) == abs(Vb) AND segments intersect at t=0
    return (abs(a.v) == abs(b.v)) && segmentsIntersectAtT0(a, b);
}

bool canAssignDirections(vector<Segment>& segments) {
    int n = segments.size();
    BipartiteChecker checker(n);
    
    // Build conflict graph
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (shouldAddEdge(segments[i], segments[j])) {
                checker.addEdge(i, j);
            }
        }
    }
    
    // Check if the conflict graph is bipartite
    return checker.isBipartite();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<Segment> segments(n);
        for (int i = 0; i < n; i++) {
            cin >> segments[i].l >> segments[i].r >> segments[i].v;
        }
        
        if (canAssignDirections(segments)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
