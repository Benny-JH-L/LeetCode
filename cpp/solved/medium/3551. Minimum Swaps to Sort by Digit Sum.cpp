
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<set>

class Solution 
{
public:
    class Node 
    {
        public:
            int num {};
            int sum {};
            Node(int& n, int& s) : num(n), sum(s)
            {}
    };

    int minSwaps(vector<int>& nums) 
    {
        /*
        first sort `nums` based on the digit sum and using their value as a tie breaker.
        Then in another vector (lets call it `a`), record the index where each value ended up in the sorted array.
        We use `a` and `nums` and compare their values to determine where each element should end up; prioritize swaping with other elements that leads to their desired index.
        
        Ex. nums = [18,43,34,16]
        sorted = [16,34,43,18]
        a = [3, 2, 1, 0]
        - value 18 in `nums` ended up at index 3 in `sorted`
        - value 43 in `nums` ended up at index 2 in `sorted`
        - value 34 in `nums` ended up at index 1 in `sorted`
        - value 16 in `nums` ended up at index 0 in `sorted`

        // this works but is too slow -- see below for new idea.
        now, we can determine the min number of swaps
        Since we want `18` to ened up at index 3, we want to choose another value to swap with that wants to end up at index 0, 
        in this case, it will be value `16`. 1 Swap.
        `43` wants to be at index 2 so we swap with `34`, both end up where they want to be. 1 Swap.
        Total 2 swaps.
        Note: there will be the case where there is no swap that makes both values end up where they want to be.
        in this case; you need to consider where is the best possible swap that will eventually lead to where this value's desired index.
        // ---

        // new idea. (From hint 2)
        we know the desired index that values want to be. we can use this to determine a cycle for where values want to go.
        this cycle tells us the number of swaps required to get those values to their desired index's.
        Ex. nums = [18,43,34,26]
        sorted = [34,43,26,18]
        inx map= [0, 1, 2, 3]

        Pick some arbitrary starting point, we will use index 0.
        Nums[0] = 18, 18 wants index 3
        Nums[3] = 26, 26 wants index 2,
        Nums[2] = 34, 34 wants index 0,
        Nums[0] = 18. Cycle detected, number of swaps = cycle size - 1 = 3 - 1 = 2

        Unchecked index's: 1
        Nums[1] = 43, 43 wants index 1. Cycle detected, number of swaps = 1 - 1 = 0.

        Number of swaps = 2 + 0 = 2. Which is the correct number of minimum swaps.
        */
        vector<Node*> toSort {};
        for (int& i : nums)
        {
            int sum {};
            for (char& c : to_string(i))
                sum += static_cast<int>(c) - 48;   // 48 is ascii for '0'
            toSort.push_back(new Node(i, sum));
        }

        // sort
        auto comp = [](Node* n1, Node* n2) -> bool
        {
            if (n1->sum == n2->sum)
                return n1->num < n2->num;
            return n1->sum < n2->sum;
        };
        sort(toSort.begin(), toSort.end(), comp);

        // make index mapping
        unordered_map<int, int> indexMap {};
        // string debug1 = "sorted: ", debug2 = "idx map: ";
        for (int i = 0; i < toSort.size(); ++i)
        {
            Node* n = toSort[i];
            indexMap[n->num] = i;  // map `value` with their desired sorted `index`
            // debug1 += to_string(n-> num) + ", ";
            // debug2 += to_string(i) + ", ";
        }
        // cout << debug1 << endl;
        // cout << debug2 << endl;

        // find the min number of swaps
        set<int> visited {};    // track indicies visited
        int swaps {}, cycleSize {};
        // go though desired index mapping of values
        for (auto& pair : indexMap) 
        {
            int& desiredIndex = pair.second; // the desired sorted index for pair.first
            if (visited.contains(desiredIndex)) // visited this index already
                continue;

            visited.insert(desiredIndex);
            ++cycleSize;

            // count cycle size
            for (int nextDesired = indexMap[nums[desiredIndex]]; nextDesired != desiredIndex ;)
            {
                ++cycleSize;
                visited.insert(nextDesired);
                nextDesired = indexMap[nums[nextDesired]];
            }

            swaps += (cycleSize - 1);
            cycleSize = 0;  // reset
        }


        // for (int i = 0; i < nums.size(); ++i)
        // {
        //     int num1 = nums[i];
        //     // check if current num is in the right position
        //     if (indexMap[num1] == i)
        //         continue;
            
        //     // find value in `nums` who wants to be at index `i`
        //     for (int j = i; j < nums.size(); ++j)
        //     {
        //         int num2 = nums[j];
        //         // perform swap if this `value` wants to be at index `i`
        //         if (indexMap[num2] == i) 
        //         {
        //             nums[i] = num2;
        //             nums[j] = num1;
        //             ++swaps;
        //             break;
        //         }
        //     }
        // }

        return swaps;
    }
};
