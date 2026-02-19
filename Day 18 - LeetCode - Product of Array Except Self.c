#include <stdio.h>
#include <stdlib.h>

int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* answer = (int*)malloc(numsSize * sizeof(int));
    
    // Initialize the answer array
    answer[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        answer[i] = answer[i - 1] * nums[i - 1];
    }
    
    // Calculate suffix product and update answer array
    int suffix = 1;
    for (int i = numsSize - 1; i >= 0; i--) {
        answer[i] = answer[i] * suffix;
        suffix = suffix * nums[i];
    }
    
    return answer;
}

int main() {
    int n;
    printf("Enter size of array: ");
    if (scanf("%d", &n) != 1) return 1;

    int* nums = (int*)malloc(n * sizeof(int));
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int returnSize;
    int* result = productExceptSelf(nums, n, &returnSize);

    printf("Product Array: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(nums);
    free(result);

    return 0;
}