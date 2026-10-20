#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// This function calculates the maximum profit that can be achieved from a list
// of stock prices.

// TC: O(n), SC: O(1)
int maxProfit(vector<int> &prices) {
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
