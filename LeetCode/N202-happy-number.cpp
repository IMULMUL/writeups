class Solution {
public:
    bool isHappy(int n) {
        vector<int> occur;
        int sum = n;
        while (sum != 1) {
            if (find(occur.begin(), occur.end(), sum) != occur.end())
                return false;
            
            occur.push_back(sum);
            int tmp = sum;
            sum = 0;
            while (tmp !=0 ) {
                sum += (tmp % 10) * (tmp % 10);
                tmp = tmp / 10;
            }
        }
        
        return true;
    }
};
