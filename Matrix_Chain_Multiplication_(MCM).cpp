#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

// Matrix Chain Multiplication (MCM)

// Given a sequence of matrices, find the minimum number of scalar
// multiplications required to multiply all matrices by choosing the best order
// of multiplication.

// The goal is to minimize the multiplication cost, not to change the order of
// matrices.

// Recusion => TC = O(2^n), SC = O(n)
int solveRec(int i, int j, vector<int> &arr) {
    if (i == j)
        return 0;

    int mini = 1e9;

    for (int k = i; k < j; k++) {
        int steps = arr[i - 1] * arr[k] * arr[j] + solveRec(i, k, arr) +
                    solveRec(k + 1, j, arr);

        mini = min(steps, mini);
    }

    return mini;
}

int matrixMultiplicationRec(vector<int> &arr) {
    int n = arr.size();

    return solveRec(1, n - 1, arr);
}

// Memoization => TC = O(n^3), SC = O(n^2) + O(n)
int solveMemo(int i, int j, vector<int> &arr, vector<vector<int>> &dp) {
    if (i == j)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int mini = 1e9;

    for (int k = i; k < j; k++) {
        int steps = arr[i - 1] * arr[k] * arr[j] + solveMemo(i, k, arr, dp) +
                    solveMemo(k + 1, j, arr, dp);

        mini = min(steps, mini);
    }

    return dp[i][j] = mini;
}

int matrixMultiplicationMemo(vector<int> &arr) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));

    return solveMemo(1, n - 1, arr, dp);
}

// Tabulation => TC = O(n^3), SC = O(n^2)
int matrixMultiplicationTab(vector<int> &arr) {
    int n = arr.size();

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = n - 1; i >= 1; i--) {
        for (int j = i + 1; j < n; j++) {

            int mini = 1e9;

            for (int k = i; k < j; k++) {
                int steps =
                    arr[i - 1] * arr[k] * arr[j] + dp[i][k] + dp[k + 1][j];

                mini = min(mini, steps);
            }

            dp[i][j] = mini;
        }
    }

    return dp[1][n - 1];
}

int main() {
    vector<int> arr = {40, 20, 30, 10, 30};

    cout << "Minimum number of multiplications (Recursion): "
         << matrixMultiplicationRec(arr) << endl;

    cout << "Minimum number of multiplications (Memoization): "
         << matrixMultiplicationMemo(arr) << endl;

    cout << "Minimum number of multiplications (Tabulation): "
         << matrixMultiplicationTab(arr) << endl;

    return 0;
}
