class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
            cuts.push_back(n);
            cuts.insert(cuts.begin(), 0);

            sort(cuts.begin(), cuts.end());

            vector<vector<int>> dp(cuts.size(), vector<int>(cuts.size(), 0));

            for (int i = cuts.size() - 2; i >= 1; i--) {
                    for (int j = i; j <= cuts.size() - 2; j++) {
                            if (i > j)
                continue;

                            int mini = 1e9;

                            for (int idx = i; idx <= j; idx++) {
                                    // Current cut cost + left and right partition costs
                int cost =
                    cuts[j + 1] - cuts[i - 1] + dp[i][idx - 1] +
                        dp[idx + 1][j];

                                    mini = min(mini, cost);
                               
                }

                            dp[i][j] = mini;
                       
            }
               
        }

            return dp[1][cuts.size() - 2];
    }
};