#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

bool canPlaceCows(int* stalls, int n, int k, int min_dist) {
    int cows_placed = 1;
    int last_position = stalls[0];
    
    for (int i = 1; i < n; i++) {

        if (stalls[i] - last_position >= min_dist) {
    
            cows_placed++;
            last_position = stalls[i];
        }
        
        if (cows_placed == k) {
            return true;
        }
    }
    
    return false;
}

int aggressiveCows(int* stalls, int n, int k) {
    qsort(stalls, n, sizeof(int), compare);
    
    int left = 1; 
    int right = stalls[n - 1] - stalls[0]; 
    int best_gap = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canPlaceCows(stalls, n, k, mid)) {
    
            best_gap = mid;
            left = mid + 1;
        } else {
    
            right = mid - 1;
        }
    }
    
    return best_gap;
}


int main() {
    int n, k;
    
    if (scanf("%d %d", &n, &k) != 2) return 0;
    
    int* stalls = (int*)malloc(n * sizeof(int));
    if (stalls == NULL) return 1;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &stalls[i]);
    }
    
    int result = aggressiveCows(stalls, n, k);
    printf("%d\n", result);
    
    free(stalls);
    
    return 0;
}