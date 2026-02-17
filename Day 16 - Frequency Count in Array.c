#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    
    // Read array size
    if (scanf("%d", &n) != 1) return 0;

    int arr[n];
    
    // Read array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array to group identical elements
    qsort(arr, n, sizeof(int), compare);

    // Iterate and count frequencies
    if (n > 0) {
        int count = 1;
        for (int i = 1; i < n; i++) {
            if (arr[i] == arr[i - 1]) {
                count++;
            } else {
                printf("%d:%d ", arr[i - 1], count);
                count = 1; // Reset count for new element
            }
        }
        // Print the last element and its count
        printf("%d:%d\n", arr[n - 1], count);
    }

    return 0;
}