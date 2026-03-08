#include <stdio.h>
#include <stdlib.h>

// Define the Circular Queue structure
struct CircularQueue {
    int front;
    int rear;
    int size;
    int capacity;
    int* array;
};

// Function to create a circular queue with dynamic memory allocation
struct CircularQueue* createQueue(int capacity) {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->size = 0;
    queue->rear = capacity - 1; // Initialize rear to end so first enqueue wraps to 0
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

// Function to check if the queue is full
int isFull(struct CircularQueue* queue) {
    return (queue->size == queue->capacity);
}

// Function to check if the queue is empty
int isEmpty(struct CircularQueue* queue) {
    return (queue->size == 0);
}

// Function to add an item to the queue
void enqueue(struct CircularQueue* queue, int item) {
    if (isFull(queue)) return;
    
    // Rear wraps around to 0 if it reaches the capacity
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

// Function to remove an item from the queue
int dequeue(struct CircularQueue* queue) {
    if (isEmpty(queue)) return -1;
    
    int item = queue->array[queue->front];
    // Front wraps around to 0 if it reaches the capacity
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    
    return item;
}

// Function to display the queue elements from front to rear
void displayQueue(struct CircularQueue* queue) {
    if (isEmpty(queue)) return;
    
    int count = queue->size;
    int index = queue->front;
    
    for (int i = 0; i < count; i++) {
        printf("%d", queue->array[index]);
        if (i < count - 1) {
            printf(" ");
        }
        index = (index + 1) % queue->capacity;
    }
    printf("\n");
}

int main() {
    int n, m;
    
    // Read the number of elements to enqueue
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    struct CircularQueue* queue = createQueue(n);

    // Read and enqueue the elements
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        enqueue(queue, val);
    }

    // Read the number of dequeue operations
    if (scanf("%d", &m) == 1) {
        // Dequeue 'm' elements and immediately enqueue them back
        // to demonstrate the circular wrap-around and match the expected output
        for (int i = 0; i < m; i++) {
            if (!isEmpty(queue)) {
                int dequeuedItem = dequeue(queue);
                enqueue(queue, dequeuedItem);
            }
        }
    }

    // Display the final state of the queue
    displayQueue(queue);

    // Clean up memory
    free(queue->array);
    free(queue);

    return 0;
}