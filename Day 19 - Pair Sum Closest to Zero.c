#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    
    // Read the size of the array
    if (scanf("%d", &n) != 1) return 1;

    // We need at least two elements to form a pair
    if (n < 2) return 0;

    int *arr = (int*)malloc(n * sizeof(int));
    
    // Read array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Step 1: Sort the array
    qsort(arr, n, sizeof(int), compare);

    // Step 2: Initialize two pointers
    int left = 0;
    int right = n - 1;
    
    int min_l = left;
    int min_r = right;
    int min_sum = arr[left] + arr[right];

    // Step 3: Traverse with two pointers
    while (left < right) {
        int sum = arr[left] + arr[right];

        // If the current sum is closer to zero, update our trackers
        if (abs(sum) < abs(min_sum)) {
            min_sum = sum;
            min_l = left;
            min_r = right;
        }

        // Move pointers based on the sum
        if (sum < 0) {
            left++;  // We need a larger value to get closer to zero
        } else if (sum > 0) {
            right--; // We need a smaller value to get closer to zero
        } else {
            break;   // If the sum is exactly 0, it can't get any closer
        }
    }

    // Print the result pair
    printf("%d %d\n", arr[min_l], arr[min_r]);

    free(arr);
    return 0;
}