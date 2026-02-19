#include <stdio.h>
#include <stdlib.h>

int maxSubarraySumCircular(int* nums, int numsSize) {
    int total_sum = 0;
    int curr_max = 0;
    int max_sum = nums[0];
    int curr_min = 0;
    int min_sum = nums[0];
    
    for (int i = 0; i < numsSize; i++) {
        total_sum += nums[i];
        
        curr_max = (curr_max + nums[i] > nums[i]) ? curr_max + nums[i] : nums[i];
        if (curr_max > max_sum) {
            max_sum = curr_max;
        }
        
        curr_min = (curr_min + nums[i] < nums[i]) ? curr_min + nums[i] : nums[i];
        if (curr_min < min_sum) {
            min_sum = curr_min;
        }
    }
    
    if (max_sum > 0) {
        int circular_max = total_sum - min_sum;
        return (max_sum > circular_max) ? max_sum : circular_max;
    }
    
    return max_sum;
}

int main() {
    int n;
    printf("Enter size of array: ");
    if (scanf("%d", &n) != 1) return 1;

    if (n <= 0) return 0;

    int* nums = (int*)malloc(n * sizeof(int));
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int result = maxSubarraySumCircular(nums, n);

    printf("Maximum Circular Subarray Sum: %d\n", result);

    free(nums);
    return 0;
}