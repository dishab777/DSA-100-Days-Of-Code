#include <stdio.h>

// Function to remove all occurrences of val in-place
int removeElement(int* nums, int numsSize, int val) {
    int k = 0; // k tracks the position for the next non-val element

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != val) {
            nums[k] = nums[i];
            k++;
        }
    }
    return k;
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    if (scanf("%d", &n) != 1) return 1;

    int nums[1000]; // Assuming max size 1000 for testing
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int val;
    printf("Enter the value to remove: ");
    scanf("%d", &val);

    // Call the function
    int k = removeElement(nums, n, val);

    // Print the result
    printf("New size (k): %d\n", k);
    printf("Modified array: ");
    for (int i = 0; i < k; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}