#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int compare(const void* a, const void* b) {
    int int_a = *(int*)a;
    int int_b = *(int*)b;
    return (int_a > int_b) - (int_a < int_b);
}

// Function to find the triplets
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (numsSize < 3) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    // Step 1: Sort the array
    qsort(nums, numsSize, sizeof(int), compare);

    int capacity = 100; // Initial capacity for the result array
    int** result = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));

    // Step 2: Iterate and use two pointers
    for (int i = 0; i < numsSize - 2; i++) {
        // Skip duplicate elements for the first number
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }

        int left = i + 1;
        int right = numsSize - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            
            if (sum == 0) {
                // Resize arrays if we hit capacity
                if (*returnSize >= capacity) {
                    capacity *= 2;
                    result = (int**)realloc(result, capacity * sizeof(int*));
                    *returnColumnSizes = (int*)realloc(*returnColumnSizes, capacity * sizeof(int));
                }

                // Store the valid triplet
                result[*returnSize] = (int*)malloc(3 * sizeof(int));
                result[*returnSize][0] = nums[i];
                result[*returnSize][1] = nums[left];
                result[*returnSize][2] = nums[right];
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                // Skip duplicates for the second and third numbers
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;

                left++;
                right--;
            } else if (sum < 0) {
                left++; // We need a larger sum
            } else {
                right--; // We need a smaller sum
            }
        }
    }

    return result;
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    if (scanf("%d", &n) != 1) return 1;

    int* nums = (int*)malloc(n * sizeof(int));
    if (n > 0) {
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
        }
    }

    int returnSize;
    int* returnColumnSizes;
    int** result = threeSum(nums, n, &returnSize, &returnColumnSizes);

    printf("Triplets that sum to zero:\n");
    if (returnSize == 0) {
        printf("None found.\n");
    } else {
        for (int i = 0; i < returnSize; i++) {
            printf("[%d, %d, %d]\n", result[i][0], result[i][1], result[i][2]);
        }
    }

    // Free all allocated memory
    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);
    free(nums);

    return 0;
}