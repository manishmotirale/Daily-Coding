class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int bestBuy = prices[0];
        int maxProfit = 0;
        int n = prices.size();

        for (int i = 0; i < n; i++) {
            int cost = prices[i] - bestBuy;
            maxProfit = max(maxProfit, cost);

            bestBuy = min(bestBuy, prices[i]);
        }

        return maxProfit;
    }
};