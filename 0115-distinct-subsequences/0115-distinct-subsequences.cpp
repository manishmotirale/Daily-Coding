#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Problem Statement:Given two strings s and t, count the number of ways to
// obtain t as a subsequence of s by deleting zero or more characters without
// changing the relative order of the remaining characters.

// Recursion => TC: O(2^m * 2^nn)
int solveRec(string &s1, string &s2, int i, int j) {
    if (j < 0)
        return 1;

    if (i < 0)
        return 0;

    if (s1[i] == s2[j]) {
        int include = solveRec(s1, s2, i - 1, j - 1);
        int exclude = solveRec(s1, s2, i - 1, j);

        return include + exclude;
    }

    return solveRec(s1, s2, i - 1, j);
}

int countWaysRecursion(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();

    return solveRec(s1, s2, n - 1, m - 1);
}

// Memoization => TC: O(m*n) SC: O(m*n) + O(n)
int solveMemo(string &s1, string &s2, int i, int j, vector<vector<int>> &dp) {
    if (j < 0)
        return 1;

    if (i < 0)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (s1[i] == s2[j]) {
        int include = solveMemo(s1, s2, i - 1, j - 1, dp);
        int exclude = solveMemo(s1, s2, i - 1, j, dp);

        return dp[i][j] = include + exclude;
    }

    return dp[i][j] = solveMemo(s1, s2, i - 1, j, dp);
}

int countWaysMemoization(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveMemo(s1, s2, n - 1, m - 1, dp);
}

// Tabulation => TC: O(m*n) SC: O(m*n)
int countWaysTabulation(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();

    vector<vector<double>> dp(n, vector<double>(m, 0));

    for (int i = 0; i <= n; i++)
        dp[i][0] = 1;

    for (int j = 0; j <= m; j++)
        dp[0][j] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return (int)dp[n][m];
}

// Space Optimization => TC: O(m*n) SC: O(n)
int countWaysSpaceOpti(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();

    vector<double> prev(m + 1, 0);
    vector<double> curr(m + 1, 0);

    // Empty target can be formed in one way
    prev[0] = 1;
    curr[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1] + prev[j];
            } else {
                curr[j] = prev[j];
            }
        }

        prev = curr;
    }

    return (int)prev[m];
}

// Two Vector => One Vector => Space Optimization => TC: O(m*n) SC: O(n)X
int countWaysSpaceOptiOneVector(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();

    vector<double> prev(m + 1, 0);

    // Empty target can be formed in one way
    prev[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            if (s1[i - 1] == s2[j - 1]) {
                prev[j] = prev[j - 1] + prev[j];
            }
        }
    }

    return (int)prev[m];
}

int main() {
    string s1 = "rabbbit";
    string s2 = "rabbit";

    cout << "Count of distinct subsequences (Recursion): "
         << countWaysRecursion(s1, s2) << endl;

    cout << "Count of distinct subsequences (Memoization): "
         << countWaysMemoization(s1, s2) << endl;

    cout << "Count of distinct subsequences (Tabulation): "
         << countWaysTabulation(s1, s2) << endl;

    cout << "Count of distinct subsequences (Space Optimization): "
         << countWaysSpaceOpti(s1, s2) << endl;

    cout << "Count of distinct subsequences (Space Optimization One Vector): "
         << countWaysSpaceOptiOneVector(s1, s2) << endl;

    return 0;
}
