#include <iostream>
#include <vector>
using namespace std;

// Problem Statement: Best Time to Buy and Sell Stock III — LeetCode 123

// Given an array prices[], find the maximum profit you can earn by completing
// at most two transactions. You must sell your current stock before buying
// again.

// Recursion => TC: O(2^n), SC: O(n)
int solveRec(vector<int> &prices, int i, int buy, int cap) {
    int n = prices.size();

    if (i == n || cap == 0)
        return 0;

    int profit = 0;

    if (buy) {
        profit = max(-prices[i] + solveRec(prices, i + 1, 0, cap),
                     solveRec(prices, i + 1, 1, cap));
    } else {
        profit = max(prices[i] + solveRec(prices, i + 1, 1, cap - 1),
                     solveRec(prices, i + 1, 0, cap));
    }

    return profit;
}

int maxProfitIIIRec(vector<int> &prices) { return solveRec(prices, 0, 1, 2); }

// Memoization => TC: O(n*2*3), SC: O(n*2*3) + O(n)
int solveMemo(vector<int> &prices, int i, int buy, int cap,
              vector<vector<vector<int>>> &dp) {
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

int maxProfitIIIMemo(vector<int> &prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(n,
                                   vector<vector<int>>(2, vector<int>(3, -1)));

    return solveMemo(prices, 0, 1, 2, dp);
}

// Tabulation => TC: O(n*2*3), SC: O(n*2*3)
int maxProfitIIITab(vector<int> &prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(n + 1,
                                   vector<vector<int>>(2, vector<int>(3, 0)));

    for (int i = n - 1; i >= 0; i--) {
        for (int buy = 0; buy <= 1; buy++) {
            for (int cap = 1; cap <= 2; cap++) {
                if (buy) {
                    dp[i][buy][cap] =
                        max(-prices[i] + dp[i + 1][0][cap], dp[i + 1][1][cap]);
                } else {
                    dp[i][buy][cap] = max(prices[i] + dp[i + 1][1][cap - 1],
                                          dp[i + 1][0][cap]);
                }
            }
        }
    }

    return dp[0][1][2];
}

// Space Optimization => TC: O(n*2*3), SC: O(2*3)
int maxProfitIIISpace(vector<int> &prices) {
    int n = prices.size();

    vector<vector<int>> ahead(2, vector<int>(3, 0)), curr(2, vector<int>(3, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int buy = 0; buy <= 1; buy++) {
            for (int cap = 1; cap <= 2; cap++) {
                if (buy) {
                    curr[buy][cap] =
                        max(-prices[i] + ahead[0][cap], ahead[1][cap]);
                } else {
                    curr[buy][cap] =
                        max(prices[i] + ahead[1][cap - 1], ahead[0][cap]);
                }
            }
        }
        ahead = curr;
    }

    return ahead[1][2];
}

// Space Optimization with Memoization => TC: O(n*4), SC: O(n*4) + O(n)
int solveSpaceMemo(vector<int> &prices, int i, int cap,
                   vector<vector<int>> &dp) {
    int n = prices.size();
    if (i == n || cap == 4)
        return 0;

    if (dp[i][cap] != -1)
        return dp[i][cap];

    int profit = 0;

    if (cap % 2 == 0) {
        // Buy
        profit = max(-prices[i] + solveSpaceMemo(prices, i + 1, cap + 1, dp),
                     solveSpaceMemo(prices, i + 1, cap, dp));
    } else {
        // Sell
        profit = max(prices[i] + solveSpaceMemo(prices, i + 1, cap + 1, dp),
                     solveSpaceMemo(prices, i + 1, cap, dp));
    }

    return dp[i][cap] = profit;
}

int maxProfitIIISpaceMemo(vector<int> &prices) {
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(4, -1));

    return solveSpaceMemo(prices, 0, 0, dp);
}

int main() {
    vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};

    cout << "Maximum Profit (Recursion): " << maxProfitIIIRec(prices) << endl;

    cout << "Maximum Profit (Memoization): " << maxProfitIIIMemo(prices)
         << endl;

    cout << "Maximum Profit (Tabulation): " << maxProfitIIITab(prices) << endl;

    cout << "Maximum Profit (Space Optimization): " << maxProfitIIISpace(prices)
         << endl;

    cout << "Maximum Profit (Space Optimization with Memoization): "
         << maxProfitIIISpaceMemo(prices) << endl;

    return 0;
}
