
#include <unordered_map>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>

#define sint short

class Solution 
{
public:
    bool getCandidate(unordered_map<sint, vector<sint>>& serversMap, array<sint,2>& candidate)
    {
        // get an arbitrary server
        for (const auto& [row, colVec] : serversMap)
        {
            // make sure it's not empty 
            if (colVec.size() == 0)
                continue;
            
            candidate = {row, colVec[0]};
            // remove(colVec.begin(), colVec.end(), colVec[0]); // this is done in the main code anyway.
            // cout << "candidate: (" << row << ", " << colVec[0] <<")"<< endl;
            return true;
        }

        candidate = {-1,-1};
        return false ; // no candidate found
    }

    int countServers(vector<vector<int>>& grid) 
    {
        /*
        Idea:
        Go through the input and find the entry's with a 1 and record the row and col, use two hashmaps and record the entry: 
            row: [col]  - a row key will store multiple col entries. the key and col element pair will form a grid entry.
        - we will also use this to consider the next servers, see below.

        Pick some arbitrary server as the starting point. Get all the servers that are long this server's row and col. put them onto a stack to check their 
        rows and cols next. Remove these entries from the map. We can remove these because these servers will belong to the same "communication network" (don't want to revisit them) and wont be visited from other networks.
        Ex. 
        [
        [1,1,1,0],
        [0,1,1,0],
        [0,0,1,0],
        [0,0,0,1]]
        hashmap = {
        0: [0,1,2]
        1: [1,2]
        2: [2]
        3: [3]
        }

        we arbitrarily pick grid entry at (0,1).
        Getting all the servers in the same row and col: [(0,0), (0,2), (1,1)]. we update the map as follows:
        hashmap = {
        0: []
        1: [2]
        2: [2]
        3: [3]
        }
        current communication size = 4 servers.
        On the stack we get (0,2). Getting all the servers along its row and col: [(1,2),(2,2)] update the map:
        hashmap = {
        0: []
        1: []
        2: []
        3: [3]
        }
        current communication size = 6 servers.
        Server entries: [(0,0),(1,1),(1,2),(2,2)] wont contribute to the stack as they will check the hashmap and see nothing for their respective rows and cols.
        checking the next entry we only get 1. and the max of (6,1) is 6, which is the result.

        Note: If there are ((m*n)/2) +1 servers, that means all the servers are connected.
        */

        unordered_map<sint, vector<sint>> serverMap {};
        int result {};  // track server count for now
        for (int r = 0; r < grid.size(); ++r)
        {
            vector<int>& row = grid[r];
            for (int c = 0; c < row.size(); ++c)
            {
                if (row[c]) // check if it is '1'
                {
                    serverMap[r].push_back(c);    // add to the map
                    ++result;
                }
            }
        }

        // quick check: If there are ((m*n)/2)+1 servers, that means all the servers are connected.
        if (result >= (((grid.size()*grid[0].size())/2) + 1))
            return result;

        auto printMap = [&serverMap]()
        {
            for (const auto& [row, colVec] : serverMap)
            {
                cout << row << " : [";
                for (int i = 0; i < colVec.size(); ++i)
                    cout << ""<<colVec[i]<<", ";
                cout << "]" << endl;
            }
        };
        
        result = 0;  // will now count server communication count
        int considering {};
        array<sint, 2> candidate {};
        stack<array<sint, 2>> serverCandidates {};
        
        if (getCandidate(serverMap, candidate))
            serverCandidates.push(candidate);
        // no candidate found
        else
            return 0;
        
        while (serverCandidates.size() > 0)
        {
            candidate = serverCandidates.top();
            serverCandidates.pop();
            
            auto& [row, col] = candidate;

            // cout << "candidate: (" << row << ", " << col <<")"<< endl;
            // cout << "map: \n";
            // printMap();

            // get all servers along its row
            vector<sint>& rowVec = serverMap[row];
            for (sint& rowCol : rowVec)
                serverCandidates.push({row, rowCol});   // add candidates to the stack
            considering += rowVec.size();    // add all the servers along this row
            serverMap[row].clear();     // remove the whole row, do not need to consider it for rest of this "network", or across other "networks"
            
            // cout << "removing row<"<<row<<">\n";
            // printMap();
            
            // get all servers along its col
            for (auto& pair : serverMap)
            {
                const sint& rowKey = pair.first;
                vector<sint>& rVec = pair.second;

                bool rmvCol = false;
                auto it = rVec.begin();
                for (;it < rVec.end(); ++it)  // check this row's elements for `col` match
                {
                    if (*it == col)     // match, add to candidates and remove
                    {
                        serverCandidates.push({rowKey, col});
                        ++considering;
                        rmvCol = true;
                    }
                }

                if (rmvCol)
                    rVec.erase(it, it+1);
            }

            // update `result` based on this "network" size
            if (serverCandidates.size() == 0)
            {
                if (considering > 1)
                    result += considering;
                considering = 0;

                // find another server network
                if (getCandidate(serverMap, candidate))
                    serverCandidates.push(candidate);
                else
                    break;
            }
        }

        return (result == 1 ? 0 : result);  // if result is 1, only communicates with itself, so server is not communicating with other servers.
    }
};
