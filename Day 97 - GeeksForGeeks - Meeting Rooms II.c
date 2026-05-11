#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

typedef struct {
    int* data;
    int size;
} MinHeap;

void push(MinHeap* heap, int val) {
    heap->data[heap->size] = val;
    int curr = heap->size;
    heap->size++;
    while (curr > 0 && heap->data[(curr - 1) / 2] > heap->data[curr]) {
        swap(&heap->data[(curr - 1) / 2], &heap->data[curr]);
        curr = (curr - 1) / 2;
    }
}

void pop(MinHeap* heap) {
    if (heap->size == 0) return;
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    int curr = 0;
    while (1) {
        int left = 2 * curr + 1;
        int right = 2 * curr + 2;
        int smallest = curr;
        
        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        
        if (smallest != curr) {
            swap(&heap->data[curr], &heap->data[smallest]);
            curr = smallest;
        } else {
            break;
        }
    }
}

int compareIntervals(const void* a, const void* b) {
    int* intervalA = *(int**)a;
    int* intervalB = *(int**)b;
    return intervalA[0] - intervalB[0];
}

int minMeetingRooms(int** intervals, int intervalsSize, int* intervalsColSize) {
    if (intervalsSize == 0) return 0;
    
    qsort(intervals, intervalsSize, sizeof(int*), compareIntervals);
    
    MinHeap heap;
    heap.data = (int*)malloc(intervalsSize * sizeof(int));
    heap.size = 0;
    
    push(&heap, intervals[0][1]);
    
    for (int i = 1; i < intervalsSize; i++) {
        if (heap.data[0] <= intervals[i][0]) {
            pop(&heap);
        }
        push(&heap, intervals[i][1]);
    }
    
    int result = heap.size;
    free(heap.data);
    return result;
}

int main() {
    int arr1[][2] = {{0, 30}, {5, 10}, {15, 20}};
    int size1 = 3;
    int* intervals1[3];
    for(int i = 0; i < size1; i++) intervals1[i] = arr1[i];
    
    printf("Intervals: [[0, 30], [5, 10], [15, 20]]\n");
    printf("Min Rooms: %d\n", minMeetingRooms(intervals1, size1, NULL));
    printf("Expected:  2\n\n");
    
    int arr2[][2] = {{7, 10}, {2, 4}};
    int size2 = 2;
    int* intervals2[2];
    for(int i = 0; i < size2; i++) intervals2[i] = arr2[i];
    
    printf("Intervals: [[7, 10], [2, 4]]\n");
    printf("Min Rooms: %d\n", minMeetingRooms(intervals2, size2, NULL));
    printf("Expected:  1\n");

    return 0;
}