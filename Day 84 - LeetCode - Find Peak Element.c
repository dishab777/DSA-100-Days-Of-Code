#include <stdio.h>
#include <stdlib.h>

int findPeakElement(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] < nums[mid + 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

int main() {
    int nums1[] = {1, 2, 3, 1};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    
    printf("Array 1: [1, 2, 3, 1]\n");
    int result1 = findPeakElement(nums1, size1);
    printf("Peak Index Found: %d (Value: %d)\n", result1, nums1[result1]);
    printf("Expected:         2\n\n");
    
    int nums2[] = {1, 2, 1, 3, 5, 6, 4};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    
    printf("Array 2: [1, 2, 1, 3, 5, 6, 4]\n");
    int result2 = findPeakElement(nums2, size2);
    printf("Peak Index Found: %d (Value: %d)\n", result2, nums2[result2]);
    printf("Expected:         5 (or 1)\n\n");
    
    int nums3[] = {1, 2, 3, 4, 5};
    int size3 = sizeof(nums3) / sizeof(nums3[0]);
    
    printf("Array 3: [1, 2, 3, 4, 5]\n");
    int result3 = findPeakElement(nums3, size3);
    printf("Peak Index Found: %d (Value: %d)\n", result3, nums3[result3]);
    printf("Expected:         4\n");
    
    return 0;
}