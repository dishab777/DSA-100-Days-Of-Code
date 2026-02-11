#include <stdio.h>
#include <stdlib.h>

int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes) 
{
    int rows = matrixSize;
    int cols = matrixColSize[0];
    int** result = (int**)malloc(cols * sizeof(int*));
    *returnColumnSizes = (int*)malloc(cols * sizeof(int));
    *returnSize = cols;
    
    for (int i = 0; i < cols; i++) 
    {
        result[i] = (int*)malloc(rows * sizeof(int));
        (*returnColumnSizes)[i] = rows;
        for (int j = 0; j < rows; j++) 
        {
            result[i][j] = matrix[j][i];
        }
    }
    
    return result;
}

int main() 
{
    int r, c;
    printf("Enter rows and columns: ");
    if (scanf("%d %d", &r, &c) != 2) return 1;

    int** matrix = (int**)malloc(r * sizeof(int*));
    int* matrixColSize = (int*)malloc(r * sizeof(int));

    printf("Enter matrix elements:\n");
    for (int i = 0; i < r; i++) 
    {
        matrix[i] = (int*)malloc(c * sizeof(int));
        matrixColSize[i] = c;
        for (int j = 0; j < c; j++) 
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    int returnSize;
    int* returnColumnSizes;
    int** result = transpose(matrix, r, matrixColSize, &returnSize, &returnColumnSizes);

    printf("Transposed Matrix:\n");
    for (int i = 0; i < returnSize; i++) 
    {
        for (int j = 0; j < returnColumnSizes[i]; j++) 
        {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < r; i++) free(matrix[i]);
    free(matrix);
    free(matrixColSize);
    
    for (int i = 0; i < returnSize; i++) free(result[i]);
    free(result);
    free(returnColumnSizes);

    return 0;
}