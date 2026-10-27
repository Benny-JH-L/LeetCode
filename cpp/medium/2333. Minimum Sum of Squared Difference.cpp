
#include<queue>
#include<vector>
#include<cmath>

class Solution 
{
public:
    class Node
    {
        public:
            int idx;
            int diff;

            Node(int index, int dif) : idx(index), diff(dif)
            { }

            bool operator<(const Node& node) const
            {
                return this->diff < node.diff;
            }
    };

    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) 
    {
        /*
        idea: 
        using a max heap to store nums1[i] and nums2[i]'s squared difference & their values.
        1) we will go through the input and create our initial heap with no modifications.
        2) poping from the max heap we get nums1[i] and nums2[i]'s square diff, then we modify nums1[i] and nums2[i] to get 
            a smaller squared difference (as close to 0 as possible); recording k1 and k2 modifications, and putting it back onto the max heap.
        3) we will keep repeating 2) until we have exhausted our k1 and k2 maximum modifications or until the total sum is no longer decreasing. 
            if a node does not reduce in its squared difference, it is no longer considered for future modification's (as long as we have modifications remaining)
        */

        auto compareNodePtr = [](Node* n1, Node* n2)
        {
            return n1->diff < n2->diff;
        };

        priority_queue<Node*, vector<Node*>, decltype(compareNodePtr)> maxHeap {};   // stores squared differences

        for (int i = 0; i < nums1.size(); ++i)
        {
            Node* node = new Node(i, abs(nums1[i] - nums2[i]));
            maxHeap.push(node); // store squared diff
            // Node top = *maxHeap.top();
            // cout << "n1: " << nums1[node->idx] << " | n2: " << nums2[node->idx] << " | diff: " << node->diff << endl;
        }
        cout << endl;
        
        // apply modifications
        while (maxHeap.size() > 0)
        {
            Node* node = maxHeap.top();
            maxHeap.pop();

            const int& i = node->idx;
            // cout << "nums1["<<i<<"]: " << nums1[i] << " | nums2["<<i<<"]: " << nums2[i] << " | diff: " << node->diff << endl;

            // don't need to consider this node
            if (nums1[i] - nums2[i] == 0)
            {
                delete node;
                continue;
            }

            if (k1 == 0 && k2 == 0)
            {
                break;
            }

            // case: k1 > 0; subtract or add 1 to get smaller diff from nums1[i]
            // case: k2 > 0; subtract or add 1 to get smaller diff from nums2[i]

            int maxMod = node->diff - maxHeap.top()->diff; // maximum modifications we can do before we reach the next big node.
            int maxK1Mod = 1;
            int maxK2Mod = 1;

            int addn1 = nums1[i] + maxK1Mod;
            int subn1 = nums1[i] - maxK1Mod;

            int addn2 = nums2[i] + maxK2Mod;
            int subn2 = nums2[i] - maxK2Mod;

            if (k1 > 0)
            {
                int sDiff1 = abs(addn1 - nums2[i]);
                int sDiff2 = abs(subn1 - nums2[i]);

                // adding gives smaller square diff
                if (sDiff1 <= sDiff2)
                {
                    k1 -= maxK1Mod;
                    nums1[i] += maxK1Mod;
                }
                // subtracting gives smaller square diff
                else if (sDiff2 < sDiff1)
                {
                    k1 -= maxK1Mod;
                    nums1[i] -= maxK1Mod;
                }

                node->diff = min(sDiff1, sDiff2);
                maxHeap.push(node);
            }
            else if (k2 > 0)
            {
                int sDiff1 = abs(nums1[i] - addn2);
                int sDiff2 = abs(nums1[i] - subn2);

                // adding gives smaller square diff
                if (sDiff1 <= sDiff2)
                {
                    k2 -= maxK2Mod;
                    nums2[i] += maxK2Mod;
                }
                // subtracting gives smaller square diff
                else if (sDiff2 < sDiff1)
                {
                    k2 -= maxK2Mod;
                    nums2[i] -= maxK2Mod;
                }

                node->diff = min(sDiff1, sDiff2);
                maxHeap.push(node);
            }
        }

        long long result {};

        for (int i = 0; i < nums1.size(); ++i)
        {
            long long difference = nums1[i] - nums2[i]; 
            result += (difference * difference);
        }

        return result;
    }
};
