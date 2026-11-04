
#include<algorithm>
#include<vector>

class Solution 
{
public:
    vector<int> plusOne(vector<int>& digits) 
    {
        vector<int> result;
        short carry {}, size = digits.size(), s {};
        digits[size-1] += 1;

        for (short i = size - 1; i >= 0; --i)
        {
            int& n = digits[i];            
            s = (n + carry) % 10;
            carry = (s == 0 && n != 0 ? 1 : 0);
            result.push_back(s);
        }

        if (carry != 0)
            result.push_back(carry);
        
        reverse(result.begin(), result.end());
        return result;
    }
};
