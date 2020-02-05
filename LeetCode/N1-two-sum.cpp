class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int idx1 = 0;
        for (auto i : nums) {
            int idx2 = 0;
            for (auto j : nums) {
                if (idx1 != idx2 && i + j == target) {
                    return vector<int>{idx1, idx2};
                }
                idx2++;
            }
            idx1++;
        }
        return vector<int>{};
    }
};
