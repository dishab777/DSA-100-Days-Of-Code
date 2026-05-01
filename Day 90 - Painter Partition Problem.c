#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValid(int* boards, int n, int k, long long max_time) {
    int painters_needed = 1;
    long long current_time = 0;
    
    for (int i = 0; i < n; i++) {
        if (boards[i] > max_time) {
            return false;
        }
        
        if (current_time + boards[i] > max_time) {
            painters_needed++;
            current_time = boards[i];
            
            if (painters_needed > k) {
                return false;
            }
        } else {
            current_time += boards[i];
        }
    }
    
    return true;
}

long long findMinTime(int* boards, int n, int k) {
    long long sum = 0;
    int max_val = 0;
    
    for (int i = 0; i < n; i++) {
        sum += boards[i];
        if (boards[i] > max_val) {
            max_val = boards[i];
        }
    }
    
    long long left = max_val;
    long long right = sum;
    long long best_time = right;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        if (isValid(boards, n, k, mid)) {
            best_time = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return best_time;
}

int main() {
    int n, k;
    
    if (scanf("%d %d", &n, &k) != 2) return 0;
    
    int* boards = (int*)malloc(n * sizeof(int));
    if (boards == NULL) return 1;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &boards[i]);
    }
    
    long long result = findMinTime(boards, n, k);
    printf("%lld\n", result);
    
    free(boards);
    return 0;
}