#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct Edge {
    int u, v, w;
};
struct Graph {
    int V, E;
    struct Edge* edges;
};
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

void bellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int* dist = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edges[j].u;
            int v = graph->edges[j].v;
            int w = graph->edges[j].w;
            
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int j = 0; j < E; j++) {
        int u = graph->edges[j].u;
        int v = graph->edges[j].v;
        int w = graph->edges[j].w;
        
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("NEGATIVE CYCLE DETECTED\n");
            free(dist);
            return;
        }
    }

    printf("Vertex \t Distance from Source (%d)\n", src);
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX) {
            printf("%d \t INF\n", i);
        } else {
            printf("%d \t %d\n", i, dist[i]);
        }
    }

    free(dist);
}

void freeGraph(struct Graph* graph) {
    free(graph->edges);
    free(graph);
}

int main() {
    int V1 = 5; 
    int E1 = 8;
    struct Graph* graph1 = createGraph(V1, E1);

    graph1->edges[0] = (struct Edge){0, 1, -1};
    graph1->edges[1] = (struct Edge){0, 2, 4};
    graph1->edges[2] = (struct Edge){1, 2, 3};
    graph1->edges[3] = (struct Edge){1, 3, 2};
    graph1->edges[4] = (struct Edge){1, 4, 2};
    graph1->edges[5] = (struct Edge){3, 2, 5};
    graph1->edges[6] = (struct Edge){3, 1, 1};
    graph1->edges[7] = (struct Edge){4, 3, -3};

    printf("--- Test Case 1: Standard Graph with Negative Edges ---\n");
    bellmanFord(graph1, 0);
    freeGraph(graph1);
    printf("\n");

    int V2 = 4;
    int E2 = 4;
    struct Graph* graph2 = createGraph(V2, E2);
    
    graph2->edges[0] = (struct Edge){0, 1, 1};
    graph2->edges[1] = (struct Edge){1, 2, -1};
    graph2->edges[2] = (struct Edge){2, 3, -1};
    graph2->edges[3] = (struct Edge){3, 1, -1};

    printf("--- Test Case 2: Graph with Negative Cycle ---\n");
    bellmanFord(graph2, 0);
    freeGraph(graph2);

    return 0;
}