#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
} MyCircularDeque;

MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque* obj = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    obj->capacity = k;
    obj->size = 0;
    obj->data = (int*)malloc(k * sizeof(int));
    obj->front = 0;
    obj->rear = k - 1; 
    return obj;
}

bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    return obj->size == 0;
}

bool myCircularDequeIsFull(MyCircularDeque* obj) {
    return obj->size == obj->capacity;
}

bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    if (myCircularDequeIsFull(obj)) return false;
    obj->front = (obj->front - 1 + obj->capacity) % obj->capacity;
    obj->data[obj->front] = value;
    obj->size++;
    return true;
}

bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    if (myCircularDequeIsFull(obj)) return false;
    obj->rear = (obj->rear + 1) % obj->capacity;
    obj->data[obj->rear] = value;
    obj->size++;
    return true;
}

bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) return false;
    obj->front = (obj->front + 1) % obj->capacity;
    obj->size--;
    return true;
}

bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) return false;
    obj->rear = (obj->rear - 1 + obj->capacity) % obj->capacity;
    obj->size--;
    return true;
}

int myCircularDequeGetFront(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) return -1;
    return obj->data[obj->front];
}

int myCircularDequeGetRear(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) return -1;
    return obj->data[obj->rear];
}

void myCircularDequeFree(MyCircularDeque* obj) {
    free(obj->data);
    free(obj);
}

int main() {
    // Initialize deque with capacity 3
    MyCircularDeque* myCircularDeque = myCircularDequeCreate(3);
    printf("Deque created with capacity 3.\n");

    printf("insertLast(1): %s\n", myCircularDequeInsertLast(myCircularDeque, 1) ? "true" : "false"); // return True
    printf("insertLast(2): %s\n", myCircularDequeInsertLast(myCircularDeque, 2) ? "true" : "false"); // return True
    printf("insertFront(3): %s\n", myCircularDequeInsertFront(myCircularDeque, 3) ? "true" : "false"); // return True
    
    // Deque is now full: [3, 1, 2]
    printf("insertFront(4): %s\n", myCircularDequeInsertFront(myCircularDeque, 4) ? "true" : "false"); // return False, it is full
    
    printf("getRear(): %d\n", myCircularDequeGetRear(myCircularDeque)); // return 2
    printf("isFull(): %s\n", myCircularDequeIsFull(myCircularDeque) ? "true" : "false"); // return True
    printf("deleteLast(): %s\n", myCircularDequeDeleteLast(myCircularDeque) ? "true" : "false"); // return True
    
    // Deque is now: [3, 1]
    printf("insertFront(4): %s\n", myCircularDequeInsertFront(myCircularDeque, 4) ? "true" : "false"); // return True
    
    // Deque is now: [4, 3, 1]
    printf("getFront(): %d\n", myCircularDequeGetFront(myCircularDeque)); // return 4

    myCircularDequeFree(myCircularDeque);
    printf("Memory freed.\n");

    return 0;
}