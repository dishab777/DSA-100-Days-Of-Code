#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Core function to evaluate the expression
int calculate(char * s) {
    int len = strlen(s);
    if (len == 0) return 0;
    
    int *stack = (int *)malloc(len * sizeof(int));
    int top = -1;
    
    long currentNumber = 0;
    char operation = '+';
    
    for (int i = 0; i < len; i++) {
        char currentChar = s[i];
        
        if (isdigit(currentChar)) {
            currentNumber = (currentNumber * 10) + (currentChar - '0');
        }
        
        if ((!isdigit(currentChar) && !isspace(currentChar)) || i == len - 1) {
            if (operation == '+') {
                stack[++top] = currentNumber;
            } else if (operation == '-') {
                stack[++top] = -currentNumber;
            } else if (operation == '*') {
                stack[top] = stack[top] * currentNumber;
            } else if (operation == '/') {
                stack[top] = stack[top] / currentNumber; // Truncates toward zero automatically in C
            }
            
            operation = currentChar;
            currentNumber = 0;
        }
    }
    
    int result = 0;
    for (int i = 0; i <= top; i++) {
        result += stack[i];
    }
    
    free(stack);
    return result;
}

int main() {
    // Example 1: "3+2*2" => 7
    char exp1[] = "3+2*2";
    printf("Input: \"%s\"\n", exp1);
    printf("Result: %d (Expected: 7)\n\n", calculate(exp1));

    // Example 2: " 3/2 " => 1
    char exp2[] = " 3/2 ";
    printf("Input: \"%s\"\n", exp2);
    printf("Result: %d (Expected: 1)\n\n", calculate(exp2));

    // Example 3: " 3+5 / 2 " => 5
    char exp3[] = " 3+5 / 2 ";
    printf("Input: \"%s\"\n", exp3);
    printf("Result: %d (Expected: 5)\n", calculate(exp3));

    return 0;
}