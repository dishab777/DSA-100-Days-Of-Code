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
        
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int main() {
    int nums1[] = {-1, 0, 3, 5, 9, 12};
    int target1 = 9;
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    
    printf("Array 1: [-1, 0, 3, 5, 9, 12] | Target: 9\n");
    int result1 = search(nums1, size1, target1);
    printf("Index Found: %d\n", result1);
    printf("Expected:    4\n\n");

    int nums2[] = {-1, 0, 3, 5, 9, 12};
    int target2 = 2;
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    
    printf("Array 2: [-1, 0, 3, 5, 9, 12] | Target: 2\n");
    int result2 = search(nums2, size2, target2);
    printf("Index Found: %d\n", result2);
    printf("Expected:    -1\n");
    
    return 0;
}