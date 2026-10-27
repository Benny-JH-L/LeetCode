
#include <vector>
#include <cmath>

class Solution 
{
public:

    bool isPalindrome(int x) 
    {
        if (x < 0)
            return false;

        vector<int> remainders {};

        // compute remainders
        while (x >= 1)
        {
            if (x == 1)
            {
                remainders.emplace_back(x);
                break;
            }

            int rem {};
            // cout << "x: "<<x<<endl;
            
            rem = (x % 10 == 0 ? 0 : x % 10);

            x = floor(x / 10);
            // cout << "rem: "<< rem << " | x: "<<x<<endl;W
            
            remainders.emplace_back(rem);
        }

        // check if palindrome
        for (int front = 0, end = remainders.size() - 1; front <= end && front != end; ++front, --end)
        {
            if (remainders[front] != remainders[end])
                return false;
        }

        return true;
    }
};
