// Exercise 9.52:
/*
 Use a stack to process parenthesized expressions.
 When you see an open parenthesis, note that it was seen.
 When you see a close parenthesis after an open parenthesis, pop elements down to and including the open parenthesis off the stack. push a value onto the stack to indicate that a parenthesized expression was replaced.
 
 >> Have simplified instructions, don't want to spend too much time on one exercise
 >> jaege has covered an exmaple on his GitHub
*/

#include <stack>
#include <string>
#include <iostream>

int calcExpr(const std::string &s)
{
    // split characters into variables
    return sum;
}

void simplify(cosnt std::string &s)
{
    // create empty stack
    std::stack<char> stk;
    
    // push each character of pe to stack
    for (auto &e : pe) {
        stk.push(e);
        // check if stk.top() is '('
            // start recording temporary expression after '(' to string e.g. 5+5
            // count steps up to and including ')'
            // pass final expression to function that calculates "5+5" expression
            // pop however long the expression was
            // push simplified expression from function in place is parenthesised expression and carry on with loop
    }
    
    // print contents of stk
}

int main()
{
    // example parenthesised expression below
    // exercise could have given an example expression to make context clearer...
    simplify("(5+5) * (6+4)");
    
    return 0;
}
