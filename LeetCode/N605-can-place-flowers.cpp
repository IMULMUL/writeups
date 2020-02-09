// the solution is trival
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        vector<int> plot;
        int count;
        bool countinued = false;
        for (int j = 0; j < flowerbed.size(); ++j) {
            int i = flowerbed[j];
            if (countinued && i == 0) {
                count++;
            } else if (!countinued && i == 0) {
                count++;
                if (j == 0) count++;
                countinued = true;
            }
            
            if ((countinued && i == 1) || j == flowerbed.size() - 1) {
                if (j == flowerbed.size() - 1 && i == 0) count++;
                plot.push_back(count);
                countinued = false;
                count = 0;
            }
        }
        
        int total = 0;
        for (auto i : plot) {
            total += (i - 1) / 2;
        }
        
        return total >= n;
    }
};
