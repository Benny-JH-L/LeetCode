#include <cmath>

class Solution 
{
public:
    bool judgeSquareSum(int c) 
    {
        /*
        square root `c`, take the floor of it as our starting point, call this 'a'.
        then set 'b' to 'a'; check if a^2 + b^2 = c. if not sqrt 'b' to get our new 'b', keep testing a^2 + b^2 = c until it works or 'b' is 1 and can no longer satisfy the constraint.

        new idea:
        start `a` = sqrt(c), and `b` = `a`, check a^2 + b^2 = c, 
            if our result is > c, decrease 'b' by half (record the local max).
            if our result is < c, increase 'b' by ((local max - `b`) / 2), rounded.
        repeat until constraint is satisfied or until 'b' reaches local max again.
        If the local max is reached again, decrease 'a' by 1, then repeat above.
        */

        // cout << "c: " << c << endl;
        int a = floor(sqrt(c));
        int b = a;
        int localMax {};
        for (;;)
        {
            int a2 = (a*a);
            int b2 = (b*b);
            // int myC = a2 + b2;
            int diff = c - a2 - b2;

            // cout << a << " * " << a << " = " << a2 << endl;
            // cout << b << " * " << b << " = " << b2 << endl;
            // // cout << c << " - " << a2 << " = " << (c - a2)<< endl;
            // // cout << c << " - " << b2 << " = " << (c - b2)<< endl;
            // cout << "(diff) " << c << " - " << a2 << " - " << b2 << " = " << diff << endl;
            // cout << "my c = " << myC << "\n" << endl;

            if (diff == 0)
            // if (myC == c)
                return true;
            else if (b == 1)
            {
                if (a2 == c) // treat 'b' as 0
                    return true;
            }
                
            if (diff < 0)   // too far off from `c` (too big from `c`)
            // if (myC > c)
            {
                localMax = b;
                b = round((float)b / 2);
            }
            else
            {
                b += round((localMax - b) / (float)2);

                // this search did result in a success, decrease `a`
                if (b == localMax)
                {
                    b = a; 
                    --a;

                    // `a` is negative, then we've checked everything and couldn't satisfy constraint
                    if (a < 0)
                        return false;
                }
            }
        }

        return false;
    }
};
