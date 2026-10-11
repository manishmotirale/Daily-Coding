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
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            ans += str1[i - 1];
            i--;
        } else {
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

int main() {
    string str1 = "abac";
    string str2 = "cab";

    cout << "Shortest Common Supersequence: "
         << shortestCommonSupersequence(str1, str2) << endl;

    return 0;
}
