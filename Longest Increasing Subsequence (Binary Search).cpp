#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Problem Statement: Longest Increasing Subsequence (LIS)
// Given an integer array, find the length of the longest strictly increasing
// subsequence while maintaining the original order of elements. Solve it in
// O(n * log n) using Binary Search.

// Note: temp stores the smallest possible tail for each subsequence length; it
// does not necessarily contain the actual LIS.

// Binary Search Approach => TC: O(n log n), SC: O(n)
int lengthOfLIS(vector<int> &nums) {
    vector<int> temp;
    temp.push_back(nums[0]);

    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > temp.back()) {
            temp.push_back(nums[i]);
        } else {
            int idx =
                lower_bound(temp.begin(), temp.end(), nums[i]) - temp.begin();

            temp[idx] = nums[i];
        }
    }

    return temp.size();
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

    cout << "Length of Longest Increasing Subsequence (Binary Search): "
         << lengthOfLIS(nums) << endl;

    return 0;
}
