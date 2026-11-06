class Solution 
{
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) 
    {
        int result {};
        for (int& num1 : arr1)
        {
            bool valid = true;
            for (int& num2: arr2)
            {
                if (abs(num1 - num2) <= d)
                {
                    valid = false;
                    break;
                }
            }

            if (valid)
                ++result;
        }
        return result;
    }
};
