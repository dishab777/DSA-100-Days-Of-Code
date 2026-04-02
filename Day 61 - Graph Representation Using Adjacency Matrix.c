#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Core Logic ---
int** buildAdjacencyMatrix(int n, int m, int edges[][2], bool isDirected) {
    // Dynamically allocate an n x n matrix. 
    // Using calloc ensures every cell is automatically initialized to 0.
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));
    }

    // Populate the matrix with the edges
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        // Mark the edge from u to v
        matrix[u][v] = 1;

        // If the graph is undirected, the edge goes both ways
        if (!isDirected) {
            matrix[v][u] = 1;
        }
    }

    return matrix;
}

// --- Helper Functions ---

// Function to cleanly print the adjacency matrix
void printMatrix(int** matrix, int n) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Free the allocated memory to prevent memory leaks
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    // Example Input
    // 4 Vertices (0, 1, 2, 3)
    // 4 Edges
    int n = 4;
    int m = 4;
    
    // Pairs (u, v)
    int edges[4][2] = {
        {0, 1},
        {0, 2},
        {1, 2},
        {2, 3}
    };

    // --- Undirected Test ---
    printf("--- UNDIRECTED GRAPH ---\n");
    bool isDirected = false;
    int** undirectedMatrix = buildAdjacencyMatrix(n, m, edges, isDirected);
    printMatrix(undirectedMatrix, n);
    freeMatrix(undirectedMatrix, n);

    printf("\n");

    // --- Directed Test ---
    printf("--- DIRECTED GRAPH ---\n");
    isDirected = true;
    int** directedMatrix = buildAdjacencyMatrix(n, m, edges, isDirected);
    printMatrix(directedMatrix, n);
    freeMatrix(directedMatrix, n);

    return 0;
}