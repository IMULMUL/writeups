class Solution {
public:
    bool isIsomorphic(string s, string t) {
        map<char, char> table1, table2;
        if (s.size() != t.size()) return false;
        
        for (int i = 0; i < s.size(); ++i) {
            if (table1.find(s[i]) == table1.end()
               && table2.find(t[i]) == table2.end()) {
                table1.insert(pair<char, char>(s[i], t[i]));
                table2.insert(pair<char, char>(t[i], s[i]));
            } else {
                if (table1[s[i]] != t[i] || table2[t[i]] != s[i])
                    return false;
            }
        }
        
        return true;
    }
};
