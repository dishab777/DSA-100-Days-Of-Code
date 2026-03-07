#include <stdio.h>
#include <stdlib.h>

// Define the Queue structure using an array
struct Queue {
    int front;
    int rear;
    int capacity;
    int* array;
};

// Function to create a queue with dynamic memory allocation
struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    // Dynamically allocate memory for the array based on capacity
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

// Function to add an item to the rear of the queue
void enqueue(struct Queue* queue, int item) {
    // Check if queue is full
    if (queue->rear == queue->capacity - 1) {
        return; 
    }
    // Increment rear and add the item
    queue->array[++queue->rear] = item;
}

// Function to display the queue from front to rear
void displayQueue(struct Queue* queue) {
    // Check if queue is empty
    if (queue->front > queue->rear) {
        return; 
    }
    // Traverse from front pointer to rear pointer
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d", queue->array[i]);
        if (i < queue->rear) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int n;
    
    // Read the number of elements
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    // Create a queue of capacity 'n'
    struct Queue* queue = createQueue(n);

    // Read n elements and enqueue them
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        enqueue(queue, val);
    }

    // Display the queue
    displayQueue(queue);

    // Clean up dynamically allocated memory
    free(queue->array);
    free(queue);

    return 0;
}