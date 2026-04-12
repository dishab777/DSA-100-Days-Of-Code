#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize) {
    int n = pointsSize;
    
    bool visited[1000] = {false};
    int minDist[1000];
    
    for (int i = 0; i < n; i++) {
        minDist[i] = INT_MAX;
    }
    
    minDist[0] = 0;
    int totalCost = 0;
    
    for (int i = 0; i < n; i++) {
        int u = -1;
        int currentMin = INT_MAX;
        
        for (int j = 0; j < n; j++) {
            if (!visited[j] && minDist[j] < currentMin) {
                currentMin = minDist[j];
                u = j;
            }
        }
        
        visited[u] = true;
        totalCost += currentMin;
        
        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                int dist = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                if (dist < minDist[v]) {
                    minDist[v] = dist;
                }
            }
        }
    }
    
    return totalCost;
}

int** createPoints(int size, int raw[][2]) {
    if (size == 0) return NULL;
    int** points = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        points[i] = (int*)malloc(2 * sizeof(int));
        points[i][0] = raw[i][0];
        points[i][1] = raw[i][1];
    }
    return points;
}

void freePoints(int** points, int size) {
    for (int i = 0; i < size; i++) free(points[i]);
    free(points);
}

int main() {
    int size = 5;
    int raw[][2] = {
        {0, 0}, 
        {2, 2}, 
        {3, 10}, 
        {5, 2}, 
        {7, 0}
    };
    
    int** points = createPoints(size, raw);
    
    printf("Calculating Minimum Spanning Tree (Prim's Algorithm)...\n\n");
    
    int result = minCostConnectPoints(points, size, NULL);
    
    printf("Minimum Cost to Connect All Points: %d\n", result);
    printf("Expected Output:                    20\n");
    
    freePoints(points, size);

    return 0;
}