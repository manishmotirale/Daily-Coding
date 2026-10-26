#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Recursion => TC: O(2^n), SC: O(n)
int solveRec(int W, vector<int> &val, vector<int> &wt, int i) {
    if (i == 0) {
        if (wt[0] <= W)
            return (W / wt[0]) * val[0]; // Take as many of the first item as possible
        return 0;
    }

    int notTake = solveRec(W, val, wt, i - 1);

    int take = INT_MIN;
    if (wt[i] <= W) {
        take = val[i] + solveRec(W - wt[i], val, wt, i);
    }

    return max(take, notTake);
}

int unboundedKnapsackRec(int W, vector<int> &val, vector<int> &wt) {
    int n = val.size();
    return solveRec(W, val, wt, n - 1);
}

// Memoization => TC: O(n*W), SC: O(n*W) + O(n) (Recursion stack)
int solveMemo(int W, vector<int> &val, vector<int> &wt, int i,
              vector<vector<int>> &dp) {
    if (i == 0) {
        if (wt[0] <= W)
            return (W / wt[0]) * val[0];
        return 0;
    }

    if (dp[i][W] != -1) {
        return dp[i][W];
    }

    int notTake = solveMemo(W, val, wt, i - 1, dp);

    int take = INT_MIN;
    if (wt[i] <= W) {
        take = val[i] + solveMemo(W - wt[i], val, wt, i, dp);
    }

    return dp[i][W] = max(take, notTake);
}

int unboundedKnapsackMemo(int W, vector<int> &val, vector<int> &wt) {
    int n = val.size();
    vector<vector<int>> dp(n, vector<int>(W + 1, -1));

    return solveMemo(W, val, wt, n - 1, dp);
}

// Tabulation => TC: O(n*W), SC: O(n*W)
int knapsackTab(int W, vector<int> &val, vector<int> &wt) {
    int n = val.size();
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));

    for (int w = wt[0]; w <= W; w++) {
        dp[0][w] = (w / wt[0]) * val[0];
    }

    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = dp[i - 1][w];

            int take = INT_MIN;
            if (wt[i] <= w) {
                take = val[i] + dp[i][w - wt[i]];
            }

            dp[i][w] = max(take, notTake);
        }
    }

    return dp[n - 1][W];
}

// Space Optimization => TC: O(n*W), SC: O(W)
int unboundedKnapsackSpaceOpt(int W, vector<int> &val, vector<int> &wt) {
    int n = val.size();
    vector<int> prev(W + 1, 0), curr(W + 1, 0);

    for (int w = wt[0]; w <= W; w++) {
        prev[w] = (w / wt[0]) * val[0];
    }

    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = prev[w];

            int take = INT_MIN;
            if (wt[i] <= w) {
                take = val[i] + curr[w - wt[i]];
            }

            curr[w] = max(take, notTake);
        }
        prev = curr;
    }

    return prev[W];
}

// Two vectors => one vector
// Space Optimization => TC: O(n*W), SC: O(W)
int knapsackSpaceOptForOneVector(int W, vector<int> &val, vector<int> &wt) {
    int n = val.size();
    vector<int> prev(W + 1, 0);

    for (int w = wt[0]; w <= W; w++) {
        prev[w] = (w / wt[0]) * val[0];
    }

    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = prev[w];

            int take = INT_MIN;
            if (wt[i] <= w) {
                take = val[i] + prev[w - wt[i]];
            }

            prev[w] = max(take, notTake);
        }
    }
    return prev[W];
}

int main() {
    int W = 5;
    vector<int> val = {1, 2, 3, 4};
    vector<int> wt = {1, 2, 3, 4};

    cout << unboundedKnapsackRec(W, val, wt) << endl;
    cout << unboundedKnapsackMemo(W, val, wt) << endl;
    cout << unboundedKnapsackTab(W, val, wt) << endl;
    cout << unboundedKnapsackSpaceOpt(W, val, wt) << endl;
    cout << knapsackSpaceOptForOneVector(W, val, wt) << endl;
}
