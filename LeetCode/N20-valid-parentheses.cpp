class Solution {
public:
    bool isValid(string s) {
        stack<char> ch_stack;
        if (s.length() % 2 == 1) return false;
        for (auto ch : s) {
            if (ch == '(' || ch == '[' || ch == '{') {
                ch_stack.push(ch);
            } else {
                if (ch_stack.size() == 0) return false;
                char curr = ch_stack.top();
                ch_stack.pop();
                if (ch == ')' && curr == '(')
                    continue;
                if (ch == '}' && curr == '{')
                    continue;
                if (ch == ']' && curr == '[')
                    continue;
                return false;
            }
        }
        
        return ch_stack.size() == 0;
    }
};
