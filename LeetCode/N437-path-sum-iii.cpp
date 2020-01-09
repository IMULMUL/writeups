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
    int pathSum(TreeNode* root, int sum) {
        return help(root, sum, 0, true);
    }
    
    int help(TreeNode* root, int sum, int num, bool split) {
        if (root == nullptr) {
            return 0;
        }
        int val = root->val + num;
        int res = val == sum;
        if (split) {
            return res + help(root->left, sum, val, true) + help(root->right, sum, val, true) + help(root->left, sum, 0, false) + help(root->right, sum,0,false);
        } else {
            return res + help(root->left, sum, val, false) + help(root->right, sum, val, false);
        }
    }
};
