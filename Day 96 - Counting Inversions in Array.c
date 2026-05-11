#include <stdio.h>
#include <stdlib.h>

long long mergeAndCount(int* arr, int* temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    long long inv_count = 0;

    while ((i <= mid) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inv_count;
}

long long mergeSortAndCount(int* arr, int* temp, int left, int right) {
    long long inv_count = 0;
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        inv_count += mergeSortAndCount(arr, temp, left, mid);
        inv_count += mergeSortAndCount(arr, temp, mid + 1, right);
        inv_count += mergeAndCount(arr, temp, left, mid, right);
    }
    
    return inv_count;
}

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) return 0;
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) return 1;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int* temp = (int*)malloc(n * sizeof(int));
    if (temp == NULL) {
        free(arr);
        return 1;
    }
    
    long long total_inversions = mergeSortAndCount(arr, temp, 0, n - 1);
    
    printf("%lld\n", total_inversions);
    
    free(arr);
    free(temp);
    return 0;
}