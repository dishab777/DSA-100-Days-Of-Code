#include <stdio.h>
#include <stdlib.h>

int lowerBound(int* arr, int n, int x) {
    int left = 0;
    int right = n - 1;
    int ans = n;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] >= x) {
            ans = mid;
            right = mid - 1;
        } 
    
        else {
            left = mid + 1;
        }
    }
    
    return ans;
}

int upperBound(int* arr, int n, int x) {
    int left = 0;
    int right = n - 1;
    int ans = n;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
    
        if (arr[mid] > x) {
            ans = mid;
            right = mid - 1;
        } 
    
        else {
            left = mid + 1;
        }
    }
    
    return ans;
}


int main() {
    int n, x;

    if (scanf("%d", &n) != 1) return 0;

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) return 1;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    scanf("%d", &x);
    
    int lb = lowerBound(arr, n, x);
    int ub = upperBound(arr, n, x);
    
    printf("%d %d\n", lb, ub);
    
    free(arr);
    
    return 0;
}