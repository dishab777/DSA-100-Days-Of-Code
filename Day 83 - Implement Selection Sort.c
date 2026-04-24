#include <stdio.h>
#include <stdlib.h>

// --- Core Selection Sort Logic ---

void selectionSort(int arr[], int n) {
    // Outer loop dictates the starting point of the unsorted portion
    for (int i = 0; i < n - 1; i++) {
        
        // Assume the first unsorted element is the smallest
        int min_idx = i;
        
        // Inner loop scans the remaining unsorted portion to find the true minimum
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j; // Update our record of where the smallest number lives
            }
        }
        
        // If the minimum isn't already the first element, swap them!
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

// --- Main Execution ---

int main() {
    int n;
    
    // Read the size of the array
    if (scanf("%d", &n) != 1) return 0;
    
    // Dynamically allocate memory to handle large inputs safely
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) return 1;
    
    // Read the array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Execute the sorting algorithm
    selectionSort(arr, n);
    
    // Print the sorted array matching the required format
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    // Always clean up your dynamically allocated memory
    free(arr);
    
    return 0;
}