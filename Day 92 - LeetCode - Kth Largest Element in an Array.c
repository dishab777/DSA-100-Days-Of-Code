#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int quickSelect(int* nums, int left, int right, int targetIndex) {
    if (left == right) {
        return nums[left];
    }
    
    int pivotIndex = left + rand() % (right - left + 1);
    int pivot = nums[pivotIndex];
    
    int i = left;
    int j = left;
    int k = right;
    
    while (j <= k) {
        if (nums[j] < pivot) {
            swap(&nums[i], &nums[j]);
            i++;
            j++;
        } else if (nums[j] > pivot) {
            swap(&nums[j], &nums[k]);
            k--;
        } else {
            j++;
        }
    }
    
    if (targetIndex >= i && targetIndex <= k) {
        return pivot;
    } else if (targetIndex < i) {
        return quickSelect(nums, left, i - 1, targetIndex);
    } else {
        return quickSelect(nums, k + 1, right, targetIndex);
    }
}

int findKthLargest(int* nums, int numsSize, int k) {
    int targetIndex = numsSize - k;
    return quickSelect(nums, 0, numsSize - 1, targetIndex);
}

int main() {
    int nums1[] = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    
    printf("Array: [3, 2, 1, 5, 6, 4] | k: 2\n");
    printf("Kth Largest: %d\n", findKthLargest(nums1, size1, k1));
    printf("Expected:    5\n\n");
    
    int nums2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int k2 = 5;
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    
    printf("Array: [1, 1, 1... 1] (Duplicates) | k: 5\n");
    printf("Kth Largest: %d\n", findKthLargest(nums2, size2, k2));
    printf("Expected:    1\n");
    
    return 0;
}