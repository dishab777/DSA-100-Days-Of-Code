#include <stdio.h>
#include <stdlib.h>

// --- LeetCode Solution Core ---
void dfs(int** isConnected, int n, int city, int* visited) {
    for (int j = 0; j < n; j++) {
        if (isConnected[city][j] == 1 && visited[j] == 0) {
            visited[j] = 1;
            dfs(isConnected, n, j, visited);
        }
    }
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize) {
    int n = isConnectedSize;
    int provinces = 0;
    
    int* visited = (int*)calloc(n, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            provinces++;
            visited[i] = 1;
            dfs(isConnected, n, i, visited);
        }
    }
    
    free(visited);
    return provinces;
}

// --- Helper Functions for Local Testing ---

// Create a dynamically allocated 2D Adjacency Matrix
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

int main() {
    // Example 1:
    // isConnected = [[1,1,0],
    //                [1,1,0],
    //                [0,0,1]]
    int n = 3;
    int vals[] = {
        1, 1, 0,
        1, 1, 0,
        0, 0, 1
    };
    
    int** isConnected = createMatrix(n, n, vals);
    int colSize[] = {n, n, n};

    printf("Calculating Number of Provinces...\n\n");
    
    int result = findCircleNum(isConnected, n, colSize);

    printf("Total Provinces: %d\n", result);
    printf("Expected Output: 2\n");

    // Clean up memory
    freeMatrix(isConnected, n);

    return 0;
}