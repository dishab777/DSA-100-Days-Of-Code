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

// Add a ONE-WAY edge
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// --- DFS Topological Sort Logic ---

void dfs(struct Graph* graph, int curr, bool* visited, int* stack, int* top) {
    visited[curr] = true;
    
    struct Node* temp = graph->adjList[curr];
    while (temp != NULL) {
        int neighbor = temp->dest;
        if (!visited[neighbor]) {
            dfs(graph, neighbor, visited, stack, top);
        }
        temp = temp->next;
    }
    
    stack[(*top)++] = curr;
}

void topologicalSort(struct Graph* graph) {
    int V = graph->V;
    bool* visited = (bool*)calloc(V, sizeof(bool));
    int* stack = (int*)malloc(V * sizeof(int));
    int top = 0;
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(graph, i, visited, stack, &top);
        }
    }
    
    printf("Topological Sort: ");
    while (top > 0) {
        printf("%d ", stack[--top]);
    }
    printf("\n");
    
    free(visited);
    free(stack);
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
    // Constructing a DAG (Directed Acyclic Graph)
    // 5 -> 0 <- 4
    // |         |
    // v         v
    // 2 -> 3 -> 1
    int V = 6;
    struct Graph* graph = createGraph(V);
    
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    printf("Executing DFS Topological Sort on a DAG with %d vertices...\n", V);
    topologicalSort(graph);
    // Expected valid topological sorts: 
    // 5 4 2 3 1 0  or  4 5 2 3 1 0 (depending on vertex processing order)

    freeGraph(graph);

    return 0;
}