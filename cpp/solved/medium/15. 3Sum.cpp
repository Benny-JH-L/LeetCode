
#include<unordered_map>
#include<string>
#include<algorithm>

class Solution 
{
public:
    void getKey(vector<int>& v, string& keyOut)
    {
        sort(v.begin(), v.end());
        keyOut = {};
        for (int& i : v)
            keyOut += to_string(i);
    }

    vector<vector<int>> threeSum(vector<int>& nums) 
    {
        /*
        Idea:
        - count the number of occurances that each number appears in a hash map.
        - Set nums to a new array containing only 1 instance of each number in the hashmap, call it `nums2`
        - Now it is a 2-sum similar problem;
            iterate through `nums2` taking the sum 'a' = nums2[i] + nums2[j], where i != j.
            now using the hashmap check is there an element '-a' that will make the total sum 0.
            Note: you will need to check if there's an available '-a' to use because nums2[i] and or nums2[j] could use up all of '-a'.
        
        ex. nums = [-1,0,1,2,-1,-4]
        map = {(-1: 2),(0: 1), (1: 1), (2: 1), (-4: 1)}
        nums2 = [-1,0,1,2,-4]   // order doesn't matter
        
        we will eventually get to the sum 'a' = nums[0] + nums[3] = -1 + 2 = 1
        we check the map for '-a' (which is -1), notice how we used an instance of -1 and we want to get another -1. Luckily the map says we can use at most 2 '-1's.
        Thus a solution we have is [-1,-1,2].
        */

        unordered_map<int, int> map {};
        for (int& i : nums)
            ++map[i];
        
        vector<int> nums2 {};
        for (auto& pair : map)
            nums2.push_back(pair.first);    // put the value into the vector
        
        // find solutions
        unordered_map<string, int> cache {};
        string key {};
        vector<vector<int>> results {};
        for (auto i = nums2.begin(); i != nums2.end(); ++i)
        {
            int& n1 = *i;
            --map[n1];
            for (auto j = nums2.begin(); j != nums2.end(); ++j)
            {              
                int& n2 = *j;
                // cout << "n1: " << n1 << "\nn2: " << n2 << endl;
                // cout << "map["<<n1<<"] - 2: " << (map[n1] - 2) << endl;
                // check if we used up the same val
                if (n1 == n2 && map[n1] - 1 < 0)
                    continue;
                
                int a = n1 + n2;
                --map[n2];
                int negA = -a;
                // cout << (n1) << " + " << (n2) << " = " << a << endl;
                // cout << "map["<<negA<<"]: " << map[negA] << endl;
                if (map.count(negA) > 0 && map[negA] > 0)  // check if value exists and if we have available instances of '-a' to use
                {
                    // check if 'v' has already been added
                    vector<int> v = {n1, n2, negA};
                    getKey(v, key);

                    // only add result if its unique
                    if (cache.count(key) < 1)
                    {
                        // cout << "key added: " << key << endl;
                        ++cache[key];
                        results.push_back(v);
                    }
                }
                // cout << endl;
                ++map[n2];
            }
            ++map[n1];
        }
        return results;
    }
};
