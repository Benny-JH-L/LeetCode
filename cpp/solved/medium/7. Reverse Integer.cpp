
#include <vector>
#include <string>
#include <algorithm>

class Solution 
{
public:

    int reverse(int x) 
    {  
        bool negative = x < 0;
        string reversed = to_string(x);
        std::reverse(reversed.begin(), reversed.end());

        // quick checks
        string compareTo = (negative ? to_string(2147483648) + "-" : to_string(2147483647));

        if (reversed.size() < compareTo.size())
            return (negative ? stoi("-" + reversed) : stoi(reversed));
        
        // check digits if overflowed
        vector<int> results {}; // 2: larger, 1: equal, 0: less (when compared to `compareTo` with `reversed`)
        int size = reversed.size(), ascii {}, ascii2 {};

        for (int i = 0; i < size; ++i)
        {
            ascii = static_cast<int>(reversed[i]);
            ascii2 = static_cast<int>(compareTo[i]);
            // cout << static_cast<char>(ascii) << endl;
            // cout << static_cast<char>(ascii2) << endl;

            if (ascii > ascii2)
                results.push_back(2);
            else if (ascii == ascii2)
                results.push_back(1);
            else
                results.push_back(0);
        }

        // cout << "rev: " << reversed << endl;
        // cout << "Too: " << compareTo << endl;
        // cout << "rez: ";
        // for (int& i : results)
        //     cout << i;
        // cout << endl;

        if (results[0] == 2)
            return 0;
        
        for (int p1 = 1; p1 < size; ++p1)
        {
            // cout << "p1: " << p1 << endl;
            if (results[p1] == 2)   
            {
                int& back1 = results[p1 - 1];
                if (back1 == 0)         // no way to overflow with a '02' pattern in the front of '22'
                    break;
                else if (back1 <= 2)    // found a '12' or '22' with no '02' in front, overflow
                    return 0;
            }  
        }

        // int max = 2147483647, min = -2147483648;
        return (negative ? stoi("-" + reversed) : stoi(reversed));
    }
};
