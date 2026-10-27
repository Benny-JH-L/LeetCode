
#include<algorithm>
#include<cmath>

class Solution 
{
public:
    vector<int> targetIndices(vector<int>& nums, int target) 
    {
        int size = nums.size();
        sort(nums.begin(), nums.end());
        // use binary search to find `target`
        int left {}, right = size - 1, middle {};   // index's
        int targetIdx = -1;
        while (left <= right)
        {
            middle = left + round((right - left) / 2.0);
            // cout << "l: " << left << endl;
            // cout << "r: " << right << endl;
            // cout << "m: " << middle << endl << endl;
            int& elem = nums[middle];
            if (elem == target)
            {
                targetIdx = middle;
                break;
            }
            else if (target > elem)
                left = middle + 1;
            else
                right = middle - 1;
        }

        // for (int& n : nums)
        //     cout << n << ", ";
        // cout << "\ntargetIdx = " << targetIdx;
        
        vector<int> result {};
        // check if there are multiple `targets`
        if (targetIdx != -1)
        {
            // check backward
            for (int i = targetIdx; i >= 0; --i)
            {
                if (nums[i] == target)
                    result.push_back(i);
                else
                    break;
            }
            reverse(result.begin(), result.end());
            // check forward
            for (int i = targetIdx + 1; i < size; ++i)
            {
                if (nums[i] == target)
                    result.push_back(i);
                else
                    break;   
            }
        }

        return result;
    }
};
