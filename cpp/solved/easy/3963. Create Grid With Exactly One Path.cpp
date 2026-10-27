
#include<vector>
#include<string>

class Solution 
{
public:
    vector<string> createGrid(int m, int n) 
    {
        /*
        Well since we can return ANY grid where there is exactly one valid path from the top left cell to
        the bottom-right cell, we can have one of the most simple grids where; move to the right until you reach 'n' column
        then we move down 'm' rows.
        */

        vector<string> result {string(n, '.')}; // beginning is just '.' n times
        
        // make rest of the rows
        for (int i = 1; i < m; ++i)
        {
            result.emplace_back(n, '#');    // makes a row of n '#'
            result.back().back() = '.';     // replaces the last '#' in the sequence with a '.'
        }

        return result;
    }
};

