class Solution 
{
public:
    int findPeakElement(vector<int>& nums) 
    {
        /*
        Idea:
        Using binary search while checking neighbours, initial index range is from [0, nums.size()-1]. 
        Check middle element, if it is not bigger than its two neighbours, check which neighbour, left or right, is bigger.
        Left neighbour is index [middle - 1], right neighbour is index [middle + 1].
            - If the right is bigger search range = [middle + 1, nums.size() - 1]
            - Otherwise left is bigger, search range = [0, middle - 1]
            - then continue.
            Note: if the middle element index's neighbours outside of `nums`, ex. index of -1, or index of nums.size(), then we treat those neighbours as -INF.
        
        Ex.
        nums = [1,2,1,3,5,6,4]

        range[0, 6], middle val = 3, left val = 1, right val = 5 -> middle is not peak, right is bigger.
        range[4, 6], middle val = 6, left val = 5, right val = 4, both neighbours are smaller than `middle val`, return peak.

        Note: we would have turned left instead of right, and we would of found 2 to be the peak instead of 6.
        */
    }
};
