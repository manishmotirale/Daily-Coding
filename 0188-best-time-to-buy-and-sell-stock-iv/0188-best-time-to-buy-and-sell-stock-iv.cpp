#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Best Time to Buy and Sell Stock IV — LeetCode 188

// Given an array prices[] and an integer k, find the maximum profit by
// completing at most k transactions. You must sell your current stock before
// buying again.

// Recursion => TC: O(2^n), SC: O(n)
int solveRec(int k, vector<int> &prices, int i, int tranNo) {
    int n = prices.size();
    if (i == n || tranNo == 2 * k) // we have reached the end of the array or
                                   // completed all transactions
        return 0;

    int profit = 0;

    if (tranNo % 2 == 0) {
        // buy => we can either buy the stock or skip to the next day
        profit = max(-prices[i] + solveRec(k, prices, i + 1, tranNo + 1),
                     solveRec(k, prices, i + 1, tranNo));
    } else {
        // not buy => we can either sell the stock or skip to the next day
        profit = max(prices[i] + solveRec(k, prices, i + 1, tranNo + 1),
                     solveRec(k, prices, i + 1, tranNo));
    }
    return profit;
}

int maxProfitIVRec(int k, vector<int> &prices) {
    return solveRec(k, prices, 0, 0);
}

// Memoization => TC: O(n*k*2), SC: O(n*k*2) + O(n)
int solveMemo(int k, vector<int> &prices, int i, int tranNo,
              vector<vector<int>> &dp) {
    int n = prices.size();

    if (i == n || tranNo == 2 * k) // we have reached the end of the array or
        // completed all transactions
        return 0;

    if (dp[i][tranNo] != -1)
        return dp[i][tranNo];

    int profit = 0;
    if (tranNo % 2 == 0) {
        // buy => we can either buy the stock or skip to the next day
        profit = max(-prices[i] + solveMemo(k, prices, i + 1, tranNo + 1, dp),
                     solveMemo(k, prices, i + 1, tranNo, dp));
    } else {
        // not buy => we can either sell the stock or skip to the next day
        profit = max(prices[i] + solveMemo(k, prices, i + 1, tranNo + 1, dp),
                     solveMemo(k, prices, i + 1, tranNo, dp));
    }

    return dp[i][tranNo] = profit;
}

int maxProfitIVMemo(int k, vector<int> &prices) {
    vector<vector<int>> dp(prices.size(), vector<int>(2 * k, -1));
    return solveMemo(k, prices, 0, 0, dp);
}

// Tabulation => TC: O(n*k*2), SC: O(n*k*2)
int maxProfitIVTab(int k, vector<int> &prices) {
    int n = prices.size();
    vector<vector<int>> dp(n + 1, vector<int>(2 * k + 1, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int tranNo = 2 * k - 1; tranNo >= 0; tranNo--) {
            if (tranNo % 2 == 0) {
                dp[i][tranNo] =
                    max(-prices[i] + dp[i + 1][tranNo + 1], dp[i + 1][tranNo]);
            } else {
                dp[i][tranNo] =
                    max(prices[i] + dp[i + 1][tranNo + 1], dp[i + 1][tranNo]);
            }
        }
    }

    return dp[0][0];
}

// Space Optimization => TC: O(n*k*2), SC: O(k*2)
int maxProfitIVSpace(int k, vector<int> &prices) {
    int n = prices.size();
    vector<int> ahead(2 * k + 1, 0);
    vector<int> curr(2 * k + 1, 0);

    for (int i = n - 1; i >= 0; i--) {
        for (int tranNo = 2 * k - 1; tranNo >= 0; tranNo--) {
            if (tranNo % 2 == 0) {
                curr[tranNo] =
                    max(-prices[i] + ahead[tranNo + 1], ahead[tranNo]);
            } else {
                curr[tranNo] =
                    max(prices[i] + ahead[tranNo + 1], ahead[tranNo]);
            }
        }
        ahead = curr;
    }

    return ahead[0];
}

int main() {
    vector<int> prices = {3, 2, 6, 5, 0, 3};
    int k = 4;

    cout << "Maximum Profit (Recursion): " << maxProfitIVRec(k, prices) << endl;

    cout << "Maximum Profit (Memoization): " << maxProfitIVMemo(k, prices)
         << endl;

    cout << "Maximum Profit (Tabulation): " << maxProfitIVTab(k, prices)
         << endl;

    cout << "Maximum Profit (Space Optimization): "
         << maxProfitIVSpace(k, prices) << endl;

    return 0;
}
