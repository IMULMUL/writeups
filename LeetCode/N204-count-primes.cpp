class Solution {
public:
    int countPrimes(int n) {
        int count = 0;
        for (int i = 2; i < n; ++i) {
            if (isPrime(i))
                ++count;
        }
        
        return count;
    }
    
    inline bool isPrime(int n) {
        for (int i = 2; i <= (int) sqrt(n); ++i) {
            if (n % i == 0 && n != i)
                return false;
        }
        
        return true;
    }
};
