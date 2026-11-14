
#include<climits>

class Solution 
{
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) 
    {
        int result = INT_MAX;
        for (int i = 0; i < nums.size(); ++i)
        {
            int sum = nums[i], size = 1;

            for (int j = i + 1; j < nums.size() && size <= r - 1; ++j)
            {
                // cout << "sum: " << sum << " | size: " << size << endl;
                if (size >= l && size <= r && sum > 0)
                    result = min(result, sum);
                sum += nums[j];
                ++size;

            }

            if (size >= l && size <= r && sum > 0)
                result = min(result, sum);
        }

        return (result == INT_MAX ? -1 : result);
    }
};
