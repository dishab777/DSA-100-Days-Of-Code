#include <stdio.h>
#include <stdlib.h>

// Define the Linked List Node for the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Define the Graph structure
struct Graph {
    int numVertices;
    struct Node** adjLists; // Array of pointers to Linked List nodes
};

// --- Core Logic ---

// Helper function to create a new linked list node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    
    // Allocate memory for the array of adjacency lists
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    
    // Initialize all lists as empty (NULL)
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    
    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // 1. Add an edge from src to dest
    // We insert at the HEAD of the linked list because it's O(1) time complexity
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // 2. Add an edge from dest to src (because it is undirected)
    // If this were a directed graph, we would simply delete this second block
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// --- Helper Functions ---

// Function to print the entire adjacency list
void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* temp = graph->adjLists[i];
        printf("Vertex %d: ", i);
        while (temp != NULL) {
            printf("%d", temp->vertex);
            if (temp->next != NULL) {
                printf(" -> ");
            }
            temp = temp->next;
        }
        printf("\n");
    }
}

// Free the allocated memory to prevent memory leaks
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
    free(graph);
}

int main() {
    // Example Input
    // 5 Vertices (0 to 4)
    // 6 Edges
    int n = 5;
    int m = 6;
    
    // Pairs (u, v)
    int edges[6][2] = {
        {0, 1},
        {0, 4},
        {1, 2},
        {1, 3},
        {1, 4},
        {2, 3}
    };

    printf("Building Graph using Adjacency Lists...\n\n");

    // Initialize Graph
    struct Graph* graph = createGraph(n);

    // Add all edges
    for (int i = 0; i < m; i++) {
        addEdge(graph, edges[i][0], edges[i][1]);
    }

    // Print the results
    printGraph(graph);

    // Clean up memory
    freeGraph(graph);

    return 0;
}