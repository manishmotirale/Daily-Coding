#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Longest Increasing Subsequence (LIS) — LeetCode 300

// Given an array of integers, find the length of the longest strictly
// increasing subsequence. Elements must remain in their original order, but
// they do not need to be adjacent.

// Recursion => TC: O(2^n), SC: O(n)
int solveRec(vector<int> &nums, int i, int prev) {
    int n = nums.size();

    if (i == n)
        return 0;

    int len = solveRec(nums, i + 1, prev);

    if (prev == -1 || nums[i] > nums[prev]) {
        len = max(len, 1 + solveRec(nums, i + 1, i));
    }

    return len;
}

int lengthOfLISRec(vector<int> &nums) { return solveRec(nums, 0, -1); }

// Memoization => TC: O(n^2), SC: O(n^2) + O(n)
int solveMemo(vector<int> &nums, int i, int prev, vector<vector<int>> &dp) {
    int n = nums.size();

    if (i == n)
        return 0;

    if (dp[i][prev + 1] != -1)
        return dp[i][prev + 1];

    int len = solveMemo(nums, i + 1, prev, dp);

    if (prev == -1 || nums[i] > nums[prev]) {
        len = max(len, 1 + solveMemo(nums, i + 1, i, dp));
    }

    return dp[i][prev + 1] = len;
}

int lengthOfLISMemo(vector<int> &nums) {
    int n = nums.size();

    vector<vector<int>> dp(n, vector<int>(n + 1, -1));

    return solveMemo(nums, 0, -1, dp);
}

// Tabulation => TC: O(n^2), SC: O(n^2)
int lengthOfLISTab(vector<int> &nums) {
    int n = nums.size();

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int prev = i - 1; prev >= -1; prev--) {
            int len = dp[i + 1][prev + 1];

            if (prev == -1 || nums[i] > nums[prev]) {
                len = max(len, 1 + dp[i + 1][i + 1]);
            }

            dp[i][prev + 1] = len;
        }
    }

    return dp[0][0];
}

// Space Optimization => TC: O(n^2), SC: O(n)
int lengthOfLISSpace(vector<int> &nums) {
    int n = nums.size();

    vector<int> next(n + 1, 0), curr(n + 1, 0);

    for (int i = n - 1; i >= 0; i--) {
        for (int prev = i - 1; prev >= -1; prev--) {
            int len = next[prev + 1];

            if (prev == -1 || nums[i] > nums[prev]) {
                len = max(len, 1 + next[i + 1]);
            }

            curr[prev + 1] = len;
        }
        next = curr;
    }

    return next[0];
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

    cout << "Length of Longest Increasing Subsequence (Recursion): "
         << lengthOfLISRec(nums) << endl;

    cout << "Length of Longest Increasing Subsequence (Memoization): "
         << lengthOfLISMemo(nums) << endl;

    cout << "Length of Longest Increasing Subsequence (Tabulation): "
         << lengthOfLISTab(nums) << endl;

    cout << "Length of Longest Increasing Subsequence (Space Optimization): "
         << lengthOfLISSpace(nums) << endl;

    return 0;
}
