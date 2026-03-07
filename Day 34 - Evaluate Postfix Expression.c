#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define the structure for a stack node (linked list)
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to push an element onto the stack
void push(Node** top, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = *top;
    *top = newNode;
}

// Function to pop an element from the stack
int pop(Node** top) {
    if (*top == NULL) {
        printf("Stack Underflow\n");
        exit(1);
    }
    Node* temp = *top;
    int poppedValue = temp->data;
    *top = (*top)->next;
    free(temp);
    return poppedValue;
}

// Function to check if a string is an operator
int isOperator(char* token) {
    return (strlen(token) == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/'));
}

int main() {
    char expr[1000];
    
    // Read the entire line of input
    if (fgets(expr, sizeof(expr), stdin) == NULL) {
        return 1;
    }

    Node* stack = NULL;

    // Tokenize the string using space and newline as delimiters
    char* token = strtok(expr, " \n");

    while (token != NULL) {
        if (isOperator(token)) {
            // Operator found: pop two elements and apply the operator
            int val1 = pop(&stack); // Top element (right operand)
            int val2 = pop(&stack); // Second top element (left operand)
            
            if (token[0] == '+') {
                push(&stack, val2 + val1);
            } else if (token[0] == '-') {
                push(&stack, val2 - val1);
            } else if (token[0] == '*') {
                push(&stack, val2 * val1);
            } else if (token[0] == '/') {
                push(&stack, val2 / val1);
            }
        } else {
            // Operand found: convert to integer and push to stack
            push(&stack, atoi(token));
        }
        
        // Get the next token
        token = strtok(NULL, " \n");
    }

    // The final result will be the only element left in the stack
    int result = pop(&stack);
    printf("%d\n", result);

    return 0;
}