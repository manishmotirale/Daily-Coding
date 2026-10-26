#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Recursion => TC = O(2^N), SC = O(N)
int solveRec(int i, int N, vector<int> &price) {
    if (i == 0) {
        return N * price[0];
    }

    int notTake = solveRec(i - 1, N, price);

    int take = INT_MIN;
    int rodLen = i + 1;

    if (rodLen <= N) {
        take = price[i] + solveRec(i, N - rodLen, price);
    }

    return max(take, notTake);
}

int cutRodRec(vector<int> &price) {
    int N = price.size();

    return solveRec(N - 1, N, price);
}

// Memoization => TC = O(N^2), SC = O(N^2) + O(N)
int solveMemo(int i, int N, vector<int> &price, vector<vector<int>> &dp) {
    if (i == 0) {
        return N * price[0];
    }

    if (dp[i][N] != -1) {
        return dp[i][N];
    }

    int notTake = solveMemo(i - 1, N, price, dp);

    int take = INT_MIN;
    int rodLen = i + 1;

    if (rodLen <= N) {
        take = price[i] + solveMemo(i, N - rodLen, price, dp);
    }

    return dp[i][N] = max(take, notTake);
}

int cutRodMemo(vector<int> &price) {
    int N = price.size();

    vector<vector<int>> dp(N, vector<int>(N + 1, -1));
    return solveMemo(N - 1, N, price, dp);
}

// Tabulation => TC = O(N^2), SC = O(N^2)
int cutRodTab(vector<int> &price) {
    int N = price.size();

    vector<vector<int>> dp(N, vector<int>(N + 1, 0));

    for (int n = 0; n <= N; n++) {
        dp[0][n] = n * price[0];
    }

    for (int i = 1; i < N; i++) {
        for (int n = 0; n <= N; n++) {
            int notTake = dp[i - 1][n];

            int take = INT_MIN;
            int rodLen = i + 1;

            if (rodLen <= n) {
                take = price[i] + dp[i][n - rodLen];
            }

            dp[i][n] = max(take, notTake);
        }
    }

    return dp[N - 1][N];
}

// Space Optimization => TC = O(N^2), SC = O(N)
int cutRodSpaceOpt(vector<int> &price) {
    int N = price.size();

    vector<int> prev(N + 1, 0), curr(N + 1, 0);

    for (int n = 0; n <= N; n++) {
        prev[n] = n * price[0];
    }

    for (int i = 1; i < N; i++) {
        for (int n = 0; n <= N; n++) {
            int notTake = prev[n];

            int take = INT_MIN;
            int rodLen = i + 1;

            if (rodLen <= n) {
                take = price[i] + curr[n - rodLen];
            }

            curr[n] = max(take, notTake);
        }
        prev = curr;
    }

    return prev[N];
}

// Two Vector => One Vector
// TC = O(N^2), SC = O(N)
int cutRodOneVector(vector<int> &price) {
    int N = price.size();

    vector<int> prev(N + 1, 0);

    for (int n = 0; n <= N; n++) {
        prev[n] = n * price[0];
    }

    for (int i = 1; i < N; i++) {
        for (int n = 0; n <= N; n++) {
            int notTake = prev[n];

            int take = INT_MIN;
            int rodLen = i + 1;

            if (rodLen <= n) {
                take = price[i] + prev[n - rodLen];
            }

            prev[n] = max(take, notTake);
        }
    }

    return prev[N];
}

int main() {
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};

    cout << "Maximum obtainable value (Recursion): " << cutRodRec(price)
         << endl;

    cout << "Maximum obtainable value (Memoization): " << cutRodMemo(price)
         << endl;
    cout << "Maximum obtainable value (Tabulation): " << cutRodTab(price)
         << endl;

    cout << "Maximum obtainable value (Space Optimization): "
         << cutRodSpaceOpt(price) << endl;

    cout << "Maximum obtainable value (One Vector): " << cutRodOneVector(price)
         << endl;

    return 0;
}
