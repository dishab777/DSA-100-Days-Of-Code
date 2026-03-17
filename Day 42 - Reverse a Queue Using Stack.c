#include <stdio.h>
#include <stdlib.h>

// --- Queue Implementation ---
typedef struct {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isQueueEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, int item) {
    if (queue->size == queue->capacity) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

// --- Stack Implementation ---
typedef struct {
    int top;
    unsigned capacity;
    int* array;
} Stack;

Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int item) {
    if (stack->top == stack->capacity - 1) return;
    stack->array[++stack->top] = item;
}

int pop(Stack* stack) {
    if (isStackEmpty(stack)) return -1;
    return stack->array[stack->top--];
}

// --- Main Logic ---
int main() {
    int n;
    
    // Read the number of elements
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    Queue* queue = createQueue(n);
    Stack* stack = createStack(n);

    // 1. Read input and enqueue all elements
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        enqueue(queue, val);
    }

    // 2. Dequeue all elements from the queue and push them onto the stack
    while (!isQueueEmpty(queue)) {
        push(stack, dequeue(queue));
    }

    // 3. Pop all elements from the stack and enqueue them back into the queue
    while (!isStackEmpty(stack)) {
        enqueue(queue, pop(stack));
    }

    // 4. Print the reversed queue
    for (int i = 0; i < n; i++) {
        printf("%d", dequeue(queue));
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    // Clean up memory
    free(queue->array); free(queue);
    free(stack->array); free(stack);

    return 0;
}