#include <stdio.h>
#include <stdlib.h>

#define MAX_CALLS 50000

typedef struct {
    int* maxHeap;
    int maxSize;
    int* minHeap;
    int minSize;
} MedianFinder;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void pushMax(MedianFinder* obj, int val) {
    obj->maxHeap[obj->maxSize] = val;
    int curr = obj->maxSize++;
    while (curr > 0) {
        int parent = (curr - 1) / 2;
        if (obj->maxHeap[curr] > obj->maxHeap[parent]) {
            swap(&obj->maxHeap[curr], &obj->maxHeap[parent]);
            curr = parent;
        } else break;
    }
}

int popMax(MedianFinder* obj) {
    int res = obj->maxHeap[0];
    obj->maxHeap[0] = obj->maxHeap[--obj->maxSize];
    int curr = 0;
    while (1) {
        int left = 2 * curr + 1;
        int right = 2 * curr + 2;
        int largest = curr;
        if (left < obj->maxSize && obj->maxHeap[left] > obj->maxHeap[largest]) largest = left;
        if (right < obj->maxSize && obj->maxHeap[right] > obj->maxHeap[largest]) largest = right;
        if (largest != curr) {
            swap(&obj->maxHeap[curr], &obj->maxHeap[largest]);
            curr = largest;
        } else break;
    }
    return res;
}

void pushMin(MedianFinder* obj, int val) {
    obj->minHeap[obj->minSize] = val;
    int curr = obj->minSize++;
    while (curr > 0) {
        int parent = (curr - 1) / 2;
        if (obj->minHeap[curr] < obj->minHeap[parent]) {
            swap(&obj->minHeap[curr], &obj->minHeap[parent]);
            curr = parent;
        } else break;
    }
}

int popMin(MedianFinder* obj) {
    int res = obj->minHeap[0];
    obj->minHeap[0] = obj->minHeap[--obj->minSize];
    int curr = 0;
    while (1) {
        int left = 2 * curr + 1;
        int right = 2 * curr + 2;
        int smallest = curr;
        if (left < obj->minSize && obj->minHeap[left] < obj->minHeap[smallest]) smallest = left;
        if (right < obj->minSize && obj->minHeap[right] < obj->minHeap[smallest]) smallest = right;
        if (smallest != curr) {
            swap(&obj->minHeap[curr], &obj->minHeap[smallest]);
            curr = smallest;
        } else break;
    }
    return res;
}

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->maxHeap = (int*)malloc(MAX_CALLS * sizeof(int));
    obj->minHeap = (int*)malloc(MAX_CALLS * sizeof(int));
    obj->maxSize = 0;
    obj->minSize = 0;
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    pushMax(obj, num);
    pushMin(obj, popMax(obj));
    if (obj->minSize > obj->maxSize) {
        pushMax(obj, popMin(obj));
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->maxSize > obj->minSize) {
        return (double)(obj->maxHeap[0]);
    } else {
        return ((double)obj->maxHeap[0] + (double)obj->minHeap[0]) / 2.0;
    }
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->maxHeap);
    free(obj->minHeap);
    free(obj);
}

int main() {
    MedianFinder* medianFinder = medianFinderCreate();
    printf("Initialized MedianFinder.\n");
    
    medianFinderAddNum(medianFinder, 1);
    printf("Added 1.\n");
    
    medianFinderAddNum(medianFinder, 2);
    printf("Added 2.\n");
    
    printf("Current Median: %.5f (Expected: 1.50000)\n", medianFinderFindMedian(medianFinder));
    
    medianFinderAddNum(medianFinder, 3);
    printf("Added 3.\n");
    
    printf("Current Median: %.5f (Expected: 2.00000)\n", medianFinderFindMedian(medianFinder));
    
    medianFinderFree(medianFinder);
    printf("Memory freed.\n");

    return 0;
}