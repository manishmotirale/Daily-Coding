#include <iostream>
#include <vector>
using namespace std;

// Problem Statement: Given a string s, find the length of the longest
// palindromic subsequence in s. A subsequence is a sequence that can be derived
// from another sequence by deleting some or no elements without changing the
// order of the remaining elements.

// Change from th LCS => Just need to reverse the given string and follow LCS
// code

// Tabulation => TC: O(n * m), SC: O(n * m)
int longestPalinSubseq(string &s) {
    int n = s.size();

    string s1 = s;
    reverse(s1.begin(), s1.end());

    int m = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;

    for (int j = 0; j <= m; j++)
        dp[0][j] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            if (s[i - 1] == s1[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}
