
#include<string>

class Solution 
{
public:

    bool recurr(int& digit, int& sum, string& sequence)
    {
        if (sum == 0 && digit > 0)
        {
            // add 0 pads
            for (int i = 0; i < digit; ++i)
                sequence.push_back('0');
            
            // cout << "added seq: " << sequence << endl;
            // output.push_back(sequence);
            return true;
        }
        else if (sum == 0 && digit == 0)
        {
            // output.push_back(sequence);
            return true;
        }
        else if (sum == 0 || digit == 0)    // cannot build string to satisfy conditions 
            return false;
        
        if (sum >= 10)
        {
            sum -= 9;
            sequence.push_back('9');
            return recurr(--digit, sum, sequence);
        }
        else
        {
            sequence.push_back(sum + '0'); // `sum` is single digit now
            sum -= sum;
            return recurr(--digit, sum, sequence);
        }
    }

    string maxSumOfSquares(int num, int sum) 
    {
        /*
        recursive approach
            - if sum >= 10 we will use digit `9` (large as possible)
            - if sum < 10 we'll use the digit denoted by `sum`
            - for each digit (each recursive call) we decrement `num` by 1.  
        */

        string sequence = "";
        if (recurr(num, sum, sequence))
            return sequence;
        
        return "";
        // vector<string> output {};
        // recurr(num, sum, sequence, output);

        // // auto lambda = [](string& s) {cout << s << ", ";};
        // // for_each(output.begin(), output.end(), lambda);

        // if (output.size() == 0)
        //     return "";

        // return output[0];
    }
};


