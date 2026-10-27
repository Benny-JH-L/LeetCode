class Solution 
{
public:
    int countIslands(vector<vector<int>>& grid, int k) 
    {
        int rowSize = grid.size();
        int colSize = grid[0].size();
        vector<bool> visited(rowSize * colSize, false);
        // cout << "row sz: " << rowSize << endl;
        // cout << "col sz: " << colSize << endl;
        // cout << "grid size: " << (rowSize * colSize) << endl;

        vector<array<int, 2>> candidates {};    // store all non-zero value locations
        for (int i = 0; i < rowSize; ++i)
        {
            for (int j = 0; j < colSize; ++j)
            {
                if (grid[i][j] != 0)
                {
                    // cout << "found candidate @: [" << i << "][" << j << "]" << endl; 
                    candidates.push_back({i,j});
                }
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

        int candidateIdx {};    // cache the candidate index
        auto findNextCandidate = [&candidates, &candidateIdx, &isVisited]() -> array<int, 2>
        {
            for (int& i = candidateIdx; i < candidates.size(); ++i)
            {
                auto& arr = candidates[i];
                if (!isVisited(arr))
                    return arr;
            }

            return {-1, -1};
        };

        auto getAdjSq = [&grid, &rowSize, &colSize](int& r, int& c, vector<array<int, 2>>& squaresRet)
        {
            // bool result = true;
            squaresRet.clear();
            
            if (c-1 >= 0 && grid[r][c-1] != 0)
                squaresRet.push_back({r,c-1});      // left
                
            if (r-1 >= 0 && grid[r-1][c] != 0)
                squaresRet.push_back({r-1,c});      // top
                
            if (c+1 < colSize && grid[r][c+1] != 0)
                squaresRet.push_back({r,c+1});      // right

            if (r+1 < rowSize && grid[r+1][c] != 0)
                squaresRet.push_back({r+1,c});      // bottom
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
            
            int islandVal {};

            // construct an island
            vector<array<int, 2>> adjSq {};
            while (island.size() > 0)
            {
                int& r = island.top()[0];
                int& c = island.top()[1];
                islandVal = (islandVal + (grid[r][c] % k)) % k;
                visited[(r * colSize) + c] = true;  // dont want to revisit square
                island.pop();

                // cout << "r: " << r << " | c: " << c << endl;

                getAdjSq(r, c, adjSq);

                for (auto& arr : adjSq)
                {
                    // only add squares that have not been considered
                    if (!isVisited(arr))
                    {
                        island.push(arr);
                        visited[(arr[0] * colSize) + arr[1]] = true;  // dont want to revisit square
                        // cout << "\tadj sq added [" << arr[0] << "][" << arr[1] << "]" << endl; 
                    }
                    // else
                        // cout << "\tadj sq NOT INC. [" << arr[0] << "][" << arr[1] << "]" << endl; 
                }
            }

            if (islandVal % k == 0)
            {
                ++result;
                // cout << "found!" << endl;
            }
        
        } while (candidate[0] != -1);
        
        return result;
    }
};
