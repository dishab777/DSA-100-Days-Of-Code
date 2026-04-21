#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int findTheCity(int n, int** edges, int edgesSize, int* edgesColSize, int distanceThreshold) {
    int* dist = (int*)malloc(n * n * sizeof(int));
    
    for (int i = 0; i < n * n; i++) dist[i] = INF;
    for (int i = 0; i < n; i++) dist[i * n + i] = 0;
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        dist[u * n + v] = w;
        dist[v * n + u] = w;
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i * n + k] != INF && dist[k * n + j] != INF) {
                    int detour = dist[i * n + k] + dist[k * n + j];
                    if (detour < dist[i * n + j]) {
                        dist[i * n + j] = detour;
                    }
                }
            }
        }
    }
    
    int minReachable = n + 1;
    int bestCity = -1;
    
    for (int i = 0; i < n; i++) {
        int reachableCount = 0;
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i * n + j] <= distanceThreshold) {
                reachableCount++;
            }
        }
        
        if (reachableCount <= minReachable) {
            minReachable = reachableCount;
            bestCity = i;
        }
    }
    
    free(dist);
    return bestCity;
}

int** createEdges(int size, int raw[][3]) {
    int** edges = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        edges[i] = (int*)malloc(3 * sizeof(int));
        edges[i][0] = raw[i][0];
        edges[i][1] = raw[i][1];
        edges[i][2] = raw[i][2];
    }
    return edges;
}

void freeEdges(int** edges, int size) {
    for (int i = 0; i < size; i++) free(edges[i]);
    free(edges);
}

int main() {
    int n = 4;
    int edgesSize = 4;
    int distanceThreshold = 4;
    
    int raw[][3] = {
        {0, 1, 3},
        {1, 2, 1},
        {1, 3, 4},
        {2, 3, 1}
    };
    
    int** edges = createEdges(edgesSize, raw);
    
    printf("Evaluating cities...\n");
    int bestCity = findTheCity(n, edges, edgesSize, NULL, distanceThreshold);
    
    printf("Best City to live in: %d\n", bestCity);
    printf("Expected Output:      3\n");
    
    freeEdges(edges, edgesSize);

    return 0;
}