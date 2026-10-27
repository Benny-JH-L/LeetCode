
#include<vector>

class Solution 
{
public:
    void printVec(vector<vector<char>>& zigArr)
    {
        string r = "\n";
        for (auto& row : zigArr)
        {
            string tmp {};
            for (char& c : row)
            {
                tmp += c;
            }
            r = r + tmp + "\n";
        }
        cout << r << endl;
    }

    string convert(string s, int numRows) 
    {
        /*
        Idea 1:
        Use a 2D array to represent the zigzag, size: numRow * round(s.size() / 2.0)

        build the array:
        read the input and fill the array:
            1) going down (from index 0 to numRow-1), until you reach the end of the array. Once reach the end: do 2)
            2) diagonal: fill the array diagonally until the row is < 0 (out of range).
        
        build the output:
        read the array line by line and ignore '/' that fills the array where s's chars didnt cover.

        Idea 2:
        use the same idea but use a a linked list type of implementation instead of a 2D list.
        This way we dont sparsely fill the array and we only store the chars needed to build the array. This method will improve the speed and space complexity.

        ex.
        To make this solution use up less space and be quicker, we can use a linked list for each row and only store the required chars, instead of sparsely filling a 2D array

        For example in "PAYPALISHIRING"
        r=0,c=0
        LL[0].append(s[0])
        r=1
        LL[1].app(s[1])
        r=2
        LL[2].app(s[2])
        r=3
        LL[3].app(s[3])
        r=4 -> time to switch to diag, which is just going back up the linked list, set r=2
        LL[2].app(s[4])
        ...

        build the zig zag result by reading line by line of the linked list.
        */
        if (numRows >= s.size() || numRows == 1)
            return s;
        
        // char ignoreChar = '/';
        int colSize = round(s.size() / 2.0);
        // cout << "num cols: " << colSize << endl;

        // vector<vector<char>> zigArr (numRows, vector<char>(colSize, ignoreChar));
        vector<vector<char>> zigArr (numRows);
        // printVec(zigArr);

        bool goDown = true; // false means go diagonally
        int r {};
        for (int i = 0; i < s.size(); ++i)
        {
            char& cr = s[i];
            zigArr[r].emplace_back(cr);
            // cout << "editing: zigArr["<<r<<"][" << c << "]" <<endl;

            if (goDown)
            {
                ++r;
                // switch to diagonal
                if (r >= numRows)
                {
                    goDown = false;
                    r -= 2;
                    // cout << endl;
                }
            }
            else
            {
                --r;
                // swith to down
                if (r < 0)
                {
                    goDown = true;
                    r += 2;
                    // cout << endl;
                }
            }
        }

        // printVec(zigArr);

        // build the zig zagged string
        string result {};
        for (vector<char>& line : zigArr)
        {
            for (char& chr : line)
            {
                // if (chr != ignoreChar)
                result += chr;
            }
        }
        return result;
    }
};
