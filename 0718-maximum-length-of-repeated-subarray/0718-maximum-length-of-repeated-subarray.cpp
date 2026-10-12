
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Same Solution for Longest Common Substring

// Problem: Maximum Length of Repeated Subarray
// Example: nums1 = {1,2,3,2,1}
//          nums2 = {3,2,1,4,7}
// Output: 3

// 1. Recursion
// TC: O(3^(n+m)) upper bound
// SC: O(n+m) recursion stack
int solveRec(vector<int>& nums1, vector<int>& nums2, int i, int j, int& maxLen) {
    // Base Case
    if (i < 0 || j < 0) {
        return 0;
    }

    int len = 0;

    if (nums1[i] == nums2[j]) {
        len = 1 + solveRec(nums1, nums2, i - 1, j - 1, maxLen);
        maxLen = max(maxLen, len);
    }

    solveRec(nums1, nums2, i - 1, j, maxLen);
    solveRec(nums1, nums2, i, j - 1, maxLen);

    return len;
}

int findLengthRec(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();
    int maxLen = 0;

    solveRec(nums1, nums2, n - 1, m - 1, maxLen);

    return maxLen;
}

// 2. Memoization
// TC: O(n*m)
// SC: O(n*m) + O(n+m) recursion stack
int solveMemo(vector<int>& nums1, vector<int>& nums2, int i, int j, vector<vector<int>>& dp, int& maxLen) {
    // Base Case
    if (i < 0 || j < 0) {
        return 0;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    if (nums1[i] == nums2[j]) {
        dp[i][j] = 1 + solveMemo(nums1, nums2, i - 1, j - 1, dp, maxLen);
    } else {
        dp[i][j] = 0;
    }

    maxLen = max(maxLen, dp[i][j]);

    solveMemo(nums1, nums2, i - 1, j, dp, maxLen);
    solveMemo(nums1, nums2, i, j - 1, dp, maxLen);

    return dp[i][j];
}

int findLengthMemo(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();

    vector<vector<int>> dp(n, vector<int>(m, -1));
    int maxLen = 0;

    solveMemo(nums1, nums2, n - 1, m - 1, dp, maxLen);

    return maxLen;
}

// 3. Tabulation
// TC: O(n*m)
// SC: O(n*m)

int findLengthTabulation(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int maxLen = 0;

    // Base Case: Empty prefix
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }

    for (int j = 0; j <= m; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            if (nums1[i - 1] == nums2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                maxLen = max(maxLen, dp[i][j]);
            } else {
                dp[i][j] = 0;
            }
        }
    }

    return maxLen;
}

// 4. Space Optimization: Two Vectors
// TC: O(n*m)
// SC: O(m)

int findLengthSpace(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();

    vector<int> prev(m + 1, 0);
    vector<int> curr(m + 1, 0);
    int maxLen = 0;

    // Base Case
    prev[0] = 0;

    for (int i = 1; i <= n; i++) {
        curr[0] = 0;

        for (int j = 1; j <= m; j++) {

            if (nums1[i - 1] == nums2[j - 1]) {
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

// 5. Space Optimization: One Vector
// TC: O(n*m)
// SC: O(m)

int findLengthOneVector(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();

    vector<int> dp(m + 1, 0);
    int maxLen = 0;

    // Base Case
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {

        // Reverse traversal preserves the previous row's diagonal
        for (int j = m; j >= 1; j--) {

            if (nums1[i - 1] == nums2[j - 1]) {
                dp[j] = 1 + dp[j - 1];
                maxLen = max(maxLen, dp[j]);
            } else {
                dp[j] = 0;
            }
        }
    }

    return maxLen;
}


int main() {
    vector<int> nums1 = {1, 2, 3, 2, 1};
    vector<int> nums2 = {3, 2, 1, 4, 7};

    cout << "Recursion: "
         << findLengthRec(nums1, nums2) << endl;

    cout << "Memoization: "
         << findLengthMemo(nums1, nums2) << endl;

    cout << "Tabulation: "
         << findLengthTabulation(nums1, nums2) << endl;

    cout << "Two Vectors: "
         << findLengthSpace(nums1, nums2) << endl;

    cout << "One Vector: "
         << findLengthOneVector(nums1, nums2) << endl;

    return 0;
}
