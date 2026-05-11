#include <stdio.h>
#include <stdlib.h>

int compareIntervals(const void* a, const void* b) {
    int* intervalA = *(int**)a;
    int* intervalB = *(int**)b;
    return intervalA[0] - intervalB[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    if (intervalsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    qsort(intervals, intervalsSize, sizeof(int*), compareIntervals);
    
    int** merged = (int**)malloc(intervalsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(intervalsSize * sizeof(int));
    
    merged[0] = (int*)malloc(2 * sizeof(int));
    merged[0][0] = intervals[0][0];
    merged[0][1] = intervals[0][1];
    (*returnColumnSizes)[0] = 2;
    int k = 1;
    
    for (int i = 1; i < intervalsSize; i++) {
        if (intervals[i][0] <= merged[k - 1][1]) {
            if (intervals[i][1] > merged[k - 1][1]) {
                merged[k - 1][1] = intervals[i][1];
            }
        } else {
            merged[k] = (int*)malloc(2 * sizeof(int));
            merged[k][0] = intervals[i][0];
            merged[k][1] = intervals[i][1];
            (*returnColumnSizes)[k] = 2;
            k++;
        }
    }
    
    *returnSize = k;
    return merged;
}

int main() {
    int arr[][2] = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    int size = 4;
    int* intervals[4];
    for (int i = 0; i < size; i++) intervals[i] = arr[i];
    
    int returnSize;
    int* returnColumnSizes;
    
    int** merged = merge(intervals, size, NULL, &returnSize, &returnColumnSizes);
    
    printf("Original: [[1, 3], [2, 6], [8, 10], [15, 18]]\n");
    printf("Merged:   [");
    for (int i = 0; i < returnSize; i++) {
        printf("[%d, %d]", merged[i][0], merged[i][1]);
        if (i < returnSize - 1) printf(", ");
        free(merged[i]);
    }
    printf("]\n");
    
    free(merged);
    free(returnColumnSizes);
    
    return 0;
}