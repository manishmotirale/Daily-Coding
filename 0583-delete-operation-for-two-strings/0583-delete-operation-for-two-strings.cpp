class Solution {
public:
    int longestCommonSubsequenceTab(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (text1[i - 1] == text2[j - 1]) {#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Problem Statement: Given two strings str1 and str2, we need to find the
// minimum number of deletions required to convert str1 to str2.

// Tabulation: TC O(n * m), SC O(n * m)
int longestCommonSubsequenceTab(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][m];
}

int minDistance(string word1, string word2) {
    int w1 = word1.size() - longestCommonSubsequenceTab(word1, word2);
    int w2 = word2.size() - longestCommonSubsequenceTab(word1, word2);

    return w1 + w2;
}

// Space Optimized: TC O(n * m), SC O(m)
int minDistanceSpaceOpt(string word1, string word2) {
    int n = word1.size();
    int m = word2.size();

    vector<int> prev(m + 1, 0);
    vector<int> curr(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        curr[0] = 0;

        for (int j = 1; j <= m; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                curr[j] = 1 + prev[j - 1];
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }

        prev = curr;
    }

    int lcsLength = prev[m];
    return (n - lcsLength) + (m - lcsLength);
}

int main() {
    string str1 = "heap";
    string str2 = "pea";

    cout << "Minimum number of deletions required to convert str1 to str2 "
            "(Tabulation): "
         << minDistance(str1, str2) << endl;

    cout << "Minimum number of deletions required to convert str1 to str2 "
            "(Space Optimized): "
         << minDistanceSpaceOpt(str1, str2) << endl;

    return 0;
}
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[n][m];
    }
    int minDistance(string word1, string word2) {
        int w1 = word1.size() - longestCommonSubsequenceTab(word1, word2);
        int w2 = word2.size() - longestCommonSubsequenceTab(word1, word2);

        return w1 + w2;
    }
};
