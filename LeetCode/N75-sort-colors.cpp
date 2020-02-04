class Solution {
public:
    void sortColors(vector<int>& nums) {
        const int RED = 0, WHITE = 1, BLUE = 2;
        int blue_num = 0, red_num = 0, white_num = 0;
        for (auto i : nums) {
            if (i == RED)
                red_num++;
            if (i == WHITE)
                white_num++;
            if (i == BLUE)
                blue_num++;
        }

        nums.clear();
        nums.insert(nums.end(), red_num, RED);
        nums.insert(nums.end(), white_num, WHITE);
        nums.insert(nums.end(), blue_num, BLUE);
    }
};
