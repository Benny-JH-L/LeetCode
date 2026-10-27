
#include <stack>

class Solution 
{
public:
    int minAddToMakeValid(string s) 
    {
        int moves {};
        stack<char> myStack {};
        myStack.push('1');

        // check closing brackets
        for (char& c : s)
        {
            char& top = myStack.top();

            if (c == ')')
            {
                if (top == '(')
                    myStack.pop();
                else
                    ++moves;
            }
            else
                myStack.push(c);
        }

        // cout << "top -> ";
        // while (myStack.size() > 0)
        // {
        //     cout << myStack.top() << ", ";
        //     myStack.pop();
        // }


        // stuff on the stack are open brackets that need closing brackets. -1 for offset
        return moves + myStack.size() - 1;
    }
};
