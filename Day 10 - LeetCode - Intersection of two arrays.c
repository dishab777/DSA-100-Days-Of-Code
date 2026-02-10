#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to find the intersection
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    // Sort both arrays
    qsort(nums1, nums1Size, sizeof(int), compare);
    qsort(nums2, nums2Size, sizeof(int), compare);

    // Allocate memory for the result (maximum possible size is the smaller array length)
    int maxSize = (nums1Size < nums2Size) ? nums1Size : nums2Size;
    int* result = (int*)malloc(maxSize * sizeof(int));
    
    int i = 0, j = 0, k = 0;
    
    // Two-pointer iteration
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] < nums2[j]) {
            i++;
        } else if (nums1[i] > nums2[j]) {
            j++;
        } else {
            // Match found
            result[k++] = nums1[i];
            i++;
            j++;
        }
    }
    
    *returnSize = k;
    return result;
}

int main() {
    int n1;
    printf("Enter size of first array: ");
    if (scanf("%d", &n1) != 1) return 1;

    int *nums1 = (int*)malloc(n1 * sizeof(int));
    printf("Enter %d elements for first array: ", n1);
    for (int i = 0; i < n1; i++) {
        scanf("%d", &nums1[i]);
    }

    int n2;
    printf("Enter size of second array: ");
    if (scanf("%d", &n2) != 1) return 1;

    int *nums2 = (int*)malloc(n2 * sizeof(int));
    printf("Enter %d elements for second array: ", n2);
    for (int i = 0; i < n2; i++) {
        scanf("%d", &nums2[i]);
    }

    int returnSize;
    int *result = intersect(nums1, n1, nums2, n2, &returnSize);

    printf("Intersection: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d", result[i]);
        if (i < returnSize - 1) {
            printf(" ");
        }
    }
    printf("\n");

    // Free allocated memory
    free(nums1);
    free(nums2);
    free(result);

    return 0;
}