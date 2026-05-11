#include <stdio.h>
#include <stdlib.h>

struct Element {
    int val;
    int idx;
};

void mergeAndCount(struct Element* arr, struct Element* temp, int* counts, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i].val <= arr[j].val) {
            counts[arr[i].idx] += (j - (mid + 1));
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        counts[arr[i].idx] += (j - (mid + 1));
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (int p = left; p <= right; p++) {
        arr[p] = temp[p];
    }
}

void mergeSortAndCount(struct Element* arr, struct Element* temp, int* counts, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortAndCount(arr, temp, counts, left, mid);
        mergeSortAndCount(arr, temp, counts, mid + 1, right);
        mergeAndCount(arr, temp, counts, left, mid, right);
    }
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* counts = (int*)calloc(numsSize, sizeof(int));
    if (numsSize == 0) return counts;

    struct Element* arr = (struct Element*)malloc(numsSize * sizeof(struct Element));
    struct Element* temp = (struct Element*)malloc(numsSize * sizeof(struct Element));

    for (int i = 0; i < numsSize; i++) {
        arr[i].val = nums[i];
        arr[i].idx = i;
    }

    mergeSortAndCount(arr, temp, counts, 0, numsSize - 1);

    free(arr);
    free(temp);

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