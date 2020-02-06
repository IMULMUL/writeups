class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        int n1 = 0;
        int n2 = 0;
        for (auto i : nums) {
            int tmp = n1;
            n1 = max(i + n2, n1);
            n2 = tmp;
        }
        
        return n1;
    }
};
