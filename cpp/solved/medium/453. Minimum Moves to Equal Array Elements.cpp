
#include<algorithm>
#include<climits>

class Solution 
{
public:
    int minMoves(vector<int>& nums) 
    {
        /*
        Instead of trying to add 1 to `n-1` elements until we have all the elements equal. We can think of the problem in the opposite way:
        subtract 1 to 1 element until all the elements are equal (until they equal the min element in `nums`). 
        This way we don't need to track which elements need to be incremented: sorting.

        Thus, we find the smallest element in `nums`, call it `min`.
        Go through each element in `nums` and find the gap between `min` and nums[i], where 0 <= i < nums.size(). The gap will be the number of required moves
        to get nums[i] equal to `min`. Once we go through the entire list we'll have the total number of moves.
        */

        int moves {}, minElem = INT_MAX, size = nums.size(), tmpElem {};

        // find the min element
        for (int i = 0; i < size; ++i)
        {
            tmpElem = nums[i];
            if (tmpElem < minElem)
                minElem = tmpElem;
        }

        // go through the list
        for (int i = 0; i < size; ++i)
        {
            moves += abs(nums[i] - minElem);
        }

        return moves;
    }
};
