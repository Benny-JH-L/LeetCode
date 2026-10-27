
#include<string>
#include<climits>

class Solution 
{
public:
    bool isDigit(char character, int& ascii_out)
    {
        // ASCII 48 to 57 are digits 0 to 9.
        ascii_out = static_cast<int>(character);
        if (ascii_out >= 48 && ascii_out <= 57)
            return true;
        return false;
    }

    void removeLeadingZeros(string& val)
    {
        int numZeros {};
        for (int i = 0; i < val.size(); ++i)
        {
            if (val[i] == '0')
                ++numZeros;
            else
                break;
        }

        val.erase(val.begin(), val.begin() + numZeros);
    }

    int myAtoi(string s) 
    {
        // remove whitespaces
        string formatted {};

        char& c = s[0];
        for (int i = 0; i < s.size(); ++i)
        {
            c = s[i];
            // cout << "checked: " << c << endl;
            if (c != ' ')
            {
                // add rest of characters (or until we find another space)
                for (;c != ' ' && i < s.size();++i)
                {
                    c = s[i];
                    // cout << "added: " << c << endl;
                    formatted.push_back(c);
                }
                break;
            }
        }

        // cout << "removed all <' '>: " << formatted << endl;

        bool positive = true;
        if (formatted[0] == '-')
        {
            positive = false;
            formatted[0] = '0';  // remove
        }
        else if (formatted[0] == '+')
        {
            formatted[0] = '0';
        }
        
        // skip leading 0s
        removeLeadingZeros(formatted);
        // cout << "skip leading 0s\n formatted: " << formatted << endl;

        // read
        // string strResult = (positive ? "" : "-");
        string strResult {};
        int ascii {};
        for (int i = 0; i < formatted.size(); ++i)
        {
            if (isDigit(formatted[i], ascii))
                strResult.push_back(ascii);
            // stop reading when encounered non digit char
            else
                break;
            
            // cout << "char checked: " << formatted[i] << " | ascii checked = " << ascii << endl;
        }

        // cout << "strResult = " << strResult << endl;

        // convert & check
        // 2^31 - 1 = 2147483647    // 10 characters long
        // -2^31 = -2147483648      // 10 characters long (without the sign)
        if (strResult.size() > 10 && positive)
            return INT_MAX;
        if (strResult.size() > 10 && !positive)
            return INT_MIN;
                
        long long result {};
        long long placement = 1;

        for (int index = strResult.size() - 1; index >= 0; --index)
        {
            // cout << "char to convert: " << strResult[index] << " | int val: " << (static_cast<int>(strResult[index])-48) << endl;
            result += (static_cast<int>(strResult[index] - 48) * placement);
            placement *= 10;    // shift over placement
        }

        if (!positive)
            result = -result;

        // cout << "result before constraint: " << result << endl;

        if (result > INT_MAX)
            return INT_MAX;
        else if (result < INT_MIN)
            return INT_MIN;

        return result;
    }
};
