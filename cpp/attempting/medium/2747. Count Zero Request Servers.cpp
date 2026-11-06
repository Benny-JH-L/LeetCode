
#include<unordered_map>
#include<set>
#include<climits>
#include<algorithm>

class Solution 
{
public:
    void printServerTime(vector<int>& serverTimes, const int& serverId)
    {
        // debug
        cout << "id<"<<serverId<<"> : [";
        for (int& i : serverTimes)
            cout << i << ", ";
        cout << "]"<< endl;
    }

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
        
        Idea 2:
        for each server in `n`, that was seen in `logs`
        use a hashtable to record {serverID: vector<int>}, the vector<int> stores all the unique times.
        - If a server has only 1 entry, then it only recieved a request at that one time.
        - If no entry exists with serverID, then it never appeared in the log, and as such didn't get a query.

        after going though `logs`, sort each vector<int> for the server.

        Go through `queries`, for the query, q, it will have the time range [q - x, q],
        In each server in the hash table, check if vector<int> has a entry that exists within [q-x, q]. 
        If within range, keep track of this count, call it `count`. then check the next server.
        - Note: we can use binary search to quickly find if there are any times the server had a request within [q-x,q].
        - ex. if [q-x,q] is [30, 38] and a server has the times [1,2,3,4,5,32,100]
            check the middle time <4>, it is smaller than `30` go right, search range is now from [5,32,100].
            we find 32, stop. But had 32 been bigger than 38 we search left. 
            If we've exhausted the search range, no server didn't have a request from between times [30,38].
        */
        
        unordered_map<int, set<int>>* serverRecordSetPtr = new unordered_map<int, set<int>>();  // get only unique occurances

        // get server times
        for (vector<int> pair : logs)
        {
            int& serverId = pair[0], &time = pair[1];
            
            // entry does not exist
            if (serverRecordSetPtr->count(serverId) == 0)
                (*serverRecordSetPtr)[serverId] = {};
            
            (*serverRecordSetPtr)[serverId].insert(time);
        }

        // build the record
        unordered_map<int, vector<int>> serverRecord {};
        for (auto& pair : (*serverRecordSetPtr))
        {
            vector<int>& serverTimes = serverRecord[pair.first];
            serverTimes = {};
            for (int i : pair.second)
                serverTimes.push_back(i);
            sort(serverTimes.begin(), serverTimes.end());
        }

        // no longer needed
        delete serverRecordSetPtr;
        serverRecordSetPtr = nullptr;


        // debug
        // for (auto& pair : serverRecord)
        // {
        //     cout << "id<"<<pair.first<<"> : [";
        //     for (int& i : pair.second)
        //         cout << i << ", ";
        //     cout << "]"<< endl;
        // }
        // cout << endl;

        // find servers that recieved a request, and the number of servers that didn't receive one.
        vector<int> results {};

        // for (int i = 0; i < queries.size(); ++i)
        for (int& max : queries)
        {
            int min = max - x;
            int serversReceivedRq {};

            // cout << "recieved rq within: ["<<min<<", "<<max<<"]\n";
            for (auto& pair : serverRecord)
            {
                vector<int>& serverTimes = pair.second;
                // printServerTime(serverTimes, pair.first); // debug

                // binary search `serverTimes` for a time within `min` and `max`.
                int left {}, right = serverTimes.size()-1, middle = right / 2;
                while (left <= right)
                {
                    int& time = serverTimes[middle];
                    
                    // server got a request
                    if ((time >= min && time <= max) || (time >= min && time <= max))
                    {
                        ++serversReceivedRq;
                        // cout << "\tid<"<<pair.first<<"> within range @ time<"<<time<<">" << endl;
                        break;  // stop searching
                    }

                    if (time < min)
                        left = middle + 1;
                    else if (time > max)
                        right = middle - 1;
                    middle = left + floor((right - left) / 2.0);
                }
            }

            // cout << "servers with no rq @ this interval: " << (n - serversReceivedRq) << endl;
            results.push_back(n - serversReceivedRq);
        }

        return results;
    }
};
