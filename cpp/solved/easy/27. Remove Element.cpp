
#include<algorithm>

class Solution
{
public:
    int removeElement(vector<int>& nums, int val) 
    {
        sort(nums.begin(), nums.end()); // sort ascending
        int numberOfVals = count(nums.begin(), nums.end(), val);    // find number of `val`s in nums
        auto it = find(nums.begin(), nums.end(), val);  // find first occurance of `val` in nums
        nums.erase(it, it + numberOfVals);  // remove occurances of `val` whereever they are located in vector
        return nums.size();
    }
};
