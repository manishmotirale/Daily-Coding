#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Best Time to Buy and Sell Stock II — LeetCode 122

// You are given an array prices[], where prices[i] represents the stock price
// on day i. You can buy and sell stocks multiple times to maximize total
// profit, but you can hold only one stock at a time.

// Recursion => TC: O(2^n), SC: O(n)
int solveRec(vector<int> &prices, int i, int buy) {
    int n = prices.size();

    if (i == n) // we have reached the end of the array, so we cannot make any
                // more transactions
        return 0;

    int profit = 0;

    if (buy) {
        profit =
            max(-prices[i] + solveRec(prices, i + 1, 0),
                solveRec(prices, i + 1, 1)); // buy => we can either buy the
                                             // stock or skip to the next day
    } else {
        profit = max(
            prices[i] + solveRec(prices, i + 1, 1),
            solveRec(prices, i + 1, 0)); // not buy => we can either sell the
                                         // stock or skip to the next day
    }

    return profit;
}

int maxProfitIIRec(vector<int> &prices) { return solveRec(prices, 0, 1); }

// Memoization => TC: O(n*2), SC: O(n*2) + O(n)
int solveMemo(vector<int> &prices, int i, int buy, vector<vector<int>> &dp) {
    int n = prices.size();

    if (i == n)
        return 0;

    if (dp[i][buy] != -1)
        return dp[i][buy];

    int profit = 0;

    if (buy) {
        // buy => we can either buy the stock or skip to the next day
        profit = max(-prices[i] + solveMemo(prices, i + 1, 0, dp),
                     solveMemo(prices, i + 1, 1, dp));
    } else {
        // not buy => we can either sell the stock or skip to the next day
        profit = max(prices[i] + solveMemo(prices, i + 1, 1, dp),
                     solveMemo(prices, i + 1, 0, dp));
    }

    return dp[i][buy] = profit;
}

int maxProfitIIMemo(vector<int> &prices) {
    int n = prices.size();

    vector<vector<int>> dp(n, vector<int>(2, -1));
    return solveMemo(prices, 0, 1, dp);
}

// Tabulation => TC: O(n*2), SC: O(n*2)
int maxProfitIITab(vector<int> &prices) {
    int n = prices.size();

    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    dp[n][0] = dp[n][1] = 0; // base case

    for (int i = n - 1; i >= 0; i--) {
        for (int buy = 0; buy <= 1; buy++) {
            int profit = 0;

            if (buy) {
                profit = max(-prices[i] + dp[i + 1][0], dp[i + 1][1]);
            } else {
                profit = max(prices[i] + dp[i + 1][1], dp[i + 1][0]);
            }

            dp[i][buy] = profit;
        }
    }

    return dp[0][1];
}

// Space Optimization => TC: O(n*2), SC: O(2)
int maxProfitIISpace(vector<int> &prices) {
    int n = prices.size();

    vector<int> ahead(2, 0), curr(2, 0);
    ahead[0] = ahead[1] = 0;

    for (int i = n - 1; i >= 0; i--) {
        for (int buy = 0; buy <= 1; buy++) {
            int profit = 0;

            if (buy) {
                profit = max(-prices[i] + ahead[0], ahead[1]);
            } else {
                profit = max(prices[i] + ahead[1], ahead[0]);
            }

            curr[buy] = profit;
        }
        ahead = curr;
    }

    return ahead[1];
}

// Variable Optimization => TC: O(n*2), SC: O(1)
int maxProfitIIVariable(vector<int> &prices) {
    int n = prices.size();

    // aheadBuy: Maximum profit from the next day when you can buy.
    // aheadNotBuy: Maximum profit from the next day when you already hold a
    // stock and can sell. currBuy, currNotBuy: The same states, calculated for
    // the current day.

    // aheadButy ===> currBuy
    // aheadNotBuy ===> currNotBuy

    int aheadBuy = 0, aheadNotBuy = 0;
    int currBuy = 0, currNotBuy = 0;

    for (int i = n - 1; i >= 0; i--) {
        currBuy = max(-prices[i] + aheadNotBuy, aheadBuy);

        currNotBuy = max(prices[i] + aheadBuy, aheadNotBuy);

        aheadBuy = currBuy;
        aheadNotBuy = currNotBuy;
    }

    return aheadBuy;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    cout << "Max Profit (Recursion): " << maxProfitIIRec(prices) << endl;

    cout << "Max Profit (Memoization): " << maxProfitIIMemo(prices) << endl;

    cout << "Max Profit (Tabulation): " << maxProfitIITab(prices) << endl;

    cout << "Max Profit (Space Optimized): " << maxProfitIISpace(prices)
         << endl;

    cout << "Max Profit (Variable Optimized): " << maxProfitIIVariable(prices)
         << endl;

    return 0;
}
