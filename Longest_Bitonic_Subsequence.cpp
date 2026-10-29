#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Problem Statement: Longest Bitonic Subsequence

// Given an array of integers, find the length of the longest subsequence that
// first strictly increases and then strictly decreases. The elements do not
// need to be contiguous

// TC: O(n^2), SC: O(n)
int longestBitonicSequence(int n, vector<int> &nums) {
    vector<int> lis(n, 1), lds(n, 1);

    // LIS: Longest Increasing Subsequence ending at i
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }

    // LDS: Longest Decreasing Subsequence starting at i
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (nums[j] < nums[i]) {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }

    int len = 0;

    // Combine increasing and decreasing parts
    for (int i = 0; i < n; i++) {
        if (lis[i] > 1 && lds[i] > 1) {
            len = max(len, lis[i] + lds[i] - 1);
        }
    }

    return len;
}
