#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define the Node for the Doubly Linked List
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Define the Deque structure
typedef struct {
    Node* front;
    Node* rear;
    int size;
} Deque;

// Initialize the Deque
Deque* createDeque() {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    dq->front = NULL;
    dq->rear = NULL;
    dq->size = 0;
    return dq;
}

bool empty(Deque* dq) {
    return dq->size == 0;
}

int size(Deque* dq) {
    return dq->size;
}

// 1. push_front
void push_front(Deque* dq, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = dq->front;
    
    if (empty(dq)) {
        dq->rear = newNode;
    } else {
        dq->front->prev = newNode;
    }
    dq->front = newNode;
    dq->size++;
}

// 2. push_back
void push_back(Deque* dq, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = dq->rear;
    
    if (empty(dq)) {
        dq->front = newNode;
    } else {
        dq->rear->next = newNode;
    }
    dq->rear = newNode;
    dq->size++;
}

// 3. pop_front
void pop_front(Deque* dq) {
    if (empty(dq)) return;
    
    Node* temp = dq->front;
    dq->front = dq->front->next;
    
    if (dq->front == NULL) {
        dq->rear = NULL;
    } else {
        dq->front->prev = NULL;
    }
    
    free(temp);
    dq->size--;
}

// 4. pop_back
void pop_back(Deque* dq) {
    if (empty(dq)) return;
    
    Node* temp = dq->rear;
    dq->rear = dq->rear->prev;
    
    if (dq->rear == NULL) {
        dq->front = NULL;
    } else {
        dq->rear->next = NULL;
    }
    
    free(temp);
    dq->size--;
}

// 5. front
int front(Deque* dq) {
    if (empty(dq)) return -1; // Assuming -1 represents empty for this context
    return dq->front->data;
}

// 6. back
int back(Deque* dq) {
    if (empty(dq)) return -1;
    return dq->rear->data;
}

// Additional: clear
void clear(Deque* dq) {
    while (!empty(dq)) {
        pop_front(dq);
    }
}

// Additional: reverse (O(n) time complexity)
void reverse(Deque* dq) {
    Node* current = dq->front;
    Node* temp = NULL;
    
    // Swap next and prev for all nodes
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev; // Move to the next node (which is now prev)
    }
    
    // Swap front and rear pointers
    temp = dq->front;
    dq->front = dq->rear;
    dq->rear = temp;
}

// Helper to print the final state of the deque
void printDeque(Deque* dq) {
    Node* current = dq->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    int n;
    
    // Read the number of operations
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    Deque* dq = createDeque();

    for (int i = 0; i < n; i++) {
        char op[20];
        scanf("%s", op);

        if (strcmp(op, "push_front") == 0) {
            int val;
            scanf("%d", &val);
            push_front(dq, val);
        } 
        else if (strcmp(op, "push_back") == 0) {
            int val;
            scanf("%d", &val);
            push_back(dq, val);
        } 
        else if (strcmp(op, "pop_front") == 0) {
            pop_front(dq);
        } 
        else if (strcmp(op, "pop_back") == 0) {
            pop_back(dq);
        } 
        else if (strcmp(op, "front") == 0) {
            printf("%d\n", front(dq));
        } 
        else if (strcmp(op, "back") == 0) {
            printf("%d\n", back(dq));
        } 
        else if (strcmp(op, "size") == 0) {
            printf("%d\n", size(dq));
        }
        else if (strcmp(op, "empty") == 0) {
            printf("%s\n", empty(dq) ? "true" : "false");
        }
        else if (strcmp(op, "reverse") == 0) {
            reverse(dq);
        }
        else if (strcmp(op, "clear") == 0) {
            clear(dq);
        }
    }

    // Print the final state
    printf("Final Deque: ");
    printDeque(dq);

    // Clean up
    clear(dq);
    free(dq);

    return 0;
}