class Solution {
public:
    int solveRec(vector<int>& prices, int buy, int i, vector<vector<int>>& dp) {
        int n = prices.size();

        if (i == n)
            return 0;

        int profit = 0;

        if (dp[i][buy] != -1)
            return dp[i][buy];

        if (buy) {
            profit = max(-prices[i] + solveRec(prices, 0, i + 1, dp),
                         solveRec(prices, 1, i + 1, dp));
        } else {
            profit = max(prices[i] + solveRec(prices, 1, i + 1, dp),
                         solveRec(prices, 0, i + 1, dp));
        }

        return dp[i][buy] = profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solveRec(prices, 1, 0, dp);
    }
};