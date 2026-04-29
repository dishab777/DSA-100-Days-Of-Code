#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

bool canPlaceBalls(int* position, int n, int m, int min_force) {
    int balls_placed = 1;
    int last_position = position[0];
    
    for (int i = 1; i < n; i++) {
        if (position[i] - last_position >= min_force) {
            balls_placed++;
            last_position = position[i];
            
            if (balls_placed == m) {
                return true;
            }
        }
    }
    return false;
}

int maxDistance(int* position, int positionSize, int m) {
    qsort(position, positionSize, sizeof(int), compare);
    
    int left = 1;
    int right = position[positionSize - 1] - position[0];
    int best_force = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canPlaceBalls(position, positionSize, m, mid)) {
            best_force = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return best_force;
}

int main() {
    int position1[] = {1, 2, 3, 4, 7};
    int m1 = 3;
    int size1 = sizeof(position1) / sizeof(position1[0]);
    
    printf("Baskets: [1, 2, 3, 4, 7] | Balls: 3\n");
    printf("Max Magnetic Force: %d\n", maxDistance(position1, size1, m1));
    printf("Expected:           3\n\n");
    
    int position2[] = {5, 4, 3, 2, 1, 1000000000};
    int m2 = 2;
    int size2 = sizeof(position2) / sizeof(position2[0]);
    
    printf("Baskets: [5, 4, 3, 2, 1, 1000000000] | Balls: 2\n");
    printf("Max Magnetic Force: %d\n", maxDistance(position2, size2, m2));
    printf("Expected:           999999999\n");
    
    return 0;
}