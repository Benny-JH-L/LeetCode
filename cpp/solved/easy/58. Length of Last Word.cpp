class Solution 
{
public:
    int lengthOfLastWord(string s) 
    {
        int result {};

        for (int i = s.size() - 1; i >= 0; --i)
        {
            // find first non space character
            if (s[i] != ' ')
            {
                // count word length
                for (int& j = i; j >= 0; --j)
                {
                    if (s[j] != ' ')
                        ++result;
                    else
                        break;
                }

                return result;
            }
        }

        return result;    
    }
};
