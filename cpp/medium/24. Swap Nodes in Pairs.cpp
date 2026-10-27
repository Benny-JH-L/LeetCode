/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution 
{
public:
    ListNode* swapPairs(ListNode* head) 
    {
        // base cases
        if (head == nullptr)
            return head;
        
        if (head->next == nullptr)
            return head;
        
        // perform swppaing
        ListNode* p1 = head, *p2 = head->next, *tmp = nullptr;
        while (p1 != nullptr && p2 != nullptr)
        {                
            // swap
            p1->next = p2->next;    // set p1's next node to the node one over
            p2->next = p1;          // make p2 point to p1, now their positions are swapped

            // make sure the connection from the previous node is linked properly with the swapped nodes
            if (tmp != nullptr)
                tmp->next = p2;
            else    // re set the head
                head = p2;

            // update
            tmp = p1;
            p1 = p1->next;
            if (p1 != nullptr)
                p2 = p1->next;
        }

        return head;
    }
};
