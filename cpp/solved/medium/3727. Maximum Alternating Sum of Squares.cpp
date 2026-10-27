
#include <algorithm>
#include <cmath>

class Solution 
{
public:
    long long maxAlternatingSum(vector<int>& nums) 
    {
        // sort nums from smallest to largest (ascending), then
        // split nums into two arrays evenly (one contains the smaller half of numbers, the other the bigger half)
            // can still use 'nums' but track index's

        // ensure everything is positive
        auto positive = [](int& a) -> void {a = abs(a);};
        for_each(nums.begin(), nums.end(), positive);

        sort(nums.begin(), nums.end());

        // for (int& i : nums)
        // {
        //     cout << i<< ", ";
        // }

        long long result {};

        int smallsToConsider = floor(nums.size() / 2);
        // use small to subtract, big to add
        for (int i = 0; i < smallsToConsider; ++i)
            result -= (nums[i] * nums[i]);
        for (int i = nums.size() - 1; i >= smallsToConsider; --i)
            result += (nums[i] * nums[i]);

        return result;
    }
};
