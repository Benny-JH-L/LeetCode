
#include<stack>

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
    ListNode* removeNthFromEnd(ListNode* head, int n) 
    {
        stack<ListNode*> s {};
        ListNode* curr = head;
        // add linked list to a stack
        while (curr != nullptr)
        {
            s.push(curr);
            curr = curr->next;
        }
        
        // case where we want to remove the head
        if (s.size() == n)
        {
            return head->next;
        }

        // pop n nodes
        for (int i = 0; i < n; ++i)
        {
            s.pop();
        }

        if (s.size() == 0)  // case of size 1 linked list
            head = nullptr;
        else
        {
            // cout << "s.top() val: " <<s.top()->val<< endl;
            ListNode* curr = s.top();
            curr->next = curr->next->next;  // we are guaranteed that `curr` will be the node before the node we want to remove
        }

        return head;
    }
};
