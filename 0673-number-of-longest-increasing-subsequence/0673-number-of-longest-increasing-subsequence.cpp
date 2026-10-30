#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Number of Longest Increasing Subsequences

// Problem Statement:
// Given an integer array, find the number of longest strictly increasing
// subsequences (LIS) present in the array. We need to return the count of LIS,
// not just their length.

// TC: O(n^2), SC: O(n)
int findNumberOfLIS(vector<int> &nums) {
    int len = 1;
    int n = nums.size();

    if (n == 0)
        return 0;

    vector<int> dp(n, 1), cnt(n, 1);

    for (int i = 0; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {

            if (nums[prev] < nums[i] && 1 + dp[prev] > dp[i]) {
                dp[i] = 1 + dp[prev];

                // Inherit count
                cnt[i] = cnt[prev];

            } else if (nums[prev] < nums[i] && 1 + dp[prev] == dp[i]) {
                // Increase count
                cnt[i] += cnt[prev];
            }
        }
        len = max(len, dp[i]);
    }

    int nos = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] == len) {
            nos += cnt[i];
        }
    }

    return nos;
}

int main() {
    vector<int> nums = {1, 3, 5, 4, 7};
    cout << "Number of Longest Increasing Subsequences: "
         << findNumberOfLIS(nums) << endl;

    return 0;
}
