
#include<unordered_map>

class Solution 
{
public:
    string vecToStr(vector<int>& vec)
    {
        string s {};
        for (int& i : vec)
            s += to_string(i) + ", ";
        s += "\n";
        return s;
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
        */
        
        // vector<vector<int>> result {{},{1},{2,1},{1,2,2},{2},{2,2}};
        unordered_map<short, unsigned short> occuranceMap {};
        for (int& n : nums)
            ++occuranceMap[n];
        
        vector<short> keysVec {};
        for (auto& pair : occuranceMap)
        {
            keysVec.push_back(pair.first);
            cout << pair.first<<" : " << pair.second << endl;
        }
        
        vector<vector<int>> result {{}};
        // build subsets
        for (int i = 0; i < keysVec.size(); ++i)
        {
            short& i_key = keysVec[i];
            for (short i_occurs = 1; i_occurs <= occuranceMap[i_key]; ++i_occurs)
            {
                vector<int> i_subset (i_occurs, i_key); // subset with value `i_key` with `i_occurs` occurances
                result.push_back(i_subset);
                cout << "i_added: " << vecToStr(i_subset);

                // use `i_subset` to build the subsets with other elements
                for (short j = i+1; j < keysVec.size(); ++j)
                {
                    short& j_key = keysVec[j];

                    // make subset with other elements
                    vector<int> copy = i_subset;
                    for (short otherOccur = 1; otherOccur <= occuranceMap[j_key]; ++otherOccur)
                    {
                        copy.push_back(j_key);
                        result.push_back(copy);
                        cout << "j_added: " << vecToStr(copy);
                    }
                }
            }
        }

        // add the last key
        // vector<int> lastSubsets {};
        // short& key = keysVec[keysVec.size() - 1];
        // for (short occurs = 1; occurs <= occuranceMap[key]; ++occurs)
        // {
        //     lastSubsets.push_back(key);
        //     result.push_back(lastSubsets);
        // }
        return result;
    }
};
