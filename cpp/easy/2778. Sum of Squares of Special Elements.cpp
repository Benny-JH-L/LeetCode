class Solution 
{
public:
    int sumOfSquares(vector<int>& nums) 
    {
        int result {};
        int size = nums.size();
        for (int i = 1; i < size + 1; ++i)
        {
            // cout << size << " % " << i << " = " << (size % i) << endl;
            if (size % i == 0)
            {
                result += (nums[i-1] * nums[i-1]);
            }
        }

        return result;
    }
};
