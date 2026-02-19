#include <stdio.h>
#include <stdlib.h>

// Helper function to reverse a portion of the array
void reverse(int* arr, int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int main() {
    int n;
    
    // Read array size
    if (scanf("%d", &n) != 1) return 0;
    
    // Handle edge case for size 0 or negative
    if (n <= 0) return 0;

    int* arr = (int*)malloc(n * sizeof(int));
    
    // Read array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int k;
    // Read k (rotation steps)
    if (scanf("%d", &k) != 1) {
        free(arr);
        return 0;
    }

    // Optimize k if it is greater than n
    k = k % n;

    // Apply the Reversal Algorithm
    reverse(arr, 0, n - 1);    // Step 1: Reverse whole array
    reverse(arr, 0, k - 1);    // Step 2: Reverse first k elements
    reverse(arr, k, n - 1);    // Step 3: Reverse the rest

    // Print the rotated array
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(arr);
    return 0;
}