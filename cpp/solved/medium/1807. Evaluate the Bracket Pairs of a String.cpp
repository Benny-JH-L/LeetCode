
#include <unordered_map>
#include <string>

class Solution 
{
public:

    unordered_map<string, string> fasterKnowledge {};

    string evaluate(string s, vector<vector<string>>& knowledge) 
    {
        // go through string and find a key denoted by "()" brackets
        // then in the knowledge base find if the key exists, if it does replace the bracketed key with that value; otherwise replace with `?`

        string result = {};
        int keyEnd {};
        string value {};

        // build the better mapping
        for (vector<string>& pair : knowledge)
        {
            fasterKnowledge[pair[0]] = pair[1];
        }

        for (int keyStart = 0; keyStart < s.size(); ++keyStart)
        {
            // cout << "result (before): " << result << " | size: " << result.size() << endl;

            if (s[keyStart] == '(')
            {
                // find key end
                for (int end = keyStart; end < s.size(); ++end)
                {
                    if (s[end] == ')')
                    {
                        keyEnd = end;
                        break;
                    }
                }

                // get key
                string key = s.substr(++keyStart, keyEnd - keyStart);
                // cout << "key: '" << key << "'" << endl;
                // cout << "\tkeyStart: " << keyStart << endl;
                // cout << "\tkeyEnd: " << keyEnd << endl;
                // cout << "\tkeyEnd - keyStart: " << keyEnd - keyStart << endl;

                // get value
                if (fasterKnowledge.count(key) > 0)
                    value = fasterKnowledge[key];
                else
                    value = "?";

                // replace key with value
                result += value;

                keyStart += key.size(); // skip

                // cout << "result = " << result;
                // cout << "\nkeyStart Pos: " << keyStart << endl;
            }
            else
                result += s[keyStart];
        }

        return result;
    }
};
