#include <stdio.h>
#include <stdlib.h>

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;

    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }

    while (j >= 0) {
        nums1[k] = nums2[j];
        j--;
        k--;
    }
}

int main() {
    int m, n;
    
    printf("Enter number of elements in nums1 (m): ");
    if (scanf("%d", &m) != 1) return 1;

    printf("Enter number of elements in nums2 (n): ");
    if (scanf("%d", &n) != 1) return 1;

    int *nums1 = (int*)malloc((m + n) * sizeof(int));
    int *nums2 = (int*)malloc(n * sizeof(int));

    printf("Enter %d elements for nums1 (sorted): ", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &nums1[i]);
    }

    // Fill the rest of nums1 with 0s (simulating the empty space)
    for (int i = m; i < m + n; i++) {
        nums1[i] = 0;
    }

    printf("Enter %d elements for nums2 (sorted): ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums2[i]);
    }

    merge(nums1, m + n, m, nums2, n, n);

    printf("Merged array: ");
    for (int i = 0; i < m + n; i++) {
        printf("%d ", nums1[i]);
    }
    printf("\n");

    free(nums1);
    free(nums2);

    return 0;
}