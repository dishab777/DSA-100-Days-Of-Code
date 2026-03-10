#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* heap;
    int size;
    int k;
} KthLargest;

void heapifyDown(int* heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest]) smallest = left;
    if (right < size && heap[right] < heap[smallest]) smallest = right;

    if (smallest != i) {
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        heapifyDown(heap, size, smallest);
    }
}

void heapifyUp(int* heap, int i) {
    int parent = (i - 1) / 2;
    if (i > 0 && heap[i] < heap[parent]) {
        int temp = heap[i];
        heap[i] = heap[parent];
        heap[parent] = temp;
        heapifyUp(heap, parent);
    }
}

int kthLargestAdd(KthLargest* obj, int val);

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest* obj = (KthLargest*)malloc(sizeof(KthLargest));
    obj->k = k;
    obj->size = 0;
    obj->heap = (int*)malloc(k * sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        kthLargestAdd(obj, nums[i]);
    }
    return obj;
}

int kthLargestAdd(KthLargest* obj, int val) {
    if (obj->size < obj->k) {
        obj->heap[obj->size] = val;
        heapifyUp(obj->heap, obj->size);
        obj->size++;
    } else if (val > obj->heap[0]) {
        obj->heap[0] = val;
        heapifyDown(obj->heap, obj->size, 0);
    }
    return obj->heap[0];
}

void kthLargestFree(KthLargest* obj) {
    free(obj->heap);
    free(obj);
}

int main() {
    int k = 3;
    int nums[] = {4, 5, 8, 2};
    int numsSize = 4;
    
    KthLargest* kthLargest = kthLargestCreate(k, nums, numsSize);
    printf("Initialized KthLargest with k = 3 and nums = [4, 5, 8, 2]\n\n");

    printf("add(3): %d (Expected: 4)\n", kthLargestAdd(kthLargest, 3));
    printf("add(5): %d (Expected: 5)\n", kthLargestAdd(kthLargest, 5));
    printf("add(10): %d (Expected: 5)\n", kthLargestAdd(kthLargest, 10));
    printf("add(9): %d (Expected: 8)\n", kthLargestAdd(kthLargest, 9));
    printf("add(4): %d (Expected: 8)\n", kthLargestAdd(kthLargest, 4));

    kthLargestFree(kthLargest);
    printf("\nMemory freed.\n");

    return 0;
}