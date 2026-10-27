
#include<unordered_set>
#include<unordered_map>
#include<stack>
#include<cmath>

class Solution 
{
public:
    
    class Node
    {
        public:
            unordered_set<int> set {};
            int start {};
            int end {};
            Node* parent = nullptr;

            Node(int s, int e, Node* p) : parent(p), start(s), end(e)
            {}

            string toString()
            {
                return "[" + to_string(start) + ":" + to_string(end) +"]";
            }
    };

    unordered_map<string, Node*> nodeCache {};

    bool MakeNode(int s, int e, vector<int>& nums, Node* parent, Node*& retNode)
    {
        // end of array, can't make more nodes
        if (e >= nums.size())
            return false;
        
        string key = to_string(s) + to_string(e);

        // check if node exists already
        if (nodeCache.count(key) > 0)
        {
            // retNode = nodeCache[key];
            return false;
        }

        retNode = new Node(s,e,parent);

        // get parent set if current range is more than one element
        if (parent != nullptr && s != e)
            retNode->set = parent->set;
        
        retNode->set.insert(nums[e]);
        nodeCache[key] = retNode;
        // cout << "New node made: " << retNode->toString() << " | distinct: " << retNode->set.size() << endl;
        return true;
    }


    int sumCounts(vector<int>& nums) 
    {
        int result {};
        int modulo = 1000000007; // pow(10, 9) + 7;

        Node* root = nullptr;
        MakeNode(0, 0, nums, nullptr, root);
        stack<Node*> nodes {};
        nodes.push(root);

        while (nodes.size() > 0)
        {
            Node* p = nodes.top();
            nodes.pop();

            // cout << "Node<" << p->toString() << ">" << endl;

            result += (p->set.size() * p->set.size());

            Node* child = nullptr;
            if (MakeNode(p->start, p->end + 1, nums, p, child))
                nodes.push(child);
            
            if (MakeNode(p->start + 1, p->end + 1, nums, p, child))
                nodes.push(child);

        }

        return result;

        // for (int subarrSize = nums.size(); subarrSize > 0; --subarrSize)
        // {
        //     // build sub arrays of size `subarrSize`
        //     for (int i = 0; i < nums.size() && i + subarrSize <= nums.size(); ++i)
        //     {
        //         unordered_set<int> distinct {};
        //         for (int j = 0; j < subarrSize; ++j)
        //         {
        //             // cout << "elem: " << nums[i+j] << endl;
        //             distinct.insert(nums[i+j]);
        //         }

        //         // compute to result
        //         result += (distinct.size() * distinct.size());
        //         result = (result % modulo);
        //         // cout << "curr result: " << result << endl; 
        //     }
        // }
        // return result;
    }
};
