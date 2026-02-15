#include <stdio.h>
#include <stdlib.h>

// Function to set rows and columns to zero
void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int m = matrixSize;
    int n = matrixColSize[0];
    int firstRowZero = 0;
    int firstColZero = 0;

    // 1. Check if the first row has any zeros
    for (int j = 0; j < n; j++) {
        if (matrix[0][j] == 0) {
            firstRowZero = 1;
            break;
        }
    }

    // 2. Check if the first column has any zeros
    for (int i = 0; i < m; i++) {
        if (matrix[i][0] == 0) {
            firstColZero = 1;
            break;
        }
    }

    // 3. Use first row and column as markers for the rest of the matrix
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    // 4. Set matrix elements to zero based on markers
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
    }

    // 5. Handle the first row if needed
    if (firstRowZero) {
        for (int j = 0; j < n; j++) {
            matrix[0][j] = 0;
        }
    }

    // 6. Handle the first column if needed
    if (firstColZero) {
        for (int i = 0; i < m; i++) {
            matrix[i][0] = 0;
        }
    }
}

int main() {
    int m, n;
    printf("Enter rows and columns: ");
    if (scanf("%d %d", &m, &n) != 2) return 1;

    // Allocate memory for the matrix
    int** matrix = (int**)malloc(m * sizeof(int*));
    int* matrixColSize = (int*)malloc(m * sizeof(int));

    printf("Enter matrix elements:\n");
    for (int i = 0; i < m; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        matrixColSize[i] = n; // Store column size for LeetCode compatibility
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Call the function
    setZeroes(matrix, m, matrixColSize);

    // Print the result
    printf("Modified Matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(matrixColSize);

    return 0;
}