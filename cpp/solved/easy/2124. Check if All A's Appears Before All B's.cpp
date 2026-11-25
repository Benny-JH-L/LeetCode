class Solution 
{
public:
    bool checkString(string s) 
    {
        /*
        Idea:
        find the first occurance of 'b', then if we find an 'a' after this 'b' then not all 'a's are before all 'b's.
        */

        bool bFound = false;
        for (char& c : s)
        {
            if (bFound && c == 'a')
                return false;
            if (c == 'b')
                bFound = true;
        }

        return true;
    }
};
