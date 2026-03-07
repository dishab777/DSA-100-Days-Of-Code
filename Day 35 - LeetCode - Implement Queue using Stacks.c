#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int s1[MAX_SIZE];
    int top1;
    int s2[MAX_SIZE];
    int top2;
} MyQueue;

MyQueue* myQueueCreate() {
    MyQueue* obj = (MyQueue*)malloc(sizeof(MyQueue));
    obj->top1 = -1;
    obj->top2 = -1;
    return obj;
}

void myQueuePush(MyQueue* obj, int x) {
    obj->s1[++(obj->top1)] = x;
    printf("Pushed %d to queue.\n", x);
}

void transferIfEmpty(MyQueue* obj) {
    if (obj->top2 == -1) {
        while (obj->top1 >= 0) {
            obj->s2[++(obj->top2)] = obj->s1[(obj->top1)--];
        }
    }
}

int myQueuePop(MyQueue* obj) {
    transferIfEmpty(obj);
    int val = obj->s2[(obj->top2)--];
    printf("Popped %d from queue.\n", val);
    return val;
}

int myQueuePeek(MyQueue* obj) {
    transferIfEmpty(obj);
    return obj->s2[obj->top2];
}

bool myQueueEmpty(MyQueue* obj) {
    return (obj->top1 == -1 && obj->top2 == -1);
}

void myQueueFree(MyQueue* obj) {
    free(obj);
    printf("Queue memory freed.\n");
}

int main() {
    // 1. Initialize the queue
    MyQueue* myQueue = myQueueCreate();
    printf("Queue initialized.\n");

    // 2. Push 1
    myQueuePush(myQueue, 1); // queue is: [1]

    // 3. Push 2
    myQueuePush(myQueue, 2); // queue is: [1, 2] (leftmost is front)

    // 4. Peek
    int front = myQueuePeek(myQueue);
    printf("Front element is: %d (Expected: 1)\n", front); // return 1

    // 5. Pop
    myQueuePop(myQueue); // return 1, queue is [2]

    // 6. Check if empty
    bool isEmpty = myQueueEmpty(myQueue);
    printf("Is queue empty? %s (Expected: false)\n", isEmpty ? "true" : "false"); // return false

    // Clean up
    myQueueFree(myQueue);

    return 0;
}