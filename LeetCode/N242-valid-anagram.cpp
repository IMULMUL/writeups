class Solution {
public:
    bool isAnagram(string s, string t) {
        char count_s[26] = {0}, count_t[26] = {0};
        if (s.size() != t.size()) return false;
        
        for (int i = 0; i < s.size(); ++i) {
            count_s[s[i] - 'a']++;
            count_t[t[i] - 'a']++;
        }
        
        for (int i = 0; i < 26; ++i) {
            if (count_s[i] != count_t[i]) return false;
        }
        
        return true;
    }
};
