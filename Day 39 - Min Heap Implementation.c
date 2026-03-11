#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to maintain the min-heap property by bubbling up
void heapifyUp(int *heap, int index) {
    int parent = (index - 1) / 2;
    // If current node is smaller than its parent, swap and continue bubbling up
    if (index > 0 && heap[index] < heap[parent]) {
        swap(&heap[index], &heap[parent]);
        heapifyUp(heap, parent);
    }
}

// Function to maintain the min-heap property by bubbling down
void heapifyDown(int *heap, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Check if left child is smaller than current smallest
    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    // Check if right child is smaller than current smallest
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }

    // If the smallest is not the root, swap and continue bubbling down
    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        heapifyDown(heap, size, smallest);
    }
}

int main() {
    int n;
    
    // Read the number of operations
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    // Dynamically allocate array for the heap
    // Max possible size is 'n' if all operations are inserts
    int* heap = (int*)malloc(n * sizeof(int));
    int size = 0;

    for (int i = 0; i < n; i++) {
        char op[15];
        scanf("%s", op);

        if (strcmp(op, "insert") == 0) {
            int val;
            scanf("%d", &val);
            // Insert at the end of the array and restore heap property
            heap[size] = val;
            heapifyUp(heap, size);
            size++;
            
        } else if (strcmp(op, "extractMin") == 0) {
            if (size == 0) {
                printf("-1\n");
            } else {
                // The minimum element is always at the root (index 0)
                printf("%d\n", heap[0]);
                
                // Replace root with the last element and reduce size
                heap[0] = heap[size - 1];
                size--;
                
                // Restore heap property
                heapifyDown(heap, size, 0);
            }
            
        } else if (strcmp(op, "peek") == 0) {
            if (size == 0) {
                printf("-1\n");
            } else {
                // Just print the root without removing it
                printf("%d\n", heap[0]);
            }
        }
    }

    // Free the dynamically allocated memory
    free(heap);
    return 0;
}