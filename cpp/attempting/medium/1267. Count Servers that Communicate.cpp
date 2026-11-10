class Solution 
{
public:
    int countServers(vector<vector<int>>& grid) 
    {
        /*
        Idea:
        Go through the input and find the entry's with a 1 and record the row and col, use two hashmaps and record the entry: 
            row: [col]  - a row key will store multiple col entries. the key and col element pair will form a grid entry.
//            col: [row]  - a col key will store multiple row entries. the key and row element pair will form a grid entry.
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
        */

        int result {};
        return result;
    }
};
