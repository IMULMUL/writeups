/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (s == nullptr) return t == nullptr ? true : false;
        if (t == nullptr) return false;
        bool res = isIsomorphic(s, t);
        
        if (res) return true;
        
        return isSubtree(s->left, t) || isSubtree(s->right, t);
    }
    
    bool isIsomorphic(TreeNode* s, TreeNode* t) {
        if (s == nullptr) return t == nullptr ? true : false;
        if (t == nullptr) return false;
       
        if (s->val == t->val) return isIsomorphic(s->left, t->left) && isIsomorphic(s->right, t->right);
            
        return false;
    }
};
