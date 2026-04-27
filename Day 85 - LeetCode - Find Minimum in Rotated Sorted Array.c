#include <stdio.h>
#include <stdlib.h>

int findMin(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return nums[left];
}

int main() {
    int nums1[] = {3, 4, 5, 1, 2};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    
    printf("Array 1: [3, 4, 5, 1, 2]\n");
    printf("Minimum Found: %d\n", findMin(nums1, size1));
    printf("Expected:      1\n\n");
    
    int nums2[] = {4, 5, 6, 7, 0, 1, 2};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    
    printf("Array 2: [4, 5, 6, 7, 0, 1, 2]\n");
    printf("Minimum Found: %d\n", findMin(nums2, size2));
    printf("Expected:      0\n\n");
    
    int nums3[] = {11, 13, 15, 17};
    int size3 = sizeof(nums3) / sizeof(nums3[0]);
    
    printf("Array 3: [11, 13, 15, 17]\n");
    printf("Minimum Found: %d\n", findMin(nums3, size3));
    printf("Expected:      11\n");
    
    return 0;
}