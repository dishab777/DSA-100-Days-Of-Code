#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int dest;
    struct Node* next;
};

void addEdge(struct Node** adjList, int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

bool dfs(struct Node** adjList, bool* visited, int curr, int parent) {
    visited[curr] = true;
    
    struct Node* temp = adjList[curr];
    while (temp != NULL) {
        int neighbor = temp->dest;
        if (!visited[neighbor]) {
            if (dfs(adjList, visited, neighbor, curr)) return true;
        } 
        else if (neighbor != parent) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool isCycle(int V, int E, int** edges) {
    struct Node** adjList = (struct Node**)calloc(V, sizeof(struct Node*));
    for (int i = 0; i < E; i++) {
        addEdge(adjList, edges[i][0], edges[i][1]);
        addEdge(adjList, edges[i][1], edges[i][0]); 
    }
    
    bool* visited = (bool*)calloc(V, sizeof(bool));
    bool cycleFound = false;
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(adjList, visited, i, -1)) {
                cycleFound = true;
                break; 
            }
        }
    }
    
    for (int i = 0; i < V; i++) {
        struct Node* curr = adjList[i];
        while (curr != NULL) {
            struct Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(adjList);
    free(visited);
    
    return cycleFound;
}

// --- Helper for creating 2D edge array ---
int** createEdges(int E, int rawEdges[][2]) {
    int** edges = (int**)malloc(E * sizeof(int*));
    for (int i = 0; i < E; i++) {
        edges[i] = (int*)malloc(2 * sizeof(int));
        edges[i][0] = rawEdges[i][0];
        edges[i][1] = rawEdges[i][1];
    }
    return edges;
}

void freeEdges(int** edges, int E) {
    for (int i = 0; i < E; i++) free(edges[i]);
    free(edges);
}

int main() {
    // --- Test Case: Multiple Components ---
    // Component 1: 0 - 1 - 2 (No Cycle)
    // Component 2: 3 - 4 - 5
    //               \_____/  (Cycle!)
    int V = 6;
    int E = 5;
    int rawEdges[][2] = {
        {0, 1}, {1, 2},         // Island 1
        {3, 4}, {4, 5}, {5, 3}  // Island 2
    };
    
    int** edges = createEdges(E, rawEdges);
    
    printf("Evaluating Graph with %d vertices and %d edges...\n", V, E);
    
    if (isCycle(V, E, edges)) {
        printf("Result: YES, the graph contains a cycle.\n");
    } else {
        printf("Result: NO, the graph does not contain a cycle.\n");
    }
    
    freeEdges(edges, E);
    
    return 0;
}