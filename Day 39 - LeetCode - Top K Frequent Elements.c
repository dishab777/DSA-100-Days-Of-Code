#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int count;
} ElementFreq;

int compareNums(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int compareFreq(const void* a, const void* b) {
    ElementFreq* ea = (ElementFreq*)a;
    ElementFreq* eb = (ElementFreq*)b;
    return eb->count - ea->count;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    qsort(nums, numsSize, sizeof(int), compareNums);

    ElementFreq* freqs = (ElementFreq*)malloc(numsSize * sizeof(ElementFreq));
    int uniqueCount = 0;

    freqs[0].val = nums[0];
    freqs[0].count = 1;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i-1]) {
            freqs[uniqueCount].count++;
        } else {
            uniqueCount++;
            freqs[uniqueCount].val = nums[i];
            freqs[uniqueCount].count = 1;
        }
    }
    uniqueCount++;

    qsort(freqs, uniqueCount, sizeof(ElementFreq), compareFreq);

    *returnSize = k;
    int* result = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        result[i] = freqs[i].val;
    }

    free(freqs);
    return result;
}

// Helper to print arrays
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(",");
    }
    printf("]\n");
}

int main() {
    // Example 1: nums = [1,1,1,2,2,3], k = 2
    int nums1[] = {1, 1, 1, 2, 2, 3};
    int k1 = 2;
    int numsSize1 = sizeof(nums1) / sizeof(nums1[0]);
    int returnSize1;
    
    int* result1 = topKFrequent(nums1, numsSize1, k1, &returnSize1);
    printf("Example 1 Output: ");
    printArray(result1, returnSize1); // Expected: [1,2]
    free(result1);

    // Example 2: nums = [1], k = 1
    int nums2[] = {1};
    int k2 = 1;
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]);
    int returnSize2;
    
    int* result2 = topKFrequent(nums2, numsSize2, k2, &returnSize2);
    printf("Example 2 Output: ");
    printArray(result2, returnSize2); // Expected: [1]
    free(result2);

    return 0;
}