
#include<stack>

class Solution 
{
public:

    int closedIsland(vector<vector<int>>& grid) 
    {
        /*
        Creating an island and checking if closed:
        1. encounter a '1' skip, otherwise check square adjacency (left, top, right, bottom).
        2. If adjacency has a '0', add that square to be checked next on the stack. This square is visited, and wont be considered again. Skip '1's.
            note if an adjacent square is out-of-bounds we stop checking, and do not add to the count.
        3. if we empty the stack then we have a closed island, and add 1 to the count.

        If the stack is empty, check the next island;
        - Scan the grid for an unvisited '0' to check next.
        */
        int rowSize = grid.size();
        int colSize = grid[0].size();
        vector<bool> visited(rowSize * colSize, false);
        // cout << "row sz: " << rowSize << endl;
        // cout << "col sz: " << colSize << endl;
        // cout << "grid size: " << (rowSize * colSize) << endl;

        vector<array<int, 2>> candidates {};
        for (int i = 0; i < rowSize; ++i)
        {
            for (int j = 0; j < colSize; ++j)
            {
                if (grid[i][j] == 0)
                    candidates.push_back({i,j});
            }
        }

        auto isVisited = [&visited, &colSize](array<int,2>& val) -> bool
        {
            int& r = val[0];
            int& c = val[1];
            // cout << "graph[" << r << "][" << c << "]" << endl;
            // cout << "visited["<<((r * colSize) + c )<<"]" << endl;
            return visited[(r * colSize) + c];
        };
        
        int idxCache {};
        auto findNextCandidate = [&candidates, &idxCache, isVisited]() -> array<int, 2>
        {
            for (int& i = idxCache; i < candidates.size(); ++i)
            {
                auto& arr = candidates[i];
                if (!isVisited(arr))
                    return arr;
            }
            return {-1, -1};
        };

        auto getAdjSq = [&grid, &rowSize, &colSize](int r, int c, vector<array<int, 2>>& squaresRet) -> bool
        {
            bool result = true;
            squaresRet.clear();

            // out of bounds
            if (r+1 >= rowSize || r-1 < 0)
                result = false;
            if (c+1 >= colSize || c-1 < 0)
                result = false;
            
            if (c-1 >= 0 && grid[r][c-1] == 0)
                squaresRet.push_back({r,c-1});      // left
            if (r-1 >= 0 && grid[r-1][c] == 0)
                squaresRet.push_back({r-1,c});      // top
            if (c+1 < colSize && grid[r][c+1] == 0)
                squaresRet.push_back({r,c+1});      // right
            if (r+1 < rowSize && grid[r+1][c] == 0)
                squaresRet.push_back({r+1,c});      // bottom
            return result;
        };
        

        int result {};
        stack<array<int, 2>> island = {};   // array's [0]: row, [1]: col
        array<int, 2> candidate {};
        do 
        {
            candidate = findNextCandidate();

            if (candidate[0] != -1)
                island.push(candidate);
            else
                break;
            
            bool isIslandClosed = true;

            // construct an island
            vector<array<int, 2>> adjSq {};
            while (island.size() > 0)
            {
                int& r = island.top()[0];
                int& c = island.top()[1];
                island.pop();
                visited[(r * colSize) + c] = true;  // dont want to revisit square

                // cout << "r: " << r << " | c: " << c << endl;

                isIslandClosed = isIslandClosed & getAdjSq(r, c, adjSq);   // record if this island is "closed"

                for (auto& arr : adjSq)
                {
                    // only add squares that have not been considered
                    if (!isVisited(arr))
                    {
                        island.push(arr);
                        // cout << "\tadj sq added [" << arr[0] << "][" << arr[1] << "]" << endl; 
                    }
                    // else
                    //     cout << "\tadj sq NOT INC. [" << arr[0] << "][" << arr[1] << "]" << endl; 
                }
            }

            // cout << "island is closed: " << isIslandClosed << endl;

            if (isIslandClosed)
                ++result;
        
        } while (candidate[0] != -1);
        
        return result;
    }
};
