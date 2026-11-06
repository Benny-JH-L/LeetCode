
#include<unordered_map>

class Solution 
{
public:
    vector<unordered_map<short, unsigned short>> subSetsCache {};   // stores all the unique subsets found 

    string vecToStr(vector<int> vec)
    {
        string s = "[";
        for (int& i : vec)
            s += to_string(i) + ", ";
        s += "]\n";
        return s;
    }
    vector<int> setToVec(unordered_map<short, unsigned short> set)
    {
        vector<int> vec {};
        for (const auto& [value, occurs]:set)
        {
            for (int i = 0; i < occurs; ++i)
                vec.push_back(value);
        }
        return vec;
    }

    bool isSetInResults(const unordered_map<short, unsigned short>& set)
    {
        // check if each value in `set` occures the same number of times in a subset found so far
        // get a cached result
        for (auto& cached : subSetsCache)
        {
            // check if the cached result has the same paramaters as the `set`.
            bool allSame = true;
            for (const auto& [value, occurs] : set)
            {
                if (cached[value] != occurs)   // found a entry where this cached result doesn't match the `set`
                {
                    allSame = false;
                    break;
                }
            }

            if (allSame)    // found a entry in cached result where all the paramters match `set`
                return true;
        }
        
        return false;
    }

    void recur(unordered_map<short, unsigned short>& set, unordered_map<short, unsigned short>& occuranceMap)
    {
        vector<unordered_map<short, unsigned short>> setsSoFar {};

        // build subsets
        for (const auto& [value, occurances] : occuranceMap)
        {
            // check if we can add another `value` to the current `set`
            if (set[value] == occurances)
                continue;
            
            // add `value` to the current `set`
            unordered_map<short, unsigned short> copy = set;
            ++copy[value];
            setsSoFar.push_back(copy);
        }

        for (unordered_map<short, unsigned short>& subSet : setsSoFar)
        {
            // check if the subset was already added to the result, don't include it in the final result or call it on `recur`
            if (isSetInResults(subSet))
                continue;
            subSetsCache.push_back(subSet);
            // cout << "added set: " << vecToStr(setToVec(subSet)) << endl;
            recur(subSet, occuranceMap);
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) 
    {
        /*
        Idea:
        count the number of occurances for each integer in `nums` and put them into a hashmap.
        Get the keys and put them into a vector<int>, call it v_key, iterate through this list and using the hashmap to generate subsets.
        Ex. hashmap = {(2: 2), (1:2)}, v_key = [1,2] 
            starting index 0, v_key[0] = 1:
            loop though v_key from j = i+1 and go through the hashmap :
                with key `1`, we can make the sub sets:
                j = 1 [1,2], [1,2,2], [1,1,2], [1,1,2,2], put them in the return.
            after looping through the hashmap we can make all the possible sets with v_key[i].
            in this case it is: [1], [1,1], and we put them into the return.

            we return all the results with the empty set already in it.
            - Fails
        
        Idea 2:
        count the number of occurances for each integer in `nums` and put them into a hashmap.
        We use recurrsion, to find all unique subsets. Let's use hashmap = {(2: 2), (1:2)}, v_key = [1,2] for the explanation.
        The function `recur` that takes a set, `setSoFar`, and a copy of the hashmap.
        `recur` will build the subsets with `setSoFar`, then call itself for each of those subsets.
        Initially we sent the set {1} and it built the following subsets: {1,1}, {1,2}.
        recur {1,1}: it notices that it can't use any more `1`s, so it will add a 2 -> {1,2,2}
            recur {1,2,2}: notices it can't use any more `2`s, so it will add a 1 -> {1,2,2,1}
                recur {1,2,2,1}: notices it cannot use any more values, returns.
        recur {1,2}: makes the sets {1,1,2}, {1,2,2} but because we built {1,2,2} already it wont call itself with it.
            recur {1,1,2}: notices it cannot use any more `1`s adds a `2` -> {1,1,2,2}, but {1,1,2,2} has been build already, so returns.
        
        sets found so far: {} {1}, {1,1}, {1,2,2}, {1,2,2,1}, {1,2}, {1,1,2}
        
        next we call `recur` with {2}
        recur {2}: {2,1}, {2,2}, set {2,1} has already been made.
            recur {2,2}: {2,2,1}, set {2,2,1} has already been made.

        power set is: {}, {1}, {1,1}, {1,2,2}, {1,2,2,1}, {1,2}, {1,1,2}, {2}, {2,2}
        note: use a hashmap to represent the sets made, at the end we can convert the hashmaps into the vector<int>
        */

        // vector<vector<int>> result {{},{1},{2,1},{1,2,2},{2},{2,2}};

        unordered_map<short, unsigned short> occuranceMap {};
        for (int& n : nums)
            ++occuranceMap[n];
        
        vector<vector<int>> result {{}};
        for (auto& pair : occuranceMap)
        {
            unordered_map<short, unsigned short> set {};
            set[pair.first] = 1;
            result.push_back({pair.first});
            recur(set, occuranceMap);
        }

        // build the results
        for (auto& set : subSetsCache)
        {
            vector<int> vec {};
            for (const auto& [value, occurs] : set)
            {
                for (int i = 0; i < occurs; ++i)
                    vec.push_back(value);
            }
            result.push_back(vec);
        }
        return result;
    }
};
