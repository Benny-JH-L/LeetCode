
#include<climits>
#include<cmath>

#define big unsigned long long

using namespace std;

class Solution 
{
public:
    int divide(int dividend, int divisor) 
    {
        /*
        Very simple Idea:
        Use a loop to count the number of subtractions we can do to dividend with divisor until it is < 0 and return the count.
        - this is very slow

        Idea
        Use a loop to count the number of subtractions we can do to dividend with divisor until it is < 0 and return the count.
        But to make this faster we bit-shift left once on the divisor every iteration, the base count added is 1,
        but when we bit shift we also need to shift the base count as well.

        When we encounter (dividend - divisor < 0) we need to reset the count add back to 1 and divisor to the base divisor and repeat.
        - If the (dividend - divisor < 0) and divisor is the base, we can exit and return the total count. 

        Ex. dividend = 10, divisor = 3

        count = 0
        base_count = 1
        my_divisor = 3

        iteration 1)
        10 - 3 = 7
        count += base_count // 1

        // shift
        base_count = 1 << 1 // 2
        my_divisor = 3 << 1 // 6

        iteration 2)
        7 - 6 = 1
        count += base_count // 3

        // shift
        base_count = 2 << 1 // 4
        my_divisor = 6 << 1 // 12

        iteration 3)
        1 - 12 = -11
        // reset
        base_count = 1
        my_divisor = divisor // 3

        iteration 4)
        1 - 3 = -2
        // divisor is equal to base and the difference is negative, return count (3).
        */

        bool isDivNeg = divisor < 0, isDividendNeg = dividend < 0;
        big new_divisor = abs((long long)divisor);
        big new_dividend = abs((long long)dividend);
        big scaledDivisor = new_divisor;
        big result{};

        int baseCount = 1;
        if (new_divisor > 1)
        {
            while (new_divisor <= new_dividend)
            {
                long long diff = (new_dividend - scaledDivisor);

                if (diff >= 0)
                {
                    new_dividend = diff;
                    result += baseCount;

                    // scale up counter and divisor
                    baseCount = baseCount << 1;
                    scaledDivisor = scaledDivisor << 1;

                    // divided evenly, stop
                    if (diff == 0)
                        break;
                }
                else
                {
                    // check if we subtracted with base divisor, if so and difference is negative stop
                    if (scaledDivisor == new_divisor)
                        break;
                    
                    baseCount = 1;
                    scaledDivisor = new_divisor;
                }
            }
        }
        else
        {
            // dividing by 1 gives the dividend
            if (isDivNeg && isDividendNeg && dividend == INT_MIN)   // check if two negatives and if dividend is -2147483648, if so we need to return 2147483647
                result = INT_MAX;
            else
                result = new_dividend;  
        }

        return (isDivNeg xor isDividendNeg ? -result : result); // make result negative if only one dividend or divisor is negative
    }
};
