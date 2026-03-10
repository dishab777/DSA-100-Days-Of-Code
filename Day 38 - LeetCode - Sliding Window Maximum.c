#include <stdio.h>
#include <stdlib.h>

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    *returnSize = numsSize - k + 1;
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    
    int* deque = (int*)malloc(numsSize * sizeof(int));
    int front = 0;
    int rear = -1;
    
    for (int i = 0; i < numsSize; i++) {
        if (front <= rear && deque[front] < i - k + 1) {
            front++;
        }
        
        while (front <= rear && nums[deque[rear]] <= nums[i]) {
            rear--;
        }
        
        deque[++rear] = i;
        
        if (i >= k - 1) {
            result[i - k + 1] = nums[deque[front]];
        }
    }
    
    free(deque);
    return result;
}

// Helper to print arrays
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(",");
    }
    printf("]\n");
}

int main() {
    // Example 1: nums = [1,3,-1,-3,5,3,6,7], k = 3
    int nums[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    
    printf("Input array: ");
    printArray(nums, numsSize);
    printf("Window size (k): %d\n\n", k);
    
    int* result = maxSlidingWindow(nums, numsSize, k, &returnSize);
    
    printf("Max Sliding Window result: ");
    printArray(result, returnSize);
    printf("Expected result:         [3,3,5,5,6,7]\n");
    
    free(result);
    return 0;
}