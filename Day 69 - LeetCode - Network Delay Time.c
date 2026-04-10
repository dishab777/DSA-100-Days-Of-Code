#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NODES 101

// --- LeetCode Solution Core ---
int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k) {
    int adj[MAX_NODES][MAX_NODES];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = -1;
        }
    }
    
    for (int i = 0; i < timesSize; i++) {
        int u = times[i][0];
        int v = times[i][1];
        int w = times[i][2];
        adj[u][v] = w;
    }
    
    int dist[MAX_NODES];
    bool visited[MAX_NODES];
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    
    dist[k] = 0;
    
    for (int i = 0; i < n; i++) {
        int u = -1;
        int minDist = INT_MAX;
        
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        
        if (u == -1) break;
        visited[u] = true;
        
        for (int v = 1; v <= n; v++) {
            if (adj[u][v] != -1 && !visited[v]) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }
    
    int maxTime = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) return -1;
        if (dist[i] > maxTime) maxTime = dist[i];
    }
    
    return maxTime;
}

// --- Helper Functions for Local Testing ---

int** createTimes(int size, int raw[][3]) {
    if (size == 0) return NULL;
    int** times = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        times[i] = (int*)malloc(3 * sizeof(int));
        times[i][0] = raw[i][0];
        times[i][1] = raw[i][1];
        times[i][2] = raw[i][2];
    }
    return times;
}

void freeTimes(int** times, int size) {
    for (int i = 0; i < size; i++) free(times[i]);
    free(times);
}

int main() {
    // --- Test Case 1 ---
    // times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
    // Signal travels from 2 -> 1 (time 1)
    // Signal travels from 2 -> 3 (time 1)
    // Signal travels from 3 -> 4 (time 1) -> Total time to reach 4 is 2.
    int size = 3;
    int raw[][3] = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n = 4;
    int k = 2;
    
    int** times = createTimes(size, raw);
    
    printf("Evaluating Network Delay Time...\n");
    printf("Sending signal from Node %d\n\n", k);
    
    int result = networkDelayTime(times, size, NULL, n, k);
    
    printf("Minimum time for all nodes to receive signal: %d\n", result);
    printf("Expected output: 2\n");
    
    freeTimes(times, size);

    return 0;
}