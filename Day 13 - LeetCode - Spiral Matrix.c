#include <stdio.h>
#include <stdlib.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    if (matrixSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    int rows = matrixSize;
    int cols = matrixColSize[0];
    int totalElements = rows * cols;
    int* result = (int*)malloc(totalElements * sizeof(int));
    *returnSize = totalElements;

    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;
    int index = 0;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) {
            result[index++] = matrix[top][i];
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            result[index++] = matrix[i][right];
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                result[index++] = matrix[bottom][i];
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                result[index++] = matrix[i][left];
            }
            left++;
        }
    }

    return result;
}

int main() {
    int r, c;
    printf("Enter rows and columns: ");
    if (scanf("%d %d", &r, &c) != 2) return 1;

    int** matrix = (int**)malloc(r * sizeof(int*));
    int* matrixColSize = (int*)malloc(r * sizeof(int));

    printf("Enter matrix elements:\n");
    for (int i = 0; i < r; i++) {
        matrix[i] = (int*)malloc(c * sizeof(int));
        matrixColSize[i] = c;
        for (int j = 0; j < c; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int returnSize;
    int* result = spiralOrder(matrix, r, matrixColSize, &returnSize);

    printf("Spiral Order: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    for (int i = 0; i < r; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(matrixColSize);
    free(result);

    return 0;
}