#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Node for the Linked List
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define the Queue structure with front and rear pointers
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to initialize an empty queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

// Function to add an element to the rear of the queue
void enqueue(Queue* q, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;
    
    // If the queue is empty, the new node is both the front and the rear
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    
    // Add the new node at the end and change rear
    q->rear->next = newNode;
    q->rear = newNode;
}

// Function to remove an element from the front of the queue
int dequeue(Queue* q) {
    // If the queue is empty, return -1
    if (q->front == NULL) {
        return -1;
    }
    
    // Store previous front and move front one node ahead
    Node* temp = q->front;
    int dequeuedValue = temp->data;
    q->front = q->front->next;
    
    // If front becomes NULL, then change rear to NULL as well
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return dequeuedValue;
}

// Function to free the remaining memory
void freeQueue(Queue* q) {
    while (q->front != NULL) {
        dequeue(q);
    }
    free(q);
}

int main() {
    int n;
    
    // Read the number of operations
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    Queue* q = createQueue();

    for (int i = 0; i < n; i++) {
        char op[15];
        scanf("%s", op);

        if (strcmp(op, "enqueue") == 0) {
            int val;
            scanf("%d", &val);
            enqueue(q, val);
        } 
        else if (strcmp(op, "dequeue") == 0) {
            printf("%d\n", dequeue(q));
        }
    }

    freeQueue(q);
    return 0;
}