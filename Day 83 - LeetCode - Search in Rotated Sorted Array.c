#include <stdio.h>
#include <stdlib.h>

int search(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        }
        
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    
    return -1;
}

int main() {
    int nums1[] = {4, 5, 6, 7, 0, 1, 2};
    int target1 = 0;
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    
    printf("Array 1: [4, 5, 6, 7, 0, 1, 2] | Target: 0\n");
    int result1 = search(nums1, size1, target1);
    printf("Index Found: %d\n", result1);
    printf("Expected:    4\n\n");
    
    int nums2[] = {4, 5, 6, 7, 0, 1, 2};
    int target2 = 3;
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    
    printf("Array 2: [4, 5, 6, 7, 0, 1, 2] | Target: 3\n");
    int result2 = search(nums2, size2, target2);
    printf("Index Found: %d\n", result2);
    printf("Expected:    -1\n\n");
    
    int nums3[] = {1};
    int target3 = 0;
    int size3 = sizeof(nums3) / sizeof(nums3[0]);
    
    printf("Array 3: [1] | Target: 0\n");
    int result3 = search(nums3, size3, target3);
    printf("Index Found: %d\n", result3);
    printf("Expected:    -1\n");
    
    return 0;
}