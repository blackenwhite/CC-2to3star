/*
Each palindrome can be always created from the other palindromes, if a single character is also a palindrome. For example, the string "bobseesanna" can be created by some ways:
* bobseesanna = bob + sees + anna
* bobseesanna = bob + s + ee + s + anna
* bobseesanna = b + o + b + sees + a + n + n + a
...
We want to take the value of function CountPal(s) which is the number of different ways to use the palindromes to create the string s by the above method.

Input
The string s

Output
The value of function CountPal(s), taking the modulo of 1 000 000 007 (109+7)

Limitations
0 < |s| <= 1000

*/

using ll = long long;
class Solution {
public:
    const ll mod = 1e9+7; 
    long long countWays(string s) {
        // write your code here
        ll n = s.size();
        vector<vector<bool>> pal(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) pal[i][i] = true;
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    if (len == 2)
                        pal[i][j] = true;
                    else
                        pal[i][j] = pal[i + 1][j - 1];
                }
            }
        }
    
        vector<long long> dp2(n + 1, 0);
        dp2[n] = 1;  // base case: empty suffix
        for (int i = n - 1; i >= 0; i--) {
            long long ways = 0;
            for (int j = i; j < n; j++) {
                if (pal[i][j]) {
                    ways += dp2[j + 1];
                    if (ways >= mod) ways -= mod;
                }
            }
            dp2[i] = ways;
        }
        // cout << dp2[0] << "\n";
        return dp2[0];
    }
};
