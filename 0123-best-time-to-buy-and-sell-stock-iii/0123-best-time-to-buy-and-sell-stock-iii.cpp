class Solution {
public:
    int solveMemo(vector<int>& prices, int i, int buy, int cap,
                  vector<vector<vector<int>>>& dp) {
        int n = prices.size();

        if (i == n || cap == 0)
            return 0;

        int profit = 0;
        if (dp[i][buy][cap] != -1)
            return dp[i][buy][cap];

        if (buy) {
            profit = max(-prices[i] + solveMemo(prices, i + 1, 0, cap, dp),
                         solveMemo(prices, i + 1, 1, cap, dp));
        } else {
            profit = max(prices[i] + solveMemo(prices, i + 1, 1, cap - 1, dp),
                         solveMemo(prices, i + 1, 0, cap, dp));
        }

        return dp[i][buy][cap] = profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(2, vector<int>(3, -1)));

        return solveMemo(prices, 0, 1, 2, dp);
    }
};