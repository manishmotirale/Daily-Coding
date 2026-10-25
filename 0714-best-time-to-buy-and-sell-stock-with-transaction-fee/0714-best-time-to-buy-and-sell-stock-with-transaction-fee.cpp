#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Best Time to Buy and Sell Stock with Transaction Fee — LeetCode 714

// Given an array prices[] and an integer fee, maximize profit by completing
// unlimited stock transactions. You must sell before buying again, and pay the
// transaction fee for each completed transaction

// Recursion => TC: O(2^n), SC: O(n)
int solveRec(vector<int> &prices, int i, int buy, int fee) {
    int n = prices.size();

    if (i == n)
        return 0;

    int profit = 0;
    if (buy) {
        profit = max(-prices[i] + solveRec(prices, i + 1, 0, fee),
                     solveRec(prices, i + 1, 1, fee));
    } else {
        profit = max(prices[i] - fee + solveRec(prices, i + 1, 1, fee),
                     solveRec(prices, i + 1, 0, fee));
    }
    return profit;
}

int maxProfitRec(vector<int> &prices, int fee) {
    return solveRec(prices, 0, 1, fee);
}

// Memoization => TC: O(n*2), SC: O(n*2) + O(n)
int solveMemo(vector<int> &prices, int i, int buy, int fee,
              vector<vector<int>> &dp) {
    int n = prices.size();

    if (i == n)
        return 0;

    if (dp[i][buy] != -1)
        return dp[i][buy];

    int profit = 0;
    if (buy) {
        profit = max(-prices[i] + solveMemo(prices, i + 1, 0, fee, dp),
                     solveMemo(prices, i + 1, 1, fee, dp));
    } else {
        profit = max(prices[i] - fee + solveMemo(prices, i + 1, 1, fee, dp),
                     solveMemo(prices, i + 1, 0, fee, dp));
    }
    return dp[i][buy] = profit;
}

int maxProfitMemo(vector<int> &prices, int fee) {
    int n = prices.size();

    vector<vector<int>> dp(n, vector<int>(2, -1));

    return solveMemo(prices, 0, 1, fee, dp);
}

// Tabulation => TC: O(n*2), SC: O(n*2)
int maxProfitTab(vector<int> &prices, int fee) {
    int n = prices.size();

    vector<vector<int>> dp(n + 1, vector<int>(2, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int buy = 0; buy <= 1; buy++) {
            if (buy) {
                dp[i][buy] = max(-prices[i] + dp[i + 1][0], dp[i + 1][1]);
            } else {
                dp[i][buy] = max(prices[i] - fee + dp[i + 1][1], dp[i + 1][0]);
            }
        }
    }

    return dp[0][1];
}

// Space Optimization => TC: O(n*2), SC: O(2)
int maxProfitSpaceOpt(vector<int> &prices, int fee) {
    int n = prices.size();

    int aheadBuy = 0, aheadNotBuy = 0;
    int curBuy = 0, curNotBuy = 0;

    for (int i = n - 1; i >= 0; i--) {
        curBuy = max(-prices[i] + aheadNotBuy, aheadBuy);
        curNotBuy = max(prices[i] - fee + aheadBuy, aheadNotBuy);

        aheadBuy = curBuy;
        aheadNotBuy = curNotBuy;
    }

    return aheadBuy;
}

int main() {
    vector<int> prices = {1, 3, 2, 8, 4};
    int fee = 2;

    cout << "Max Profit (Recursion): " << maxProfitRec(prices, fee) << endl;

    cout << "Max Profit (Memoization): " << maxProfitMemo(prices, fee) << endl;

    cout << "Max Profit (Tabulation): " << maxProfitTab(prices, fee) << endl;

    cout << "Max Profit (Space Optimization): "
         << maxProfitSpaceOpt(prices, fee) << endl;

    return 0;
}
