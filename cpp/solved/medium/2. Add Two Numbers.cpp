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

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        // find the min length list, then 
        // add value of Node's together till min length (accounting for carry overs) list,
        // add the remaining Node's of the longer list with 0s until all of the elements have been considered (accounting for carry overs)

        // Find the small & big lists
        ListNode* minList = nullptr;
        ListNode* maxList = nullptr;

        ListNode* tmp1 = l1;
        ListNode* tmp2 = l2;
        while (tmp1 != nullptr && tmp2 != nullptr)
        {
            if (tmp1->next == nullptr)
            {
                minList = l1;
                maxList = l2;
            }
            else if (tmp2->next == nullptr)
            {
                minList = l2;
                maxList = l1;
            }

            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        tmp1 = nullptr;
        tmp2 = nullptr;

        // cout << "max: ";
        // while (maxList != nullptr)
        // {
        //     cout << maxList->val << " -> ";
        //     maxList = maxList->next;
        // }

        // Add
        int carry {};
        ListNode* makeResult = new ListNode(0);
        ListNode** result = &makeResult->next;
        for (;minList != nullptr; minList = minList->next, maxList = maxList->next)
        {
            int sum = minList->val + maxList->val + carry;

            carry = (int)(sum / 10);   // compute carry over
            sum %= 10;  // remove carry over
            makeResult->next = new ListNode(sum);
            makeResult = makeResult->next;
        }

        // consider remaining elements from maxList
        for (;maxList != nullptr; maxList = maxList->next)
        {
            int sum = maxList->val + carry;

            carry = (int)(sum / 10);   // compute carry over
            sum %= 10;  // remove carry over
            makeResult->next = new ListNode(sum);
            makeResult = makeResult->next;
        }

        // account for last carry
        if (carry > 0)
            makeResult->next = new ListNode(carry);

        return *result;
    }
};
