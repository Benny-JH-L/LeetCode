
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

class Solution 
{
public:

    int find_largest_pancake(vector<int>& pancake_stack, int end)
    {
        auto largest_pancake = max_element(pancake_stack.begin(), pancake_stack.begin() + end);
        return distance(pancake_stack.begin(), largest_pancake);    // return index of where pancake is located
    }

    void flip(vector<int>& pancake_stack, int k)
    {
        reverse(pancake_stack.begin(), pancake_stack.begin() + k);
    }

    vector<int> pancakeSort(vector<int>& pancake_stack)
    {
        vector<int> flips;
        int n = pancake_stack.size();
        int curr_size = n;
        for (; curr_size > 1; curr_size--)
        {
            // Step 1, find largest pancake
            int largest_pancake_idx = find_largest_pancake(pancake_stack, curr_size);

            // If the largest isn't already at the bottom of the unsorted section
            if (largest_pancake_idx != curr_size - 1)
            {
                // Step 2, flip the stack so the pancake is on top
                if (largest_pancake_idx != 0)
                {
                    flip(pancake_stack, largest_pancake_idx + 1);
                    flips.push_back(largest_pancake_idx + 1);
                    // cout << "Fliped at idx: " << largest_pancake_idx << ": ";
                }

                // Step 3, flip unsorted potion so pancake is now sorted
                flip(pancake_stack, curr_size);
                flips.push_back(curr_size);
                // cout << "Fliped at idx: " << curr_size - 1 << ": ";
            }
            // Step 4, repeat until you've gone through the whole stack
        }
        return flips;
    }
};
