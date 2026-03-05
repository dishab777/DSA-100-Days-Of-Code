#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    int min;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} MinStack;

MinStack* minStackCreate() {
    MinStack* stack = (MinStack*)malloc(sizeof(MinStack));
    stack->head = NULL;
    return stack;
}

void minStackPush(MinStack* obj, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    if (obj->head == NULL) {
        newNode->min = val;
    } else {
        newNode->min = (val < obj->head->min) ? val : obj->head->min;
    }
    newNode->next = obj->head;
    obj->head = newNode;
}

void minStackPop(MinStack* obj) {
    if (obj->head != NULL) {
        Node* temp = obj->head;
        obj->head = obj->head->next;
        free(temp);
    }
}

int minStackTop(MinStack* obj) {
    if (obj->head != NULL) {
        return obj->head->val;
    }
    return 0;
}

int minStackGetMin(MinStack* obj) {
    if (obj->head != NULL) {
        return obj->head->min;
    }
    return 0;
}

void minStackFree(MinStack* obj) {
    Node* curr = obj->head;
    while (curr != NULL) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(obj);
}

int main() {
    MinStack* minStack = minStackCreate();
    
    minStackPush(minStack, -2);
    printf("Pushed -2\n");
    
    minStackPush(minStack, 0);
    printf("Pushed 0\n");
    
    minStackPush(minStack, -3);
    printf("Pushed -3\n");
    
    printf("Current Min: %d (Expected: -3)\n", minStackGetMin(minStack));
    
    minStackPop(minStack);
    printf("Popped\n");
    
    printf("Current Top: %d (Expected: 0)\n", minStackTop(minStack));
    
    printf("Current Min: %d (Expected: -2)\n", minStackGetMin(minStack));
    
    minStackFree(minStack);
    printf("Stack memory freed.\n");

    return 0;
}