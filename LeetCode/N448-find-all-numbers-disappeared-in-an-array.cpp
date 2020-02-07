class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> result;
        int size = nums.size();
        if (size == 0) return result;
        
        int arr[size] = {0};
        
        for (auto i : nums) {
            if (i > size) continue;
            
            arr[i - 1] = 1;
        }
        
        for (int i = 0; i < size; i++) {
            if (arr[i] == 0)
                result.push_back(i + 1);
        }
        
        return result;
    }
};
