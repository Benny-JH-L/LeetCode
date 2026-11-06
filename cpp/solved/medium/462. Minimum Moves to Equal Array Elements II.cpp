
#include<algorithm>

class Solution 
{
public:
    int minMoves2(vector<int>& nums) 
    {
        /*
        Idea:
        sum up the numbers in `nums` and take the average. We want to get every element to that average.
            - Will integer overflow
        
        Idea 2:
        get the local average from 0 <= i < nums.size()-1: (nums[i] + nums[i+1] / 2). Once we get the local average from all the elements, floor the value. We want to get every element to that average.
        Ex. [1,2,3]
        (1+2)/2 = 1.5 (average so far), (1.5+3)/2 = 2.25. Target number is 2.
        Total moves we will need is 2, increment 1 by 1, and decrement 3 by 1.
            - FAILS
        
        Idea 3:
        sort `nums`, compare the absolute difference between nums[i] and nums[j], where `i` starts from 0 and goes up, `j` starts from the end and counts down, i != j, i < j.
        ex. nums = [1,10,2,9], -sort-> [1,2,9,10]
        diff at nums[0] and nums[3] is abs(1 - 10) = 9,
        diff at nums[1] and nums[2] is abs(2 - 9) = 7,
        add up the differences, 9 + 7 = 16, 16 moves.
        */
        
        int moves {};
        sort(nums.begin(), nums.end());
        for (int i = 0, j = nums.size() - 1; i < j; ++i, --j)
        {
            moves += abs(nums[i] - nums[j]);
        }
        return moves;
    }
};

/*
test case:
nums = 
for (int i = 0; i <= 9000; ++i)
    // add i to nums.

nums = 
for (int i = 1; i < 9000; ++i)
    // add (i * 100) to nums
*/
