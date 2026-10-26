#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Longest Common Substring => Problem Statement: Given two strings, find the
// length of the longest common substring. Example: Input: str1 = "abcdxyz",
// str2 = "xyzabcd"

// Recursion => TC: O(2^n) SC: O(n)
int solveRec(string &s1, string &s2, int i, int j, int &maxLen) {
    if (i < 0 || j < 0) {
        return 0;
    }

    int len = 0;

    if (s1[i] == s2[j]) {
        len = 1 + solveRec(s1, s2, i - 1, j - 1, maxLen);
        maxLen = max(maxLen, len);
    }

    solveRec(s1, s2, i - 1, j, maxLen);
    solveRec(s1, s2, i, j - 1, maxLen);

    return len;
}

int longestCommonSubstringRec(string s1, string s2) {
    int n = s1.size();
    int m = s2.size();
    int maxLen = 0;

    solveRec(s1, s2, n - 1, m - 1, maxLen);

    return maxLen;
}

// Memoization => TC: O(n * m), SC: O(n * m) + O(n + m)
int solveMemo(string &s1, string &s2, int i, int j, vector<vector<int>> &dp,
              int &maxLen) {
    if (i < 0 || j < 0) {
        return 0;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    if (s1[i] == s2[j]) {
        dp[i][j] = 1 + solveMemo(s1, s2, i - 1, j - 1, dp, maxLen);
    } else {
        dp[i][j] = 0;
    }

    maxLen = max(maxLen, dp[i][j]);

    solveMemo(s1, s2, i - 1, j, dp, maxLen);
    solveMemo(s1, s2, i, j - 1, dp, maxLen);

    return dp[i][j];
}

int longestCommonSubstringMemo(string s1, string s2) {
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n, vector<int>(m, -1));
    int maxLen = 0;

    solveMemo(s1, s2, n - 1, m - 1, dp, maxLen);

    return maxLen;
}

// Tabulation => TC: O(n * m), SC: O(n * m)
int longestCommonSubstringTabulation(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int maxLen = 0;

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

                maxLen = max(maxLen, dp[i][j]);
            } else {
                dp[i][j] = 0;
            }
        }
    }

    return maxLen;
}

// Space Optimization => TC: O(n * m), SC: O(m)
int longCommSubstringSpace(string &s1, string &s2) {
    int n = s1.size(), m = s2.size();

    vector<int> prev(m + 1, 0);
    vector<int> curr(m + 1, 0);
    int maxLen = 0;

    for (int j = 0; j <= m; j++) {
        prev[j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = 1 + prev[j - 1];
                maxLen = max(maxLen, curr[j]);
            } else {
                curr[j] = 0;
            }
        }

        prev = curr;
    }

    return maxLen;
}

// Two Vectors => One Vector
// TC: O(n * m), SC: O(m)
int longCommSubstringSpaceOneVector(string &s1, string &s2) {
    int n = s1.size(), m = s2.size();

    vector<int> prev(m + 1, 0);
    int maxLen = 0;

    for (int j = 0; j <= m; j++) {
        prev[j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                prev[j] = 1 + prev[j - 1];
                maxLen = max(maxLen, prev[j]);
            } else {
                prev[j] = 0;
            }
        }
    }

    return maxLen;
}
int main() {
    string s1 = "abcdxyz";
    string s2 = "xyzabcd";

    cout << "Length of Longest Common Substring (Recursion): "
         << longestCommonSubstringRec(s1, s2) << endl;

    cout << "Length of Longest Common Substring (Memoization): "
         << longestCommonSubstringMemo(s1, s2) << endl;

    cout << "Length of Longest Common Substring (Tabulation): "
         << longestCommonSubstringTabulation(s1, s2) << endl;

    cout << "Length of Longest Common Substring (Space Optimization): "
         << longCommSubstringSpace(s1, s2) << endl;

    cout << "Length of Longest Common Substring (One Vector): "
         << longCommSubstringSpaceOneVector(s1, s2) << endl;

    return 0;
}
