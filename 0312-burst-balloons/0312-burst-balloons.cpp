#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Recursion => TC: O(2^N) SC: O(N)
int solveRec(int i, int j, vector<int> &arr) {
    if (i > j)
        return 0;

    int maxi = -1e9;

    for (int idx = i; idx <= j; idx++) {
        // Current balloon is burst last
        int cost = arr[i - 1] * arr[idx] * arr[j + 1] +
                   solveRec(i, idx - 1, arr) + solveRec(idx + 1, j, arr);

        maxi = max(maxi, cost);
    }

    return maxi;
}

int maxProductSumRec(vector<int> &arr) {
    int n = arr.size();

    arr.insert(arr.begin(), 1);
    arr.push_back(1);

    return solveRec(1, n, arr);
}

// Memoization => Top Down: TC = O(N^3) SC = O(N^2)
int solveMemo(int i, int j, vector<int> &arr, vector<vector<int>> &dp) {
    if (i > j)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int maxi = -1e9;

    for (int idx = i; idx <= j; idx++) {
        // Current balloon is burst last
        int cost = arr[i - 1] * arr[idx] * arr[j + 1] +
                   solveMemo(i, idx - 1, arr, dp) +
                   solveMemo(idx + 1, j, arr, dp);

        maxi = max(maxi, cost);
    }

    return dp[i][j] = maxi;
}

int maxProductSumMemo(vector<int> &arr) {
    int n = arr.size();
    arr.insert(arr.begin(), 1);
    arr.push_back(1);
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));

    return solveMemo(1, n, arr, dp); // n because we added 2 extra elements
}

// Tabulation => Bottom Up: TC = O(N^3) SC = O(N^2)
int maxProductSumTab(vector<int> &arr) {
    int n = arr.size();

    arr.insert(arr.begin(), 1);
    arr.push_back(1);

    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            if (i > j)
                continue;

            int maxi = -1e9;

            for (int idx = i; idx <= j; idx++) {
                // Current balloon is burst last
                int cost = arr[i - 1] * arr[idx] * arr[j + 1] + dp[i][idx - 1] +
                           dp[idx + 1][j];

                maxi = max(maxi, cost);
            }

            dp[i][j] = maxi;
        }
    }

    return dp[1][n];
}

int main() {
    vector<int> arr = {3, 1, 5, 8};

    vector<int> arr1 = arr;
    vector<int> arr2 = arr;
    vector<int> arr3 = arr;

    cout << "Maximum coins (Recursion): " << maxProductSumRec(arr1) << endl;

    cout << "Maximum coins (Memoization): " << maxProductSumMemo(arr2) << endl;

    cout << "Maximum coins (Tabulation): " << maxProductSumTab(arr3) << endl;

    return 0;
}

// Modifying the same vector
// Each function modifies arr by inserting 1 at the beginning and pushing 1 at
// the end.

// So, when you call the three functions using the same vector, the boundaries
// get added repeatedly.

// Fix: Pass a separate copy of the original array to each function.
