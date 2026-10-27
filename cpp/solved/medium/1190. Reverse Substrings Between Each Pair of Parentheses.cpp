#include <algorithm>

class Solution 
{
public:

    void recur(string& s, int& index, string& result)
    {
        for (int& i = index; i < s.size(); ++i)
        {
            char& c = s[i];
            if (c == ')')   // stop and reverse string built
            {
                reverse(result.begin(), result.end());
                return;
            }
            else if (c == '(')  // recursive case
            {
                string reverse {};
                recur(s, ++i, reverse); // get reversed word between the next '(' and ')'
                result += reverse;
            }
            else    // build string
                result += c;
        }
    }

    string reverseParentheses(string s) 
    {
        string result {};
        int index {};
        recur(s, index, result);     
        return result;
    }
};

