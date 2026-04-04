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
    bool* visited; // Array to keep track of where we have been
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
        graph->visited[i] = false; // Initialize all vertices as unvisited
    }
    
    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // We insert at the HEAD of the linked list for O(1) speed
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// --- DFS Traversal Logic ---

void DFS(struct Graph* graph, int vertex) {
    // 1. Mark the current vertex as visited
    graph->visited[vertex] = true;
    
    // 2. Process (print) the vertex
    printf("%d ", vertex);
    
    // 3. Look at all the neighbors of this vertex
    struct Node* temp = graph->adjLists[vertex];
    
    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        
        // If a neighbor hasn't been visited, recursively travel down that path
        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);
        }
        
        // Move to the next neighbor in the adjacency list
        temp = temp->next;
    }
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
    // Example Input
    // 6 Vertices (0 to 5)
    int n = 6;
    
    struct Graph* graph = createGraph(n);

    // Adding edges to create the following graph:
    //      0
    //     / \
    //    1   2
    //   / \   \
    //  3   4   5
    
    // Note: Because we add to the head of the list, 
    // adding 0-1 then 0-2 means the list for 0 is [2 -> 1].
    // DFS will visit 2 before 1.
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    int startVertex = 0;

    printf("Depth-First Search starting from vertex %d:\n", startVertex);
    printf("Traversal Order: ");
    
    DFS(graph, startVertex);
    
    printf("\n");

    freeGraph(graph);

    return 0;
}