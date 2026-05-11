#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    int valA = *(const int*)a;
    int valB = *(const int*)b;
    if (valA < valB) return -1;
    if (valA > valB) return 1;
    return 0;
}

int binarySearch(int* arr, int size, int target) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid + 1; 
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return 0;
}

void update(int* bit, int size, int index, int val) {
    while (index <= size) {
        bit[index] += val;
        index += index & (-index);
    }
}

int query(int* bit, int index) {
    int sum = 0;
    while (index > 0) {
        sum += bit[index];
        index -= index & (-index);
    }
    return sum;
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* counts = (int*)malloc(numsSize * sizeof(int));
    if (numsSize == 0) return counts;

    int* sorted_nums = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        sorted_nums[i] = nums[i];
    }

    qsort(sorted_nums, numsSize, sizeof(int), compare);

    int uniqueSize = 0;
    for (int i = 0; i < numsSize; i++) {
        if (i == 0 || sorted_nums[i] != sorted_nums[i - 1]) {
            sorted_nums[uniqueSize++] = sorted_nums[i];
        }
    }

    int* bit = (int*)calloc(uniqueSize + 1, sizeof(int));

    for (int i = numsSize - 1; i >= 0; i--) {
        int rank = binarySearch(sorted_nums, uniqueSize, nums[i]);
        counts[i] = query(bit, rank - 1);
        update(bit, uniqueSize, rank, 1);
    }

    free(sorted_nums);
    free(bit);

    return counts;
}

int main() {
    int nums1[] = {5, 2, 6, 1};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    int returnSize1;
    
    int* result1 = countSmaller(nums1, size1, &returnSize1);
    
    printf("Array: [5, 2, 6, 1]\n");
    printf("Counts: [");
    for (int i = 0; i < returnSize1; i++) {
        printf("%d", result1[i]);
        if (i < returnSize1 - 1) printf(", ");
    }
    printf("]\nExpected: [2, 1, 1, 0]\n\n");
    free(result1);
    
    int nums2[] = {-1, -1};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    int returnSize2;
    
    int* result2 = countSmaller(nums2, size2, &returnSize2);
    
    printf("Array: [-1, -1]\n");
    printf("Counts: [");
    for (int i = 0; i < returnSize2; i++) {
        printf("%d", result2[i]);
        if (i < returnSize2 - 1) printf(", ");
    }
    printf("]\nExpected: [0, 0]\n");
    free(result2);
    
    return 0;
}