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
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        TreeNode* tmp = nullptr;
        if (root == nullptr) return nullptr;
        
        if (L > root->val) {
            tmp = trimBST(root->right, L, R);
        } else if (R < root->val) { 
            tmp = trimBST(root->left, L, R); 
        } else {
            tmp = root;
            tmp->left = trimBST(tmp->left, L, R);
            tmp->right = trimBST(tmp->right, L, R);
        }
        
        return tmp;
    }
};
