
#include<unordered_set>
#include<cmath>

class Solution 
{
public:

    // made this 1st to get an idea of how to do it iteratively
    // void recurr(vector<int>& nums, int& subarrSize, int& result)
    // {
    //     if (subarrSize < 1)
    //         return;
        
    //     // cout << "sub arr size: " << subarrSize << endl;
    //     // build sub arrays of size `subarrSize`
    //     for (int i = 0; i < nums.size() && i + subarrSize <= nums.size(); ++i)
    //     {
    //         unordered_set<int> distinct {};
    //         for (int j = 0; j < subarrSize; ++j)
    //         {
    //             // cout << "elem: " << nums[i+j] << endl;
    //             distinct.insert(nums[i+j]);
    //         }

    //         // compute to result
    //         result += (distinct.size() * distinct.size());
    //         // cout << "curr result: " << result << endl; 
    //     }

    //     // compute other array sizes
    //     recurr(nums, --subarrSize, result);
    // }

    int sumCounts(vector<int>& nums) 
    {
        int result {};
        // int subarrLen = nums.size();
        // recurr(nums, subarrLen, result);
        // return result;

        for (int subarrSize = nums.size(); subarrSize > 0; --subarrSize)
        {
            // build sub arrays of size `subarrSize`
            for (int i = 0; i < nums.size() && i + subarrSize <= nums.size(); ++i)
            {
                unordered_set<int> distinct {};
                for (int j = 0; j < subarrSize; ++j)
                {
                    // cout << "elem: " << nums[i+j] << endl;
                    distinct.insert(nums[i+j]);
                }

                // compute to result
                result += (distinct.size() * distinct.size());
                // cout << "curr result: " << result << endl; 
            }
        }
        return result;
    }
};
