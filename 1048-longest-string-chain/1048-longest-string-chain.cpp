#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Problem Statement: Longest String Chain

// Given an array of words, find the length of the longest chain where each next
// word is formed by inserting exactly one character into the previous word
// without changing the order of existing characters.

// TC: O(n * m), SC: O(n)
bool checkPossible(string &s1, string &s2) {
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

int longestStringChain(vector<string> &words) {
    // Sort words by length
    sort(words.begin(), words.end(),
         [](string &a, string &b) { return a.size() < b.size(); });

    int n = words.size();
    vector<int> dp(n, 1);
    int len = 1;

    for (int i = 0; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {
            if (checkPossible(words[i], words[prev]) && 1 + dp[prev] > dp[i]) {
                dp[i] = 1 + dp[prev];
            }
        }

        len = max(len, dp[i]);
    }

    return len;
}

// Function to print the longest string chain sequence
vector<string> longestStringChainPrinting(vector<string> &words) {
    int n = words.size();

    sort(words.begin(), words.end(),
         [](string &a, string &b) { return a.size() < b.size(); });

    vector<int> dp(n, 1), hash(n);

    int maxLen = 1, lastIdx = 0;

    for (int i = 0; i < n; i++) {
        hash[i] = i;

        for (int prev = 0; prev < i; prev++) {
            if (checkPossible(words[i], words[prev]) && 1 + dp[prev] > dp[i]) {
                dp[i] = 1 + dp[prev];
                hash[i] = prev;
            }
        }

        if (dp[i] > maxLen) {
            maxLen = dp[i];
            lastIdx = i;
        }
    }

    // Reconstruct the chain
    vector<string> ans;
    ans.push_back(words[lastIdx]);

    while (hash[lastIdx] != lastIdx) {
        lastIdx = hash[lastIdx];
        ans.push_back(words[lastIdx]);
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    vector<string> words = {"a", "b", "ba", "bca", "bda", "bdca"};

    cout << "Longest String Chain: " << longestStringChain(words)
         << endl; // Output: 4X

    vector<string> chain = longestStringChainPrinting(words);
    cout << "Longest String Chain Sequence: ";
    for (string &word : chain) {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}
