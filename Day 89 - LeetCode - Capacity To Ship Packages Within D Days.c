#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Core Logic ---

// Greedy check: Can we ship everything within 'D' days using 'capacity'?
bool canShip(int* weights, int n, int D, int capacity) {
    int days_needed = 1;
    int current_load = 0;
    
    for (int i = 0; i < n; i++) {
        if (current_load + weights[i] > capacity) {
            // Ship is full! Send it off and start a new day.
            days_needed++;
            current_load = weights[i];
            
            // If we've run out of days, this capacity is too small
            if (days_needed > D) {
                return false;
            }
        } else {
            // Keep loading packages onto today's ship
            current_load += weights[i];
        }
    }
    
    return true;
}

int shipWithinDays(int* weights, int weightsSize, int days) {
    int max_weight = 0;
    int sum_weights = 0;
    
    // Calculate the boundaries of our Answer Space
    for (int i = 0; i < weightsSize; i++) {
        if (weights[i] > max_weight) {
            max_weight = weights[i];
        }
        sum_weights += weights[i];
    }
    
    int left = max_weight;  // Minimum possible ship capacity
    int right = sum_weights; // Maximum possible ship capacity
    int best_capacity = right;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canShip(weights, weightsSize, days, mid)) {
            // It works! Save it, and try to find a strictly smaller capacity.
            best_capacity = mid;
            right = mid - 1;
        } else {
            // Ship is too small, takes too many days. Need a bigger ship.
            left = mid + 1;
        }
    }
    
    return best_capacity;
}

// --- Main Execution ---

int main() {
    // Test Case 1
    int weights1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int days1 = 5;
    int size1 = sizeof(weights1) / sizeof(weights1[0]);
    printf("Weights: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] | Target Days: 5\n");
    printf("Minimum Capacity: %d\n", shipWithinDays(weights1, size1, days1));
    printf("Expected:         15\n\n");
    
    // Test Case 2
    int weights2[] = {3, 2, 2, 4, 1, 4};
    int days2 = 3;
    int size2 = sizeof(weights2) / sizeof(weights2[0]);
    printf("Weights: [3, 2, 2, 4, 1, 4] | Target Days: 3\n");
    printf("Minimum Capacity: %d\n", shipWithinDays(weights2, size2, days2));
    printf("Expected:         6\n\n");
    
    // Test Case 3
    int weights3[] = {1, 2, 3, 1, 1};
    int days3 = 4;
    int size3 = sizeof(weights3) / sizeof(weights3[0]);
    printf("Weights: [1, 2, 3, 1, 1] | Target Days: 4\n");
    printf("Minimum Capacity: %d\n", shipWithinDays(weights3, size3, days3));
    printf("Expected:         3\n");
    
    return 0;
}