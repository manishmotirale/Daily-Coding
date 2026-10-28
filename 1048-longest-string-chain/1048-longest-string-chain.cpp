class Solution {
public:
    bool checkPossible(string& s1, string& s2) {
        if (s1.size() != s2.size() + 1)
            return false;

        int first = 0, second = 0;

        while (first < s1.size()) {
            if (second < s2.size() && s1[first] == s2[second]) {
                first++;
                second++;
            } else {
                first++;
            }
        }

        return second == s2.size();
    }

    int longestStrChain(vector<string>& words) {
        // Sort words by length
        sort(words.begin(), words.end(),
             [](string& a, string& b) { return a.size() < b.size(); });

        int n = words.size();
        vector<int> dp(n, 1);
        int len = 1;

        for (int i = 0; i < n; i++) {
            for (int prev = 0; prev < i; prev++) {
                if (checkPossible(words[i], words[prev]) &&
                    1 + dp[prev] > dp[i]) {
                    dp[i] = 1 + dp[prev];
                }
            }

            len = max(len, dp[i]);
        }

        return len;
    }
};