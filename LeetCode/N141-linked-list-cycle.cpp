/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        int i = 1;
        for (ListNode *iter = head; iter != NULL; iter = iter->next) {
            int j = 0;
            for (ListNode *iter2 = iter->next; iter2 != NULL && j < i; iter2 = iter2->next) {
                j++;
                if (iter == iter2)
                    return true;
            }
            
            i++;
        }
        return false;
    }
};
