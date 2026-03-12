#include <stdio.h>
#include <stdlib.h>

// Helper function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to maintain the Max Heap property for a subtree rooted at index i
// n is the current size of the heap
void heapify(int arr[], int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // Left child index
    int right = 2 * i + 2; // Right child index

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child is larger than the largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If the largest is not the root, swap and recursively heapify the affected sub-tree
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Main function to perform Heap Sort
void heapSort(int arr[], int n) {
    // Phase 1: Build a Max Heap
    // Start from the last non-leaf node and go up to the root
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Phase 2: Extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root (maximum element) to the end of the array
        swap(&arr[0], &arr[i]);

        // Call max heapify on the reduced heap to restore the property
        heapify(arr, i, 0);
    }
}

int main() {
    int n;

    // Read the number of elements
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    int *arr = (int *)malloc(n * sizeof(int));

    // Read the array elements
    printf("Enter %d space-separated integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Perform Heap Sort
    heapSort(arr, n);

    // Print the sorted array
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}