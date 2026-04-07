#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int dest;
    struct Node* next;
};

struct Graph {
    int V;
    struct Node** adjList;
};

// Create a directed graph
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjList = (struct Node**)calloc(V, sizeof(struct Node*));
    return graph;
}

// Add a ONE-WAY edge to the directed graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// --- Cycle Detection Logic ---

bool dfs(struct Node** adjList, bool* visited, bool* recStack, int curr) {
    visited[curr] = true;
    recStack[curr] = true;
    
    struct Node* temp = adjList[curr];
    while (temp != NULL) {
        int neighbor = temp->dest;
        
        if (!visited[neighbor]) {
            if (dfs(adjList, visited, recStack, neighbor)) return true;
        } 
        else if (recStack[neighbor]) {
            return true;
        }
        
        temp = temp->next;
    }
    
    recStack[curr] = false;
    return false;
}

bool isCyclic(struct Graph* graph) {
    int V = graph->V;
    bool* visited = (bool*)calloc(V, sizeof(bool));
    bool* recStack = (bool*)calloc(V, sizeof(bool));
    bool cycleFound = false;
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(graph->adjList, visited, recStack, i)) {
                cycleFound = true;
                break;
            }
        }
    }
    
    free(visited);
    free(recStack);
    return cycleFound;
}

// --- Helper Functions ---

void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        struct Node* curr = graph->adjList[i];
        while (curr != NULL) {
            struct Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->adjList);
    free(graph);
}

int main() {
    // --- Test Case 1: Real Cycle ---
    // 0 -> 1 -> 2
    // ^         |
    // |_________|
    struct Graph* graph1 = createGraph(3);
    addEdge(graph1, 0, 1);
    addEdge(graph1, 1, 2);
    addEdge(graph1, 2, 0); // Loops back!

    printf("Test Case 1 (True Cycle):\n");
    if (isCyclic(graph1)) {
        printf("Output: YES\n\n");
    } else {
        printf("Output: NO\n\n");
    }
    freeGraph(graph1);

    // --- Test Case 2: Cross-Edge (No Cycle) ---
    // 0 -> 1 -> 2
    //  \_______/^
    struct Graph* graph2 = createGraph(3);
    addEdge(graph2, 0, 1);
    addEdge(graph2, 1, 2);
    addEdge(graph2, 0, 2); // 0 points directly to 2, but nothing points backwards!

    printf("Test Case 2 (Harmless Cross-Edge):\n");
    if (isCyclic(graph2)) {
        printf("Output: YES\n");
    } else {
        printf("Output: NO\n");
    }
    freeGraph(graph2);

    return 0;
}