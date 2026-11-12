
#include<climits>
#include<vector>
#include<cmath>

class Solution 
{
public:
    int climbStairs(int n, vector<int>& costs) 
    {
        /*
        Idea:
        Let `DP` be an array of size `n`, that stores the min cost of getting from step `i` to `j` where `i+1` <= j <= `i+3`
            - the index of DP will represent the step and DP[i] will be the min cost to get to step `i`.
        
        (Optional for debugging, DP will be storing the accumulated min cost for each step anyway)
        Let `Path` be an array of size `n` that stores the path to take to get the min cost from step 0 to step `n`. 
            - the index will represent the step and Path[i] will represent which step to go to. 
            - ex. Path = [0,0,1]
                the min cost to get to step 2 is from step 1, then from step 1 is from step 0.
        
        Example run:
        n = 4, costs = [1,2,3,4]
        DP = [0,+INF,+INF,+INF,+INF]

        Step 0: update cost of getting from step 0 to step 1,2,3

        Step 0 to 1: dp[0] + cost[1] + (1-0)^2 = 0 + 1 +1 = 2 
        Step 0 to 2: dp[0] + cost[2] + (2-0)^2 = 0 + 2 + 4 = 6 
        Step 0 to 3: dp[0] + cost[3] + (3-0)^2 = 0 + 3 + 9 = 12   
        Update DP, keep the min cost.
        DP = [0,2,6,12,+INF]

        Step 1: update cost of getting from step 1 to step 2,3,4

        Step 1 to 2: dp[1] + cost[2] + (2 - 1)^2 = 2 + 1 = 2+3 = 5  
        Step 1 to 3: dp[1] + 3 + (3-1)^2 = 2 + 7 = 9  
        Step 1 to 4: dp[1] + 4 + (4-1)^2 = 2+13=15  
        Update DP, keep the min cost.
        DP = [0,2,5,9,15]

        Step 2: update cost of getting from step 2 to step 3,4

        Step 2 to 3: dp[2] + cost[3] + (3-2)^2 = 5 + 3 + 1 = 9 
        Step 2 to 4: dp[2] + 4 + (4-2)^2 = 5 + 8 = 13   
        Update DP, keep the min cost.
        DP = [0,2,5,9,13]

        Step 3: update cost of getting from step 3 to step 4
        Step 3 to 4: DP[3] + cost[4] + (4-3)^2 = 4+1 = 9 + 5  = 14  
        Update DP, keep the min cost. 
        DP = [0,2,5,9,13] (No change)

        Step 4 to 4 - Terminate.
        return DP[`n`] = DP[4] = 13.
        */

        // for (int i = 1; i < 1001; ++i)
        //     cout << i << ", ";
        // return -1;

        vector<int> dp (n+1, INT_MAX);
        dp[0] = 0;  // start at step 0

        auto printDp = [&dp]()
        {
            cout << "[";
            for (int i = 0; i < dp.size(); ++i)
                cout << dp[i] << ", ";
            cout << "]" << endl;
        };

        for (int i = 0; i < n; ++i)
        {
            // printDp();

            // check steps `i+1`, `i+2`, `i+3`, but do not go over `n-1` steps
            int cost {};
            for (int j = i + 1; j <= min(i + 3, n); ++j)
            {
                cost = dp[i] + costs[j-1] + ((j - i) * (j - i));    // compute the min cost to get to step j from step i, recall `costs` is 1-indexed 
                // cout << "cost = " << "dp["<<i<<"] + " << costs[j-1] << " + " << (((j - i) * (j - i))) << " = " << cost << endl;
                dp[j] = min(cost, dp[j]);                           // store the min cost
            }
        }

        // printDp();
        return dp[n];
    }
};
