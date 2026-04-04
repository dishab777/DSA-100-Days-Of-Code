#include <stdio.h>
#include <stdlib.h>

// --- LeetCode Solution Core ---
void dfs(int** image, int m, int n, int r, int c, int originalColor, int newColor) {
    if (r < 0 || r >= m || c < 0 || c >= n || image[r][c] != originalColor) {
        return;
    }
    
    image[r][c] = newColor;
    
    dfs(image, m, n, r - 1, c, originalColor, newColor);
    dfs(image, m, n, r + 1, c, originalColor, newColor);
    dfs(image, m, n, r, c - 1, originalColor, newColor);
    dfs(image, m, n, r, c + 1, originalColor, newColor);
}

int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int color, int* returnSize, int** returnColumnSizes) {
    int m = imageSize;
    int n = imageColSize[0];
    int originalColor = image[sr][sc];
    
    if (originalColor != color) {
        dfs(image, m, n, sr, sc, originalColor, color);
    }
    
    *returnSize = m;
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        (*returnColumnSizes)[i] = imageColSize[i];
    }
    
    return image;
}

// --- Helper Functions for Local Testing ---

// Create a dynamically allocated 2D array
int** createMatrix(int rows, int cols, int values[]) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = values[i * cols + j];
        }
    }
    return matrix;
}

// Free the matrix memory
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}

// Print the grid
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        printf("[ ");
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("]\n");
    }
}

int main() {
    // Example 1:
    // image = [[1,1,1],
    //          [1,1,0],
    //          [1,0,1]]
    // sr = 1, sc = 1, color = 2
    int m = 3, n = 3;
    int sr = 1, sc = 1, newColor = 2;
    int vals[] = {
        1, 1, 1,
        1, 1, 0,
        1, 0, 1
    };
    
    int** image = createMatrix(m, n, vals);
    int colSize[] = {n, n, n};

    printf("Original Image:\n");
    printMatrix(image, m, n);
    
    printf("\nApplying Flood Fill at (%d, %d) with color %d...\n\n", sr, sc, newColor);
    
    int returnSize;
    int* returnColumnSizes;
    int** result = floodFill(image, m, colSize, sr, sc, newColor, &returnSize, &returnColumnSizes);

    printf("Modified Image:\n");
    printMatrix(result, returnSize, returnColumnSizes[0]);

    // Clean up memory
    free(returnColumnSizes);
    freeMatrix(image, m);

    return 0;
}