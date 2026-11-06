class Solution 
{
public:
    int minMoves2(vector<int>& nums) 
    {
        /*
        Idea:
        sum up the numbers in `nums` and take the average. We want to get every element to that average.
            - But we will integer overflow
        
        Idea 2:
        get the local average from 0 <= i < nums.size()-1: (nums[i] + nums[i+1] / 2). Once we get the local average from all the elements, floor the value. We want to get every element to that average.
        Ex. [1,2,3]
        (1+2)/2 = 1.5 (average so far), (1.5+3)/2 = 2.25. Target number is 2.
        Total moves we will need is 2, increment 1 by 1, and decrement 3 by 1.
        */
        
        float target = nums[0];
        for (int i = 1; i < nums.size(); ++i)
            target = ((target + nums[i]) / 2.0);
        
        target = floor(target);
        cout << "target: " << target << endl;

        int moves {};
        for (int& n : nums)
        {
            moves += abs(target - n);
        }
        return moves;
    }
};

/*
test case:
nums = 
for (int i = 0; i < 9000; ++i)
    // add i to nums.

*/