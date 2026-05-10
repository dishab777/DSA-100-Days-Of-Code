#include <stdio.h>
#include <stdlib.h>

int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize) {
    int max_val = 0;
    for (int i = 0; i < arr1Size; i++) {
        if (arr1[i] > max_val) {
            max_val = arr1[i];
        }
    }
    
    int* count = (int*)calloc(max_val + 1, sizeof(int));
    for (int i = 0; i < arr1Size; i++) {
        count[arr1[i]]++;
    }
    
    int* result = (int*)malloc(arr1Size * sizeof(int));
    int index = 0;
    
    for (int i = 0; i < arr2Size; i++) {
        while (count[arr2[i]] > 0) {
            result[index++] = arr2[i];
            count[arr2[i]]--;
        }
    }
    
    for (int i = 0; i <= max_val; i++) {
        while (count[i] > 0) {
            result[index++] = i;
            count[i]--;
        }
    }
    
    free(count);
    *returnSize = arr1Size;
    return result;
}

int main() {
    int arr1[] = {2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19};
    int arr1Size = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {2, 1, 4, 3, 9, 6};
    int arr2Size = sizeof(arr2) / sizeof(arr2[0]);
    
    int returnSize;
    int* sortedArray = relativeSortArray(arr1, arr1Size, arr2, arr2Size, &returnSize);
    
    printf("arr1: [2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19]\n");
    printf("arr2: [2, 1, 4, 3, 9, 6]\n");
    printf("Sorted:   [");
    for (int i = 0; i < returnSize; i++) {
        printf("%d", sortedArray[i]);
        if (i < returnSize - 1) printf(", ");
    }
    printf("]\nExpected: [2, 2, 2, 1, 4, 3, 3, 9, 6, 7, 19]\n");
    
    free(sortedArray);
    return 0;
}