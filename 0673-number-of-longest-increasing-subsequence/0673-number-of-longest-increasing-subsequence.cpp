class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
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
};