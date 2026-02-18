#include <stdio.h>
#include <stdlib.h>

// Function to find the maximum subarray sum (Kadane's Algorithm)
int maxSubArray(int* nums, int numsSize) {
    // Initialize maxSum with the first element to handle all-negative arrays correctly
    int maxSum = nums[0];
    int currentSum = 0;

    for (int i = 0; i < numsSize; i++) {
        currentSum += nums[i];
        
        // Update global max if current subarray sum is greater
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
        
        // If current sum becomes negative, discard it (reset to 0)
        // because it will only decrease the sum of any future subarray
        if (currentSum < 0) {
            currentSum = 0;
        }
    }
    
    return maxSum;
}

int main() {
    int n;
    printf("Enter size of array: ");
    if (scanf("%d", &n) != 1) return 1;

    // Handle empty or invalid array size
    if (n <= 0) {
        printf("Array size must be positive.\n");
        return 0;
    }

    // Dynamic memory allocation
    int* nums = (int*)malloc(n * sizeof(int));
    if (nums == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    // Call the function
    int result = maxSubArray(nums, n);

    printf("Maximum Subarray Sum: %d\n", result);

    // Free allocated memory
    free(nums);

    return 0;
}