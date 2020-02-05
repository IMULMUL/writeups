class Solution {
public:
    int majorityElement(vector<int>& nums) {
        map<int, int> count;
        for (auto i : nums) {
            if (count.find(i) != count.end()) {
                count[i]++;
            } else {
                count.insert(pair(i, 1));
            }
        }
        
        int num = 0, c = 0;
        bool has = false;
        for (auto it : count) {
            if (has == false || it.second > num) {
                num = it.second;
                c = it.first;
                has = true;
            }
        }
        
        return c;
    }
};
