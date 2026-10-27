
#include<vector>

class Solution 
{
public:
    int lengthOfLongestSubstring(string s) 
    {
        int maxLen = 95, size = s.size(), arrSize = 256, subSize {}, result {};
        vector<bool> visited(arrSize, false);    // track the unique characters seen for a given substring
        for (int i = 0; i < size; ++i)
        {
            // we've found the longest possible substring
            if (result >= maxLen)
                break;
            
            char c = s[i];
            for (int j = i; j < size && (j - i) <= maxLen;)  // only keep checking if we don't go out of the string's range and if we've checked
            {
                int key = static_cast<unsigned char>(c);
                if (!visited[key])
                {
                    ++subSize;
                    visited[key] = true;
                }
                else
                    break;
                ++j;
                c = s[j];
            }

            result = (subSize > result ? subSize : result);
            subSize = 0;
            fill(visited.begin(), visited.end(), false) ; // reset
        }

        return result;
    }
};
