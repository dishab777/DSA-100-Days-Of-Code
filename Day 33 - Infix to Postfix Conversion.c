#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to return the precedence of an operator
int getPrecedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Function to convert infix expression to postfix
void infixToPostfix(char* exp) {
    int len = strlen(exp);
    char result[1000]; // Assuming maximum expression length of 1000
    int resultIndex = 0;
    
    char stack[1000];
    int top = -1;
    
    for (int i = 0; i < len; i++) {
        char c = exp[i];
        
        // 1. If the character is an operand (letter or digit), add it to the output
        if (isalnum(c)) {
            result[resultIndex++] = c;
        }
        // 2. If the character is an '(', push it to the stack
        else if (c == '(') {
            stack[++top] = c;
        }
        // 3. If the character is an ')', pop to output until '(' is encountered
        else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                result[resultIndex++] = stack[top--];
            }
            if (top >= 0 && stack[top] == '(') {
                top--; // Pop and discard the '('
            }
        }
        // 4. If an operator is scanned
        else {
            while (top >= 0 && (getPrecedence(c) <= getPrecedence(stack[top]))) {
                // Special case for right-associative operator '^'
                if (c == '^' && stack[top] == '^') {
                    break;
                }
                result[resultIndex++] = stack[top--];
            }
            stack[++top] = c; // Push the current operator onto the stack
        }
    }
    
    // Pop all remaining operators from the stack
    while (top >= 0) {
        result[resultIndex++] = stack[top--];
    }
    
    result[resultIndex] = '\0'; // Null-terminate the string
    printf("%s\n", result);
}

int main() {
    char exp[1000];
    
    // Read the infix expression
    if (scanf("%s", exp) != 1) {
        return 1;
    }

    // Convert and print the postfix expression
    infixToPostfix(exp);

    return 0;
}