#include <stdio.h>
#include <stdlib.h>

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    *returnSize = temperaturesSize;
    int* result = (int*)calloc(temperaturesSize, sizeof(int)); 
    
    int* stack = (int*)malloc(temperaturesSize * sizeof(int));
    int top = -1;
    
    for (int i = 0; i < temperaturesSize; i++) {
        while (top >= 0 && temperatures[i] > temperatures[stack[top]]) {
            int prevIndex = stack[top--];
            result[prevIndex] = i - prevIndex;
        }
        stack[++top] = i;
    }
    
    free(stack);
    return result;
}

// Helper function to print arrays
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(",");
    }
    printf("]\n");
}

int main() {
    // Example 1
    int temps1[] = {73, 74, 75, 71, 69, 72, 76, 73};
    int size1 = sizeof(temps1) / sizeof(temps1[0]);
    int returnSize1;
    
    printf("Input: ");
    printArray(temps1, size1);
    
    int* result1 = dailyTemperatures(temps1, size1, &returnSize1);
    printf("Output: ");
    printArray(result1, returnSize1);
    printf("Expected: [1,1,4,2,1,1,0,0]\n\n");
    free(result1);

    // Example 2
    int temps2[] = {30, 40, 50, 60};
    int size2 = sizeof(temps2) / sizeof(temps2[0]);
    int returnSize2;
    
    printf("Input: ");
    printArray(temps2, size2);
    
    int* result2 = dailyTemperatures(temps2, size2, &returnSize2);
    printf("Output: ");
    printArray(result2, returnSize2);
    printf("Expected: [1,1,1,0]\n");
    free(result2);

    return 0;
}