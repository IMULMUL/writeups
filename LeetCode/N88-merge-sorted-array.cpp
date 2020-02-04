class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = 0;
        for (int j = 0; j < n; j++) {
            int num = nums2[j];
            while(num >= nums1[i] && i < m) {
                i++;
            }
            nums1.insert(nums1.begin() + i, num);
            nums1.pop_back();
            m++;
        }
    }
};
