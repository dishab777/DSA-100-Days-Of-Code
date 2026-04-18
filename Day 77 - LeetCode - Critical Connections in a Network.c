#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct EdgeNode {
    int dest;
    struct EdgeNode* next;
} EdgeNode;

int timer = 0;

void dfs(int u, int parent, EdgeNode** adjList, int* tin, int* low, int** result, int* resultSize) {
    tin[u] = low[u] = ++timer;
    
    for (EdgeNode* e = adjList[u]; e != NULL; e = e->next) {
        int v = e->dest;
        
        if (v == parent) continue;
        
        if (tin[v] != 0) {
            low[u] = MIN(low[u], tin[v]);
        } else {
            dfs(v, u, adjList, tin, low, result, resultSize);
            low[u] = MIN(low[u], low[v]);
            
            if (low[v] > tin[u]) {
                result[*resultSize] = (int*)malloc(2 * sizeof(int));
                result[*resultSize][0] = u;
                result[*resultSize][1] = v;
                (*resultSize)++;
            }
        }
    }
}

int** criticalConnections(int n, int** connections, int connectionsSize, int* connectionsColSize, int* returnSize, int** returnColumnSizes) {
    EdgeNode* edgePool = (EdgeNode*)malloc(2 * connectionsSize * sizeof(EdgeNode));
    int poolIdx = 0;
    EdgeNode** adjList = (EdgeNode**)calloc(n, sizeof(EdgeNode*));
    
    for (int i = 0; i < connectionsSize; i++) {
        int u = connections[i][0];
        int v = connections[i][1];
        
        edgePool[poolIdx].dest = v;
        edgePool[poolIdx].next = adjList[u];
        adjList[u] = &edgePool[poolIdx++];
        
        edgePool[poolIdx].dest = u;
        edgePool[poolIdx].next = adjList[v];
        adjList[v] = &edgePool[poolIdx++];
    }
    
    int* tin = (int*)calloc(n, sizeof(int));
    int* low = (int*)calloc(n, sizeof(int));
    timer = 0;
    
    int** result = (int**)malloc(connectionsSize * sizeof(int*));
    *returnSize = 0;
    
    dfs(0, -1, adjList, tin, low, result, returnSize);
    
    *returnColumnSizes = (int*)malloc((*returnSize) * sizeof(int));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    
    free(tin);
    free(low);
    free(adjList);
    free(edgePool);
    
    return result;
}

int** createConnections(int size, int raw[][2]) {
    int** connections = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        connections[i] = (int*)malloc(2 * sizeof(int));
        connections[i][0] = raw[i][0];
        connections[i][1] = raw[i][1];
    }
    return connections;
}

void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) free(matrix[i]);
    free(matrix);
}

int main() {
    
    int n = 4;
    int size = 4;
    int raw[][2] = {
        {0, 1}, 
        {1, 2}, 
        {2, 0}, 
        {1, 3}
    };
    
    int** connections = createConnections(size, raw);
    
    printf("Scanning network for Critical Connections (Tarjan's Algorithm)...\n\n");
    
    int returnSize;
    int* returnColSizes;
    int** result = criticalConnections(n, connections, size, NULL, &returnSize, &returnColSizes);
    
    printf("Critical Connections Found: %d\n", returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("Vulnerable Edge: [%d, %d]\n", result[i][0], result[i][1]);
    }
    
    freeMatrix(connections, size);
    freeMatrix(result, returnSize);
    free(returnColSizes);

    return 0;
}