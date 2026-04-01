#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Solution Core ---
bool isMinHeap(int arr[], int n) {
    // We only need to check the parent nodes, which go up to index (n / 2) - 1
    for (int i = 0; i <= (n / 2) - 1; i++) {
        
        // Calculate the indices of the mathematical children
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        // Check if the left child exists and violates the Min-Heap rule
        if (leftChild < n && arr[i] > arr[leftChild]) {
            return false;
        }

        // Check if the right child exists and violates the Min-Heap rule
        if (rightChild < n && arr[i] > arr[rightChild]) {
            return false;
        }
    }
    
    // If no violations were found, it is a valid Min-Heap
    return true;
}

int main() {
    int n;
    
    // Read the number of elements
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    int* arr = (int*)malloc(n * sizeof(int));

    // Read the level order elements directly into our array
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Check the Min-Heap property
    if (isMinHeap(arr, n)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    // Clean up
    free(arr);

    return 0;
}