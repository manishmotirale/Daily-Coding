#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Given two strings s1 and s2, find the minimum number of operations required
// to convert s1 into s2.
// The allowed operations are : -Insert a character.- Delete a character.-
//    Replace a character.Each operation costs 1

// Recursion => TC: O(3^n) SC: O(n)
int solveRec(string &s1, string &s2, int i, int j) {
    if (i < 0)
        return j + 1;
    if (j < 0)
        return i + 1;

    if (s1[i] == s2[j]) {
        return solveRec(s1, s2, i - 1, j - 1);
    }

    return 1 + min({solveRec(s1, s2, i - 1, j), solveRec(s1, s2, i, j - 1),
                    solveRec(s1, s2, i - 1, j - 1)});
}
int editDistanceRecursion(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();

    return solveRec(s1, s2, n - 1, m - 1);
}
// Memoization => TC: O(m*n) SC: O(m*n) + O(n)
int solveMemo(string &s1, string &s2, int i, int j, vector<vector<int>> &dp) {
    if (i < 0)
        return j + 1;
    if (j < 0)
        return i + 1;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (s1[i] == s2[j]) {
        return solveMemo(s1, s2, i - 1, j - 1, dp);
    }

    return dp[i][j] = 1 + min({solveMemo(s1, s2, i - 1, j, dp),
                               solveMemo(s1, s2, i, j - 1, dp),
                               solveMemo(s1, s2, i - 1, j - 1, dp)});
}
int editDistanceMemoization(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveMemo(s1, s2, n - 1, m - 1, dp);
}

// Tabulation => TC: O(m*n) SC: O(m*n)
int editDistanceTabulation(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Base cases
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;

    for (int j = 0; j <= m; j++)
        dp[0][j] = j;

    // Tabulation
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] =
                    1 + min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
            }
        }
    }

    return dp[n][m];
}

// Space Optimization => TC: O(m*n) SC: O(n)

int editDistanceSpaceOptimized(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();

    vector<int> prev(m + 1, 0);
    vector<int> curr(m + 1, 0);

    // Base case: converting empty string to s2
    for (int j = 0; j <= m; j++)
        prev[j] = j;

    for (int i = 1; i <= n; i++) {
        curr[0] = i;

        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1];
            } else {
                curr[j] = 1 + min({
                                  prev[j],     // Delete
                                  curr[j - 1], // Insert
                                  prev[j - 1]  // Replace
                              });
            }
        }

        prev = curr;
    }

    return prev[m];
}

int main() {
    string s1 = "kitten";
    string s2 = "sitting";

    cout << "Edit Distance (Recursion): " << editDistanceRecursion(s1, s2)
         << endl;

    cout << "Edit Distance (Memoization): " << editDistanceMemoization(s1, s2)
         << endl;

    cout << "Edit Distance (Tabulation): " << editDistanceTabulation(s1, s2)
         << endl;

    cout << "Edit Distance (Space Optimization): "
         << editDistanceSpaceOptimized(s1, s2) << endl;

    return 0;
}
