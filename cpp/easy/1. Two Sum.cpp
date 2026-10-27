class Solution 
{
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        // if we made a 2D `n`x`n` grid, where `n` is the size of `nums`, that's filled 
        // with all possible sums from `nums` we see that the grid mirrors itself about the diagonal, and 
        // the diagonal is empty bc of the problem's condition, as such we only need to compute one half of the grid (upper of lower) 
        // instead of the whole grid.
        
        vector<int> result {};

        int numSize = nums.size();
        for (int hop = 1; hop <= numSize - 1; ++hop)
        {
            for (int i = 0; i < numSize - hop; ++i)
            {
                if ((nums[i] + nums[i + hop]) == target)
                    return result = {i, i + hop};
            }
        }

        return result;
    }
};
