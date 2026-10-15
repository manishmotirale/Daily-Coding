#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Problem Statement: Given two strings str1 and str2, return the shortest
// string that has both str1 and str2 as subsequences. If there are multiple
// valid strings, return any of them.

// Tabulation => TC: O(n * m), SC: O(n * m)
string shortestCommonSupersequence(string str1, string str2) {
    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Base cases: LCS with an empty string
    for (int i = 0; i <= n; i++) {
        // When one of the strings is empty, the LCS is 0
        dp[i][0] = 0;
    }

    for (int j = 0; j <= m; j++) {
        dp[0][j] = 0;
    }

    // Build LCS DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Build the shortest common supersequence
    string ans = "";
    int i = n, j = m;

    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            ans += str1[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) { // upward
            ans += str1[i - 1];
            i--;
        } else { // leftward
            ans += str2[j - 1];
            j--;
        }
    }

    // Add remaining characters
    while (i > 0) {
        ans += str1[i - 1];
        i--;
    }
    while (j > 0) {
        ans += str2[j - 1];
        j--;
    }

    reverse(ans.begin(), ans.end());

    return ans;
}


// Length of the shortest common supersequence can be calculated as:
// SCS Length = m + n - LCS Length

// Tabulation => TC: O(n * m), SC: O(n * m)
int longestCommonSubsequenceTab(string s1, string s2) {
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= m; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][m];
}

int minSuperSeq(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();

    return m + n - longestCommonSubsequenceTab(s1, s2);
}

// Two Vectors Space Optimization
// TC: O(n * m), SC: O(n + m)
int minSuperSeqSpaceOpt(string s1, string s2) {
    int n = s1.size();
    int m = s2.size();

    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        curr[0] = 0;

        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = 1 + prev[j - 1];
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }

        prev = curr;
    }

    return n + m - prev[m];
}

int main() {
    string str1 = "abac";
    string str2 = "cab";

    cout << "Shortest Common Supersequence (Tabulation): "
         << shortestCommonSupersequence(str1, str2) << endl;
    cout << "Shortest Common Supersequence (Space Optimized): "
         << shortestCommonSupersequenceSpaceOpt(str1, str2) << endl;

    cout << "Length of Shortest Common Supersequence (Tabulation): "
         << minSuperSeq(str1, str2) << endl;
    cout << "Length of Shortest Common Supersequence (Space Optimized): "
         << minSuperSeqSpaceOpt(str1, str2) << endl;

    return 0;
}
