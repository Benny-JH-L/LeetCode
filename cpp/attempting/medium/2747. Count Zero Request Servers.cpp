
#include<unordered_map>
#include<climits>

class Solution 
{
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) 
    {
        /*
        Idea:
        for each server in `n`
        use a hashtable to record {serverID: [min Time, max Time]}, `min Time` and `max Time` are the smallest and biggest request times. 
        By default, times are set to INT_MAX and -1, respectively. If `min Time` and `max Time` are equal for an entry, then that server recieved a request only at that time.
        If no entry exists with serverID, then it never appeared in the log, and as such didn't get a query.

        Go through `queries` and check if `min Time` or `max Time` is within [queries[i] - x, queries[i]] range, keep track of this count, call it `count`.
        after checking though the hashtable, the number of servers that didn't recieve a request in that duration will be `n` - `count, then update the output at index [i].
        */
        
        unordered_map<int, array<int, 2>> serverRecord {};

        // get server times
        for (vector<int> pair : logs)
        {
            int& serverId = pair[0], &time = pair[1];
            
            // entry does not exist
            if (serverRecord.count(serverId) == 0)
                serverRecord[serverId] = {INT_MAX, -1};

            // check for better time
            array<int, 2>& range = serverRecord[serverId];
            if (time < range[0])   // set new min
                range[0] = time;
            if (time > range[1])   // set new max
                range[1] = time;
        }

        // debug
        for (auto& pair : serverRecord)
        {
            array<int,2>& range = pair.second;
            cout << "id<"<<pair.first<<"> : [" << range[0] << ", " << range[1] << "]\n";
        }
        cout << endl;

        // find servers that recieved a request, and the number of servers that didn't receive one.
        vector<int> results {};

        // for (int i = 0; i < queries.size(); ++i)
        for (int& max : queries)
        {
            int min = max - x;
            int serversReceivedRq {};

            cout << "recieved rq within: ["<<min<<", "<<max<<"]\n";
            for (auto& pair : serverRecord)
            {
                array<int,2>& range = pair.second;
                int& serverMin = range[0];
                int& serverMax = range[1];

                cout << "id<"<<pair.first<<"> : [" << serverMin << ", " << serverMax << "]\n";

                // check if the server got a request within `min` and `max`
                if (serverMin >= min && serverMin <= max)       // server got a request
                    ++serversReceivedRq;
                else if (serverMax >= min && serverMax <= max)  // server got a request
                    ++serversReceivedRq;
                else
                    cout << "\tid<"<<pair.first<<"> not within range" << endl;
            }
            cout << "servers with no rq @ this interval: " << (n - serversReceivedRq) << endl;
            results.push_back(n - serversReceivedRq);
        }

        return results;
    }
};
