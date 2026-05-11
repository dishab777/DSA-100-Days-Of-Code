#include <stdio.h>
#include <stdlib.h>

int mergeSortAndCount(int* nums, int* temp, int left, int right) {
    if (left >= right) {
        return 0;
    }
    
    int mid = left + (right - left) / 2;
    int count = mergeSortAndCount(nums, temp, left, mid) + 
                mergeSortAndCount(nums, temp, mid + 1, right);
    
    int j = mid + 1;
    for (int i = left; i <= mid; i++) {
        while (j <= right && nums[i] > 2LL * nums[j]) {
            j++;
        }
        count += (j - (mid + 1));
    }
    
    int i = left;
    j = mid + 1;
    int k = left;
    
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            temp[k++] = nums[i++];
        } else {
            temp[k++] = nums[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = nums[i++];
    }
    
    while (j <= right) {
        temp[k++] = nums[j++];
    }
    
    for (i = left; i <= right; i++) {
        nums[i] = temp[i];
    }
    
    return count;
}

int reversePairs(int* nums, int numsSize) {
    if (numsSize < 2) return 0;
    int* temp = (int*)malloc(numsSize * sizeof(int));
    int result = mergeSortAndCount(nums, temp, 0, numsSize - 1);
    free(temp);
    return result;
}

int main() {
    int nums1[] = {1, 3, 2, 3, 1};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("Array: [1, 3, 2, 3, 1]\n");
    printf("Reverse Pairs: %d\n", reversePairs(nums1, size1));
    printf("Expected:      2\n\n");
    
    int nums2[] = {2, 4, 3, 5, 1};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("Array: [2, 4, 3, 5, 1]\n");
    printf("Reverse Pairs: %d\n", reversePairs(nums2, size2));
    printf("Expected:      3\n");
    
    return 0;
}