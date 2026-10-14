#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Problem Statement: Given a string s, we need to find the minimum number of
// insertions required to make the string a palindrome.

// Tabulation: TC O(n^2), SC O(n^2)
int longestPalinSubseqTab(string &s) {
    int n = s.size();

    string s1 = s;
    reverse(s1.begin(), s1.end());

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == s1[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][n];
}

int minInsertions(string s) { return s.size() - longestPalinSubseqTab(s); }

// Space Optimized: TC O(n^2), SC O(n)
int minInsertionsSpaceOpt(string &s) {
    int n = s.size();

    string s1 = s;
    reverse(s1.begin(), s1.end());

    vector<int> prev(n + 1, 0);
    vector<int> curr(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        curr[0] = 0;

        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == s1[j - 1]) {
                curr[j] = 1 + prev[j - 1];
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }

        prev = curr;
    }
    return n - prev[n];
}

int main() {
    string s = "abcaa";

    cout << "Minimum insertions (Tabulation): " << minInsertions(s) << endl;

    cout << "Minimum insertions (Space Optimized): " << minInsertionsSpaceOpt(s)
         << endl;

    return 0;
}
