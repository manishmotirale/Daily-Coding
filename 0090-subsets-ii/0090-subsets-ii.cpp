class Solution {
public:
    void printSubSet(vector<int>& nums, vector<int>& ans, int i,
                     vector<vector<int>>& allSets) {
        int n = nums.size();

        if (i == n) {
            allSets.push_back(ans);
            return;
        }

        // Include current element
        ans.push_back(nums[i]);
        printSubSet(nums, ans, i + 1, allSets);

        // Backtrack
        ans.pop_back();

        // Skip duplicate elements
        int idx = i + 1;
        while (idx < n && nums[idx] == nums[i])
            idx++;

        printSubSet(nums, ans, idx, allSets);
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<int> ans;
        vector<vector<int>> allSets;

        printSubSet(nums, ans, 0, allSets);

        return allSets;
    }
};