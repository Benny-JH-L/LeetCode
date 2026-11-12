
#include<cmath>

class Solution 
{
public:
    int longestMonotonicSubarray(vector<int>& nums) 
    {
        /*
        Idea:
        One loop to check strictly increaseing
        One loop to check strictkly decreasing
        - only track the length of the sub array, don't need to build out the whole thing.
        */

        // minimum subarray size is 1
        short result = 1, runningCount = 1; 
        // strictly increasing check
        for (int i = 0; i < nums.size() - 1; ++i)
        {
            if (nums[i] > nums[i+1])
                ++runningCount;
            else
            {
                result = max(result, runningCount);
                runningCount = 1;
            }
        }
        result = max(result, runningCount);
        runningCount = 1;
        // strictly decreasing check
        for (int i = 0; i < nums.size() - 1; ++i)
        {
            if (nums[i] < nums[i+1])
                ++runningCount;
            else
            {
                result = max(result, runningCount);
                runningCount = 1;
            }
        }
        result = max(result, runningCount);
        return (int)result;
    }
};
