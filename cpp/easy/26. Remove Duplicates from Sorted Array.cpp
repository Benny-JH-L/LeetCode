
#include<algorithm>

class Solution
{
public:
    int removeDuplicates(vector<int>& nums) 
    {
        for (auto it = nums.begin(); it != nums.end(); ++it)    // go through `nums`
        {
            // count number of occurances of *it
            // int occur = count(nums.begin(), nums.end(), *it); -> guaranteed to be O(n)
            int occur = 1;
            for (auto it2 = it + 1; it2 != nums.end(); ++it2, ++occur) // -> worst case O(n) but should terminate much quicker
            {
                if (*it2 != *it)
                    break;
            }
            if (occur > 1)
                nums.erase(it, it + occur - 1); // erase all but one occurance of *it
        }
        return nums.size();
    }
};
