#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Problem Statement: Wildcard Matching
// Given a string s and a pattern p, determine whether the pattern matches the
// entire string.
// - ? matches any single character.
// - * matches any sequence of characters, including an empty sequence.
// Return true if the complete string matches; otherwise, return false.

// Recursion => TC: O(2^m),  SC: O(m+n)
bool solveRec(string &txt, string &pat, int i, int j) {
    if (i == 0 && j == 0)
        return true;
    if (j == 0)
        return false;

    if (i == 0) {
        for (int k = 0; k < j; k++)
            if (pat[k] != '*')
                return false;
        return true;
    }

    if (txt[i - 1] == pat[j - 1] || pat[j - 1] == '?')
        return solveRec(txt, pat, i - 1, j - 1);

    if (pat[j - 1] == '*')
        return solveRec(txt, pat, i, j - 1) || solveRec(txt, pat, i - 1, j);

    return false;
}

bool wildCardRec(string &txt, string &pat) {
    return solveRec(txt, pat, txt.size(), pat.size());
}

// Memoization => TC: O(m*n), SC: O(m*n)
bool solveMemo(string &txt, string &pat, int i, int j,
               vector<vector<int>> &dp) {
    if (i == 0 && j == 0)
        return true;
    if (j == 0)
        return false;

    if (i == 0) {
        for (int k = 0; k < j; k++)
            if (pat[k] != '*')
                return false;
        return true;
    }

    if (dp[i][j] != -1)
        return dp[i][j];

    if (txt[i - 1] == pat[j - 1] || pat[j - 1] == '?')
        return dp[i][j] = solveMemo(txt, pat, i - 1, j - 1, dp);

    if (pat[j - 1] == '*')
        return dp[i][j] = solveMemo(txt, pat, i, j - 1, dp) ||
                          solveMemo(txt, pat, i - 1, j, dp);

    return dp[i][j] = false;
}

bool wildCardMemo(string &txt, string &pat) {
    int n = txt.size(), m = pat.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return solveMemo(txt, pat, n, m, dp);
}

// Tabulation => TC: O(m*n), SC: O(m*n)
bool wildCardTab(string &txt, string &pat) {
    int n = txt.size(), m = pat.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    dp[0][0] = true;

    for (int j = 1; j <= m; j++)
        dp[0][j] = dp[0][j - 1] && pat[j - 1] == '*';

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (txt[i - 1] == pat[j - 1] || pat[j - 1] == '?')
                dp[i][j] = dp[i - 1][j - 1];
            else if (pat[j - 1] == '*')
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
        }
    }

    return dp[n][m];
}

// Space Optimization => TC: O(m*n), SC: O(m)
bool wildCardSpace(string &txt, string &pat) {
    int n = txt.size(), m = pat.size();
    vector<bool> prev(m + 1, false), curr(m + 1, false);

    prev[0] = true;
    for (int j = 1; j <= m; j++)
        prev[j] = prev[j - 1] && pat[j - 1] == '*';

    for (int i = 1; i <= n; i++) {
        curr[0] = false;

        for (int j = 1; j <= m; j++) {
            if (txt[i - 1] == pat[j - 1] || pat[j - 1] == '?')
                curr[j] = prev[j - 1];
            else if (pat[j - 1] == '*')
                curr[j] = prev[j] || curr[j - 1];
            else
                curr[j] = false;
        }

        prev = curr;
    }

    return prev[m];
}

int main() {
    string txt = "aa";
    string pat = "a*";

    cout << "Wildcard Matching (Recursive): " << wildCardRec(txt, pat) << endl;

    cout << "Wildcard Matching (Memoization): " << wildCardMemo(txt, pat)
         << endl;

    cout << "Wildcard Matching (Tabulation): " << wildCardTab(txt, pat) << endl;

    cout << "Wildcard Matching (Space Optimization): "
         << wildCardSpace(txt, pat) << endl;

    return 0;
}
