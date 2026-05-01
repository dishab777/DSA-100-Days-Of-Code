#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canSplit(int* nums, int numsSize, int k, long long maxSum) {
    int subarrays = 1;
    long long currentSum = 0;
    
    for (int i = 0; i < numsSize; i++) {
        if (currentSum + nums[i] > maxSum) {
            subarrays++;
            currentSum = nums[i];
            
            if (subarrays > k) {
                return false;
            }
        } else {
            currentSum += nums[i];
        }
    }
    return true;
}

int splitArray(int* nums, int numsSize, int k) {
    long long left = 0;
    long long right = 0;
    
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > left) {
            left = nums[i];
        }
        right += nums[i];
    }
    
    long long best = right;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        if (canSplit(nums, numsSize, k, mid)) {
            best = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return (int)best;
}

int main() {
    int nums[] = {7, 2, 5, 10, 8};
    int k = 2;
    int size = sizeof(nums) / sizeof(nums[0]);
    
    printf("Array: [7, 2, 5, 10, 8] | Subarrays (k): %d\n", k);
    printf("Minimized Largest Sum: %d\n", splitArray(nums, size, k));
    printf("Expected:              18\n");
    
    return 0;
}