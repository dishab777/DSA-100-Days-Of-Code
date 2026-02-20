#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort to sort long long integers
int compare(const void *a, const void *b) {
    long long diff = *(long long*)a - *(long long*)b;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

int main() {
    int n;
    
    // Read the size of the array
    if (scanf("%d", &n) != 1) return 1;

    // Handle edge case for size 0 or negative
    if (n <= 0) {
        printf("0\n");
        return 0;
    }

    // Allocate memory for the prefix sum array
    long long *prefix = (long long *)malloc(n * sizeof(long long));
    long long current_sum = 0;
    long long zero_sum_count = 0;

    // Read elements and compute prefix sums
    for (int i = 0; i < n; i++) {
        long long val;
        scanf("%lld", &val);
        current_sum += val;
        prefix[i] = current_sum;
        
        // If the prefix sum itself is 0, it means the subarray 
        // from the start (index 0) to current index has a sum of 0
        if (current_sum == 0) {
            zero_sum_count++;
        }
    }

    // Sort the prefix sums array to group identical sums together
    qsort(prefix, n, sizeof(long long), compare);

    // Count identical prefix sums to find zero-sum subarrays 
    // bounded between two indices
    long long count = 1;
    for (int i = 1; i < n; i++) {
        if (prefix[i] == prefix[i - 1]) {
            count++;
        } else {
            // If a sum appears 'count' times, it contributes count * (count - 1) / 2
            // to the total zero-sum subarrays (Combination formula nC2)
            zero_sum_count += (count * (count - 1)) / 2;
            count = 1; // Reset count for the next unique sum
        }
    }
    
    // Add the combinations for the last grouped sum in the sorted array
    zero_sum_count += (count * (count - 1)) / 2;

    // Print the final result
    printf("%lld\n", zero_sum_count);

    // Free allocated memory
    free(prefix);
    return 0;
}