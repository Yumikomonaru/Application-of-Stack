#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

// Function to return precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

// Function to perform arithmetic operations
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

// Function to evaluate the expression
int evaluate(string tokens) {
    int i;
    
    // Stack to store integer values
    stack<int> values;
    
    // Stack to store operators
    stack<char> ops;
    
    for (i = 0; i < tokens.length(); i++) {
        
        // Current token is a whitespace, skip it
        if (tokens[i] == ' ')
            continue;
        
        // Current token is an opening brace, push it to 'ops'
        else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        }
        
        // Current token is a number, push it to stack for numbers
        else if (isdigit(tokens[i])) {
            int val = 0;
            
            // There may be more than one digits in the number
            while (i < tokens.length() && isdigit(tokens[i])) {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }
            values.push(val);
            
            // right now the i points to the character next to the digit,
            // since the for loop also increases the i, we decrease i by 1
            i--;
        }
        
        // Closing brace encountered, solve the entire brace
        else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top();
                values.pop();
                
                int val1 = values.top();
                values.pop();
                
                char op = ops.top();
                ops.pop();
                
                values.push(applyOp(val1, val2, op));
            }
            
            // Pop opening brace
            if (!ops.empty())
               ops.pop();
        }
        
        // Current token is an operator
        else {
            // While top of 'ops' has same or greater precedence to current
            // token, which is an operator. Apply operator on top of 'ops'
            // to top two elements in values stack
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                int val2 = values.top();
                values.pop();
                
                int val1 = values.top();
                values.pop();
                
                char op = ops.top();
                ops.pop();
                
                values.push(applyOp(val1, val2, op));
            }
            
            // Push current token to 'ops'
            ops.push(tokens[i]);
        }
    }
    
    // Entire expression has been parsed at this point, apply remaining ops
    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();
        
        int val1 = values.top();
        values.pop();
        
        char op = ops.top();
        ops.pop();
        
        values.push(applyOp(val1, val2, op));
    }
    
    // Top of 'values' contains the result
    return values.top();
}

int main() {
    string expression;
    cout << "Enter an infix expression: ";
    getline(cin, expression);
    
    cout << "Result: " << evaluate(expression) << endl;
    
    return 0;
}


// Inpute: 3 + 5 - 2 * 3 / 2
// Result: 5
