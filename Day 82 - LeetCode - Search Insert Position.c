#include <stdio.h>
#include <stdlib.h>

int searchInsert(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        }
        
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return left;
}

int main() {
    int nums[] = {1, 3, 5, 6};
    int size = sizeof(nums) / sizeof(nums[0]);
    
    printf("Array: [1, 3, 5, 6]\n\n");
    
    int target1 = 5;
    printf("Target: %d | Output: %d\n", target1, searchInsert(nums, size, target1));
    printf("Expected: 2\n\n");
    
    int target2 = 2;
    printf("Target: %d | Output: %d\n", target2, searchInsert(nums, size, target2));
    printf("Expected: 1\n\n");
    
    int target3 = 7;
    printf("Target: %d | Output: %d\n", target3, searchInsert(nums, size, target3));
    printf("Expected: 4\n");
    
    return 0;
}