class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<int> dp(n, 1), hash(n);
        int maxLen = 1, lastIdx = 0;

        for (int i = 1; i < n; i++) {
            hash[i] = i;

            for (int prev = 0; prev < i; prev++) {
                // Check divisibility and update the longest subset
                if (nums[i] % nums[prev] == 0 && 1 + dp[prev] > dp[i]) {
                    dp[i] = 1 + dp[prev];
                    hash[i] = prev;
                }
            }

            // Store the index of the longest subset's endpoint
            if (dp[i] > maxLen) {
                maxLen = dp[i];
                lastIdx = i;
            }
        }

        // Reconstruct the subset using parent indices
        vector<int> temp;
        temp.push_back(nums[lastIdx]);

        while (hash[lastIdx] != lastIdx) {
            lastIdx = hash[lastIdx];
            temp.push_back(nums[lastIdx]);
        }

        reverse(temp.begin(), temp.end());
        return temp;
    }
};