#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the Linked List Node for the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Define the Graph structure
struct Graph {
    int numVertices;
    struct Node** adjLists; 
    bool* visited; 
};

// --- Graph Building Logic ---

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));
    
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false; 
    }
    
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// --- Cycle Detection Logic ---

bool dfsCycleDetect(struct Graph* graph, int currentVertex, int parentVertex) {
    // Mark the current node as visited
    graph->visited[currentVertex] = true;
    
    // Look at all neighbors
    struct Node* temp = graph->adjLists[currentVertex];
    while (temp != NULL) {
        int neighbor = temp->vertex;
        
        // If neighbor is unvisited, go down that path
        if (!graph->visited[neighbor]) {
            if (dfsCycleDetect(graph, neighbor, currentVertex)) {
                return true;
            }
        } 
        // If neighbor IS visited, and it is NOT the parent we just came from, we found a cycle!
        else if (neighbor != parentVertex) {
            return true;
        }
        
        temp = temp->next;
    }
    
    return false;
}

bool containsCycle(struct Graph* graph) {
    // We must loop through all vertices in case the graph is disconnected
    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            // Pass -1 as the parent of the starting node since it has no parent
            if (dfsCycleDetect(graph, i, -1)) {
                return true;
            }
        }
    }
    return false;
}

// --- Helper Functions ---

void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* curr = graph->adjLists[i];
        while (curr != NULL) {
            struct Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);
}

int main() {
    // --- Test Case 1: Contains a Cycle ---
    // 0 - 1 - 2
    //  \_____/
    struct Graph* graph1 = createGraph(3);
    addEdge(graph1, 0, 1);
    addEdge(graph1, 1, 2);
    addEdge(graph1, 2, 0); // This edge creates the cycle

    printf("Test Case 1 (Triangle Graph):\n");
    if (containsCycle(graph1)) {
        printf("Output: YES\n\n");
    } else {
        printf("Output: NO\n\n");
    }
    freeGraph(graph1);

    // --- Test Case 2: No Cycle ---
    // 0 - 1 - 2 - 3
    struct Graph* graph2 = createGraph(4);
    addEdge(graph2, 0, 1);
    addEdge(graph2, 1, 2);
    addEdge(graph2, 2, 3); 

    printf("Test Case 2 (Straight Line Graph):\n");
    if (containsCycle(graph2)) {
        printf("Output: YES\n");
    } else {
        printf("Output: NO\n");
    }
    freeGraph(graph2);

    return 0;
}