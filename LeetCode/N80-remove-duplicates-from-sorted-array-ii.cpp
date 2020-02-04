class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i = 0;
        while (i < nums.size() - 1 && nums.size() != 0) {
            if (i == 0) {
                i++;
                continue;
            }
            
            if (nums[i - 1] == nums[i] && nums[i] == nums[i + 1]) {
                nums.erase(nums.begin() + i);
                continue;
            }
            
            i++;
        }
        
        return nums.size();
    }
};
