#include <stdio.h>

void sortColors(int* nums, int numsSize) {
    int low = 0;
    int mid = 0;
    int high = numsSize - 1;
    
    while (mid <= high) {
        if (nums[mid] == 0) {
            int temp = nums[low];
            nums[low] = nums[mid];
            nums[mid] = temp;
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            int temp = nums[high];
            nums[high] = nums[mid];
            nums[mid] = temp;
            high--;
        }
    }
}

int main() {
    int nums1[] = {2, 0, 2, 1, 1, 0};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    
    printf("Original: [2, 0, 2, 1, 1, 0]\n");
    sortColors(nums1, size1);
    
    printf("Sorted:   [");
    for (int i = 0; i < size1; i++) {
        printf("%d", nums1[i]);
        if (i < size1 - 1) printf(", ");
    }
    printf("]\nExpected: [0, 0, 1, 1, 2, 2]\n\n");
    
    int nums2[] = {2, 0, 1};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    
    printf("Original: [2, 0, 1]\n");
    sortColors(nums2, size2);
    
    printf("Sorted:   [");
    for (int i = 0; i < size2; i++) {
        printf("%d", nums2[i]);
        if (i < size2 - 1) printf(", ");
    }
    printf("]\nExpected: [0, 1, 2]\n");
    
    return 0;
}