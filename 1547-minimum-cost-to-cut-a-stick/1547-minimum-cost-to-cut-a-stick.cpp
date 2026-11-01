#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

// Minimum Cost to Cut a Stick Partition DP

// Given a stick of length n and an array of required cut positions, find the
// minimum total cost to make all cuts.

// The cost of each cut is equal to the current length of the stick being cut.

// Recursion => TC: O(2^n), SC: O(n)
int solveRec(int i, int j, vector<int> &cuts) {
    if (i > j)
        return 0;

    int mini = 1e9;

    for (int idx = i; idx <= j; idx++) {
        // Current cut cost + left and right partition costs
        int cost = cuts[j + 1] - cuts[i - 1] + solveRec(i, idx - 1, cuts) +
                   solveRec(idx + 1, j, cuts);

        mini = min(mini, cost);
    }

    return mini;
}

int minCutCostRec(int n, vector<int> &cuts) {
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);

    sort(cuts.begin(), cuts.end());

    return solveRec(1, cuts.size() - 2,
                    cuts); // cuts.size() - 2 because we added two extra cuts (0
                           // and n) to the vector
}

// Memoization => TC: O(n^3), SC: O(n^2) + O(n)
int solveMemo(int i, int j, vector<int> &cuts, vector<vector<int>> &dp) {
    if (i > j)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j]; // Return stored answer

    int mini = 1e9;

    for (int idx = i; idx <= j; idx++) {
        // Current cut cost + left and right partition costs
        int cost = cuts[j + 1] - cuts[i - 1] + solveMemo(i, idx - 1, cuts, dp) +
                   solveMemo(idx + 1, j, cuts, dp);

        mini = min(mini, cost);
    }

    return dp[i][j] = mini; // Store answer
}

int minCutCostMemo(int n, vector<int> &cuts) {
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);

    sort(cuts.begin(), cuts.end());

    vector<vector<int>> dp(cuts.size(), vector<int>(cuts.size(), -1));

    return solveMemo(1, cuts.size() - 2, cuts, dp);
}

// Tabulation => TC: O(n^3), SC: O(n^2)
int minCutCostTab(int n, vector<int> &cuts) {
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);

    sort(cuts.begin(), cuts.end());

    vector<vector<int>> dp(cuts.size(), vector<int>(cuts.size(), 0));

    for (int i = cuts.size() - 2; i >= 1; i--) {
        for (int j = i; j <= cuts.size() - 2; j++) {
            int mini = 1e9;

            for (int idx = i; idx <= j; idx++) {
                // Current cut cost + left and right partition costs
                int cost =
                    cuts[j + 1] - cuts[i - 1] + dp[i][idx - 1] + dp[idx + 1][j];

                mini = min(mini, cost);
            }

            dp[i][j] = mini;
        }
    }

    return dp[1][cuts.size() - 2];
}

int main() {
    int n = 7;

    vector<int> cuts1 = {1, 3, 4, 5};
    vector<int> cuts2 = {1, 3, 4, 5};
    vector<int> cuts3 = {1, 3, 4, 5};

    cout << "Minimum cost (Recursion): " << minCutCostRec(n, cuts1) << endl;

    cout << "Minimum cost (Memoization): " << minCutCostMemo(n, cuts2) << endl;

    cout << "Minimum cost (Tabulation): " << minCutCostTab(n, cuts3) << endl;

    return 0;
}
