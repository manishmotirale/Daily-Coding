#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Best Time to Buy and Sell Stock with Cooldown — LeetCode 309

// Given an array prices[], maximize profit by buying and selling stocks
// multiple times. After selling a stock, you must wait one day before buying
// again. You can hold only one stock at a time.

// Recursion => TC: O(2^n), SC: O(n)
int solveRec(vector<int> &prices, int i, int buy) {
    int n = prices.size();

    if (i == n)
        return 0;

    int profit = 0;
    if (buy) {
        profit = max(-prices[i] + solveRec(prices, i + 1, 0),
                     solveRec(prices, i + 1, 1));
    } else {
        profit = max(prices[i] + solveRec(prices, i + 2, 1),
                     solveRec(prices, i + 1, 0));
    }
    return profit;
}

int maxProfitCooldownRec(vector<int> &prices) { return solveRec(prices, 0, 1); }

// Memoization => TC: O(n*2), SC: O(n*2) + O(n)
int solveMemo(vector<int> &prices, int i, int buy, vector<vector<int>> &dp) {
    int n = prices.size();

    if (i == n)
        return 0;

    if (dp[i][buy] != -1)
        return dp[i][buy];

    int profit = 0;

    if (buy) {
        // buy => we can either` buy the stock or skip to the next day
        profit = max(-prices[i] + solveMemo(prices, i + 1, 0, dp),
                     solveMemo(prices, i + 1, 1, dp));
    } else {
        // not buy => we can either sell the stock or skip to the next day
        profit = max(prices[i] + solveMemo(prices, i + 2, 1, dp),
                     solveMemo(prices, i + 1, 0, dp));
    }

    return dp[i][buy] = profit;
}

int maxProfitCooldownMemo(vector<int> &prices) {
    int n = prices.size();

    vector<vector<int>> dp(n, vector<int>(2, -1));
    return solveMemo(prices, 0, 1, dp);
}

// Tabulation => TC: O(n*2), SC: O(n*2)
int maxProfitCooldownTab(vector<int> &prices) {
    int n = prices.size();

    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    dp[n][0] = dp[n][1] = 0; // base case

    for (int i = n - 1; i >= 0; i--) {
        for (int buy = 0; buy <= 1; buy++) {
            int profit = 0;

            if (buy) {
                profit = max(-prices[i] + dp[i + 1][0], dp[i + 1][1]);
            } else {
                profit = max(prices[i] + dp[i + 2][1], dp[i + 1][0]);
            }

            dp[i][buy] = profit;
        }
    }

    return dp[0][1];
}

// Space Optimization => TC: O(n*2), SC: O(1)
int maxProfitCooldownSpace(vector<int> &prices) {
    vector<int> front1(2, 0), front2(2, 0), curr(2, 0);
    int n = prices.size();

    for (int i = n - 1; i >= 0; i--) {
        curr[1] = max(-prices[i] + front1[0], front1[1]);

        curr[0] = max(prices[i] + front2[1], front1[0]);

        front2 = front1;
        front1 = curr;
    }
    return curr[1];
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    cout << "Max Profit (Recursion): " << maxProfitCooldownRec(prices) << endl;

    cout << "Max Profit (Memoization): " << maxProfitCooldownMemo(prices)
         << endl;

    cout << "Max Profit (Tabulation): " << maxProfitCooldownTab(prices) << endl;

    cout << "Max Profit (Space Optimized): " << maxProfitCooldownSpace(prices)
         << endl;

    return 0;
}
