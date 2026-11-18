
#include<climits>

class Solution 
{
public:
    int findPeakElement(vector<int>& nums) 
    {
        /*
        Idea:
        Using binary search while checking neighbours, initial index range is from [left, right], left = 0, right = nums.size() - 1. 
        Check middle element, if it is not bigger than its two neighbours, check which neighbour, left or right, is bigger.
        Left neighbour is index [middle - 1], right neighbour is index [middle + 1].
            - If the right is bigger search range = [new left, right], new Left = middle + 1.
            - Otherwise left is bigger, search range = [left, new right], new right = middle - 1
            - then continue.
            Note: if the middle element index's neighbours outside of `nums`, ex. index of -1, or index of nums.size(), then we treat those neighbours as -INF.
        
        Ex.
        nums = [1,2,1,3,5,6,4]

        range[0, 6], middle val = 3, left val = 1, right val = 5 -> middle is not peak, right is bigger.
        range[4, 6], middle val = 6, left val = 5, right val = 4, both neighbours are smaller than `middle val`, return peak.

        Note: we would have turned left instead of right, and we would of found 2 to be the peak instead of 6.
        */

        int size = nums.size(), middle {}, left {}, right = size - 1;
        while (left <= right)
        {
            middle = left + round((right - left) / 2.0);
            // cout << "middle idx: " << middle << endl;
            // cout << "middle val: " << nums[middle] << endl;
            // cout << "curr left: " << left << " | curr right: " << right << endl << endl;

            int leftNeighbour = INT_MIN, rightNeighbour = INT_MIN, middleElem = nums[middle];

            // set if not out of bounds
            if (middle - 1 >= 0)
            {
                leftNeighbour = nums[middle - 1];
            }
            if (middle + 1 < size)
            {
                rightNeighbour = nums[middle + 1];
            }

            if (middleElem > leftNeighbour && middleElem > rightNeighbour)
                return middle;  // return index
            // set new bounds if not a peak
            if (leftNeighbour > rightNeighbour)
                right = middle - 1;
            else
                left = middle + 1;
        }

        return middle;
    }
};
