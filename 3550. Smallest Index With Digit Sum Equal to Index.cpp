class Solution 
{
public:
    int smallestIndex(vector<int>& nums) 
    {
        int numSize = nums.size();
        for (int i = 0; i < numSize; ++i)
        {
            int& val = nums[i];
            int sum {};

            while (val > 9)
            {
                sum += val % 10;
                val = (val / 10);
            }
            sum += val;

            if (sum == i)
                return i;
        }

        return -1;
    }
};
