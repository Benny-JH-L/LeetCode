
#include<algorithm>
#include<stack>

class Solution 
{
public:

    int recur(string& s, int& index)
    {
        if (index > s.size())
            return 0;
        
        int score {};

        if (s[index] == s[index + 1] && s[index] == '(') //"(("
        {
            score = 2 * recur(s, ++index);
        }
        else if (s[index] != s[index + 1] && s[index] == '(')  //"()"
        {
            score = 1;
        }
        else 
            score = recur(s, ++index);

        if (index < s.size())
            score += recur(s, ++index);

        return score;
    }

    int scoreOfParentheses(string s) 
    {
        /*
        reading the input from back to front.
        check current char, if current char is ')' and the next is ')' then
        we need to multiply by 2 - nesting.
        if we see a "()" then no more nesting.
        */

        int index {};
        return recur(s, index);
        
        // // case 1: nesting "(("
        // int score = {};
        // if (s[index] == '(')
        // {
        //     if (s[index + 1] == '(')
        //     {
        //         score = 2 * recur(s, ++index);
        //     }
        //     else
        //     {
        //         score = 1 + recur(s, ++index);
        //     }
        // }
        // // case 2: stop nesting ")"
        // else
        // {
        //     if (s[index + 1] == ')')
        //     {
        //         score = recur(s, ++index);
        //     }
        //     else
        //         score = recur(s, ++index);
        // }

        int score {};
        stack<int> operands {};
        stack<char> operations {};
        stack<char> brackets {};

        for (int i = 0; i < s.size(); ++i)
        {
            char& c = s[i];

            if (c == '(')
                brackets.push(c);
            // "()"
            else
            {
                if (i + 1 > s.size() || (brackets.size() == 1))   // reached the end and brackets enclose whole expression
                {
                    score *= 2;
                }

                brackets.pop(); // '('

                int tmpScore = 1;
                // check for nesting
                for (int& j = ++i; j < s.size() && brackets.size() > 0; ++j)
                {
                    char& c2 = s[j];

                    if (c2 == ')')  // nested
                    {
                        brackets.pop(); // '('
                        tmpScore *= 2;
                    }
                    // no nesting
                    else
                        break;
                }

                score += tmpScore;
            }
        }

        return score;

        for (int i = s.size() - 1; i > 0; --i)
        {
            char& c1 = s[i];
            char& c2 = s[i - 1];

            if (c1 == ')')
            {
                // "))"
                if (c2 == ')')
                {
                    operands.push(2);
                    operations.push('*');
                }
                // "()"
                else
                {
                    operands.push(1);
                }
            }
            // ")(", c1 == '('
            else if (c2 == ')')
            {
                // encountered a plus
                operations.push('+');
            }
        }

        // debuging
        stack<int> copy = operands;

        cout << "operands -top-> ";
        while (copy.size() > 0)
        {
            cout << copy.top() << ", ";
            copy.pop();
        }
        cout << endl;

        stack<char> copy2 = operations;
        cout << "operations -top-> ";
        while (copy2.size() > 0)
        {
            cout << copy2.top() << ", ";
            copy2.pop();
        }
        cout << endl;

        while (operations.size() > 0)
        {
            char& op = operations.top();
            operations.pop();

            int& oper1 = operands.top();
            operands.pop();
            int& oper2 = operands.top();
            operands.pop();

            cout << oper1 << " " << op << " " << oper2 << endl;

            int tmpScore {};
            if (op == '*')
               tmpScore = (oper1 * oper2); 
            else
                tmpScore = (oper1 + oper2);
            
            operands.push(tmpScore);

            // if (operations.size() == 0 && operands.size() > 1)
            //     operations.push('+');
        }

        return operands.top();
    }
};
