#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Core function to evaluate RPN
int evalRPN(char** tokens, int tokensSize) {
    int* stack = (int*)malloc(tokensSize * sizeof(int));
    int top = -1;

    for (int i = 0; i < tokensSize; i++) {
        char* token = tokens[i];
        
        if (token[1] == '\0' && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
            int b = stack[top--];
            int a = stack[top--];
            
            if (token[0] == '+') {
                stack[++top] = a + b;
            } else if (token[0] == '-') {
                stack[++top] = a - b;
            } else if (token[0] == '*') {
                stack[++top] = a * b;
            } else if (token[0] == '/') {
                stack[++top] = a / b;
            }
        } else {
            stack[++top] = atoi(token);
        }
    }

    int result = stack[top];
    free(stack);
    return result;
}

int main() {
    // Example 1: ["2","1","+","3","*"]  => ((2 + 1) * 3) = 9
    char* tokens1[] = {"2", "1", "+", "3", "*"};
    int size1 = 5;
    printf("Result 1: %d (Expected: 9)\n", evalRPN(tokens1, size1));

    // Example 2: ["4","13","5","/","+"] => (4 + (13 / 5)) = 6
    char* tokens2[] = {"4", "13", "5", "/", "+"};
    int size2 = 5;
    printf("Result 2: %d (Expected: 6)\n", evalRPN(tokens2, size2));

    // Example 3: ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
    char* tokens3[] = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    int size3 = 13;
    printf("Result 3: %d (Expected: 22)\n", evalRPN(tokens3, size3));

    return 0;
}