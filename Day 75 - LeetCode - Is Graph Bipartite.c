#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool dfs(int** graph, int* graphColSize, int* colors, int node, int color) {
    colors[node] = color;
    
    for (int i = 0; i < graphColSize[node]; i++) {
        int neighbor = graph[node][i];
        
        if (colors[neighbor] == 0) {
            if (!dfs(graph, graphColSize, colors, neighbor, -color)) {
                return false;
            }
        } else if (colors[neighbor] == color) {
            return false;
        }
    }
    return true;
}

bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    int* colors = (int*)calloc(graphSize, sizeof(int));
    
    for (int i = 0; i < graphSize; i++) {
        if (colors[i] == 0) {
            if (!dfs(graph, graphColSize, colors, i, 1)) {
                free(colors);
                return false;
            }
        }
    }
    
    free(colors);
    return true;
}

int** createGraph(int numNodes, int* colSizes, int raw[][4]) {
    int** graph = (int**)malloc(numNodes * sizeof(int*));
    for (int i = 0; i < numNodes; i++) {
        if (colSizes[i] > 0) {
            graph[i] = (int*)malloc(colSizes[i] * sizeof(int));
            for (int j = 0; j < colSizes[i]; j++) {
                graph[i][j] = raw[i][j];
            }
        } else {
            graph[i] = NULL;
        }
    }
    return graph;
}

void freeGraph(int** graph, int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        free(graph[i]);
    }
    free(graph);
}

int main() {
    int size1 = 4;
    int colSize1[] = {3, 2, 3, 2};
    int raw1[][4] = {
        {1, 2, 3}, 
        {0, 2}, 
        {0, 1, 3}, 
        {0, 2}
    };
    int** graph1 = createGraph(size1, colSize1, raw1);
    
    printf("Test Case 1:\n");
    bool result1 = isBipartite(graph1, size1, colSize1);
    printf("Is Bipartite? %s\n", result1 ? "true" : "false");
    printf("Expected:     false\n\n");
    freeGraph(graph1, size1);

    int size2 = 4;
    int colSize2[] = {2, 2, 2, 2};
    int raw2[][4] = {
        {1, 3}, 
        {0, 2}, 
        {1, 3}, 
        {0, 2}
    };
    int** graph2 = createGraph(size2, colSize2, raw2);

    printf("Test Case 2:\n");
    bool result2 = isBipartite(graph2, size2, colSize2);
    printf("Is Bipartite? %s\n", result2 ? "true" : "false");
    printf("Expected:     true\n");
    freeGraph(graph2, size2);

    return 0;
}