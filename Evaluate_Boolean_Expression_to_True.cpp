#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Evaluate Boolean Expression to True (Partition DP)

// Problem Statement:
// Given a Boolean expression containing T, F, and operators &, |, ^, count the
// number of ways to parenthesize the expression so that the final result is
// True.

// RECURSION => TC: O(2^N) SC: O(N)
int solveRec(int i, int j, int isTrue, string &s) {
    if (i > j)
        return 0;

    if (i == j) {
        if (isTrue == 1)
            return s[i] == 'T';
        else
            return s[i] == 'F';
    }

    int ways = 0;

    for (int k = i + 1; k <= j - 1; k += 2) {
        int lT = solveRec(i, k - 1, 1, s);
        int lF = solveRec(i, k - 1, 0, s);
        int rT = solveRec(k + 1, j, 1, s);
        int rF = solveRec(k + 1, j, 0, s);

        if (s[k] == '&') {
            if (isTrue)
                ways += rT * lT;
            else
                ways += (rT * lF) + (rF * lT) + (rF * lF);
        } else if (s[k] == '|') {
            if (isTrue)
                ways += (rT * lT) + (lT * rF) + (lF * rT);
            else
                ways += (rF * lF);
        } else {
            if (isTrue)
                ways += (rT * lF) + (rF * lT);
            else
                ways += (rT * lT) + (rF * lF);
        }
    }

    return ways;
}

int countWaysRec(string &s) {
    int n = s.size();

    return solveRec(0, n - 1, 1, s);
}

// MEMOIZATION => TC: O(N*N*2) SC: O(N*N*2) + O(N)
int solveMemo(int i, int j, int isTrue, string &s,
              vector<vector<vector<int>>> &dp) {
    if (i > j)
        return 0;

    if (i == j) {
        if (isTrue == 1)
            return s[i] == 'T';
        else
            return s[i] == 'F';
    }

    int ways = 0;

    if (dp[i][j][isTrue] != -1)
        return dp[i][j][isTrue];

    for (int k = i + 1; k <= j - 1; k += 2) {
        int lT = solveMemo(i, k - 1, 1, s, dp);
        int lF = solveMemo(i, k - 1, 0, s, dp);
        int rT = solveMemo(k + 1, j, 1, s, dp);
        int rF = solveMemo(k + 1, j, 0, s, dp);

        if (s[k] == '&') {
            if (isTrue)
                ways += rT * lT;
            else
                ways += (rT * lF) + (rF * lT) + (rF * lF);
        } else if (s[k] == '|') {
            if (isTrue)
                ways += (rT * lT) + (lT * rF) + (lF * rT);
            else
                ways += (rF * lF);
        } else {
            if (isTrue)
                ways += (rT * lF) + (rF * lT);
            else
                ways += (rT * lT) + (rF * lF);
        }
    }

    return dp[i][j][isTrue] = ways;
}

int countWaysMemo(string &s) {
    int n = s.size();

    vector<vector<vector<int>>> dp(n,
                                   vector<vector<int>>(n, vector<int>(2, -1)));

    return solveMemo(0, n - 1, 1, s, dp);
}

// TABULATION => TC: O(N*N*2) SC: O(N*N*2)
int countWaysTab(string &s) {
    int n = s.size();

    vector<vector<vector<int>>> dp(n,
                                   vector<vector<int>>(n, vector<int>(2, 0)));

    // Base case
    for (int i = 0; i < n; i++) {
        dp[i][i][1] = s[i] == 'T';
        dp[i][i][0] = s[i] == 'F';
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            for (int isTrue = 0; isTrue <= 1; isTrue++) {
                int ways = 0;
                for (int k = i + 1; k <= j - 1; k += 2) {

                    int lT = dp[i][k - 1][1];
                    int lF = dp[i][k - 1][0];
                    int rT = dp[k + 1][j][1];
                    int rF = dp[k + 1][j][0];

                    if (s[k] == '&') {
                        if (isTrue)
                            ways += rT * lT;
                        else
                            ways += (rT * lF) + (rF * lT) + (rF * lF);
                    } else if (s[k] == '|') {
                        if (isTrue)
                            ways += (rT * lT) + (lT * rF) + (lF * rT);
                        else
                            ways += (rF * lF);
                    } else {
                        if (isTrue)
                            ways += (rT * lF) + (rF * lT);
                        else
                            ways += (rT * lT) + (rF * lF);
                    }
                }
                dp[i][j][isTrue] = ways;
            }
        }
    }
    return dp[0][n - 1][1];
}

int main() {
    string s = "T|F&T^F";

    cout << "Number of ways to parenthesize the expression so that the final "
            "result is True (Recursion): "
         << countWaysRec(s) << endl;

    cout << "Number of ways to parenthesize the expression so that the final "
            "result is True (Memoization): "
         << countWaysMemo(s) << endl;

    cout << "Number of ways to parenthesize the expression so that the final "
            "result is True (Tabulation): "
         << countWaysTab(s) << endl;

    return 0;
}

// Meaning of lT, lF, rT, rF

// | Variable | Meaning                                            |
// | -------- | -------------------------------------------------- |
// | `lT`     | Number of ways left expression evaluates to True   |
// | `lF`     | Number of ways left expression evaluates to False  |
// | `rT`     | Number of ways right expression evaluates to True  |
// | `rF`     | Number of ways right expression evaluates to False |

// Operator combinations:

// | Operator | True condition          | False condition         |
// | -------- | ----------------------- | ----------------------- |
// | `&`      | `lT * rT`               | `lT*rF + lF*rT + lF*rF` |
// | `\\|`    | `lT*rT + lT*rF + lF*rT` | `lF*rF`                 |
// | `^`      | `lT*rF + lF*rT`         | `lT*rT + lF*rF`         |

// Remember: We calculate both True and False ways for left and right partitions
// because each operator has different combination rules.
