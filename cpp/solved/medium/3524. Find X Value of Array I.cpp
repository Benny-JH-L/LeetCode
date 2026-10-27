#include <algorithm>
#include <unordered_map>

typedef unsigned long long biggest;

class Solution 
{
public:    
    vector<long long> resultArray(vector<int>& nums, int k) 
    {
        // so i need to make an array from `num` such that the products of the elements then modular `k` results in `x` (x is from 0 to < `k`)
        // then in the results array, index `x` is the number of possibilities exist such that the above conditions are met.
        // can only remove prefix and suffix once in each operation
        vector<long long> result(k, 0);
        
        // mod everything first
        for (int& val : nums)
        {
            val = val % k;
            // cout << val << ", ";
        }
        // cout << endl;

        int numSize = nums.size();
        // vector<vector<int>> dp(k, vector(numSize, 0));

        vector<long long> prevDp(k, 0);
        for (int end = 0; end < numSize; ++end)
        {
            vector<long long> dp(k, 0);

            int& currNum = nums[end];
            ++dp[currNum];

            for (int x = 0; x < k; ++x)
            {
                dp[(currNum * x) % k] += prevDp[x]; // remainder = (currNum * x) % k
            }

            prevDp = dp;

            for (int i = 0; i < k; ++i)
                result[i] += prevDp[i];
        }

        return result;
    }
};
