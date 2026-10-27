
#include <stack>

class Solution 
{
public:
    bool isValid(string s) 
    {
        stack<char> myStack {};
        myStack.push('1');

        for (char& c : s)
        {
            char top = myStack.top();
            if (c == ')')
            {
                if (top == '(')
                    myStack.pop();
                else
                    return false;
            }
            else if (c == '}')
            {
                if (top == '{')
                    myStack.pop();
                else
                    return false;
            }
            else if (c == ']')
            {
                if (top == '[')
                    myStack.pop();
                else
                    return false;
            }
            else
                myStack.push(c);
        }

        // stack will contain at least the char '1'
        if (myStack.size() >= 2)
            return false;

        return true;
    }
};
