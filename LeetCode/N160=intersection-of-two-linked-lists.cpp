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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        using List = ListNode *;
        for (List tmp = headA; tmp != nullptr; tmp = tmp->next) {
            for (List tmp1 = headB; tmp1 != nullptr; tmp1 = tmp1->next) {
                if (tmp1 == tmp) return tmp;
            }
        }
        
        return nullptr;
    }
};
