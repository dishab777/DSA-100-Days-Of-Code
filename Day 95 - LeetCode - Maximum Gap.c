#include <stdio.h>
#include <stdlib.h>

int maximumGap(int* nums, int numsSize) {
    if (numsSize < 2) return 0;
    
    int minVal = nums[0];
    int maxVal = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < minVal) minVal = nums[i];
        if (nums[i] > maxVal) maxVal = nums[i];
    }
    
    if (minVal == maxVal) return 0;
    
    int gap = (maxVal - minVal) / (numsSize - 1);
    if ((maxVal - minVal) % (numsSize - 1) != 0) gap++;
    if (gap == 0) gap = 1;
    
    int* bucketMin = (int*)malloc(numsSize * sizeof(int));
    int* bucketMax = (int*)malloc(numsSize * sizeof(int));
    
    for (int i = 0; i < numsSize; i++) {
        bucketMin[i] = -1;
        bucketMax[i] = -1;
    }
    
    for (int i = 0; i < numsSize; i++) {
        int idx = (nums[i] - minVal) / gap;
        
        if (bucketMin[idx] == -1 || nums[i] < bucketMin[idx]) {
            bucketMin[idx] = nums[i];
        }
        if (bucketMax[idx] == -1 || nums[i] > bucketMax[idx]) {
            bucketMax[idx] = nums[i];
        }
    }
    
    int maxGap = 0;
    int previousMax = bucketMax[0];
    
    for (int i = 1; i < numsSize; i++) {
        if (bucketMin[i] == -1) continue;
        int currentGap = bucketMin[i] - previousMax;
        if (currentGap > maxGap) {
            maxGap = currentGap;
        }
        previousMax = bucketMax[i];
    }
    
    free(bucketMin);
    free(bucketMax);
    
    return maxGap;
}

int main() {
    int nums1[] = {3, 6, 9, 1};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("Array: [3, 6, 9, 1]\n");
    printf("Max Gap:  %d\n", maximumGap(nums1, size1));
    printf("Expected: 3\n\n");
    
    int nums2[] = {10};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("Array: [10]\n");
    printf("Max Gap:  %d\n", maximumGap(nums2, size2));
    printf("Expected: 0\n\n");
    
    int nums3[] = {1, 10000000};
    int size3 = sizeof(nums3) / sizeof(nums3[0]);
    printf("Array: [1, 10000000]\n");
    printf("Max Gap:  %d\n", maximumGap(nums3, size3));
    printf("Expected: 9999999\n");
    
    return 0;
}