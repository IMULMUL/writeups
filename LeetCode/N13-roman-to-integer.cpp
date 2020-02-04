class Solution {
public:
    int romanToInt(string s) {
        int res = 0, len = s.length();
        bool direct = true;
        for (int i = 0; i < len; i++) {
            bool direct = true;
            int next = i + 1;
            if (s[i] == 'I') {
                if (next < len && s[next] == 'V') {
                    res -= 1;
                } else if (next < len && s[next] == 'X') {
                    res -= 1;
                } else {
                    res += 1;
                }
            }
        
            if (s[i] == 'X') {
                if (next < len && s[next] == 'L') {
                    res -= 10;
                } else if (next < len && s[next] == 'C') {
                    res -= 10;
                } else {
                    res += 10;
                }
            }
    
            if (s[i] == 'C') {
                if (next < len && s[next] == 'D') {
                    res -= 100;
                } else if (next < len && s[next] == 'M') {
                    res -= 100;
                } else {
                    res += 100;
                }
            }
            
            if (s[i] == 'V')
                res += 5;
            
            if (s[i] == 'L')
                res += 50;
            
            if (s[i] == 'D')
                res += 500;
            
            if (s[i] == 'M')
                res += 1000;
        }
        return res;
    }
};
