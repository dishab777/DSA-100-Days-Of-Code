#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct AdjNode {
    int dest;
    int weight;
    struct AdjNode* next;
} AdjNode;

void addEdge(AdjNode** adjList, int u, int v, int w) {
    AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->dest = v;
    newNode->weight = w;
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

typedef struct HeapNode {
    int vertex;
    int dist;
} HeapNode;

typedef struct MinHeap {
    HeapNode* array;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    return heap;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left].dist < heap->array[smallest].dist)
        smallest = left;
    if (right < heap->size && heap->array[right].dist < heap->array[smallest].dist)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->array[idx], &heap->array[smallest]);
        minHeapify(heap, smallest);
    }
}

HeapNode extractMin(MinHeap* heap) {
    if (heap->size == 0) return (HeapNode){-1, -1};
    if (heap->size == 1) {
        heap->size--;
        return heap->array[0];
    }
    HeapNode root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return root;
}

void insert(MinHeap* heap, int vertex, int dist) {
    if (heap->size == heap->capacity) return;
    heap->size++;
    int i = heap->size - 1;
    heap->array[i] = (HeapNode){vertex, dist};

    while (i != 0 && heap->array[(i - 1) / 2].dist > heap->array[i].dist) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    AdjNode** adjList = (AdjNode**)calloc(n + 1, sizeof(AdjNode*));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(adjList, u, v, w);
    }

    int source;
    scanf("%d", &source);

    int* dist = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }

    MinHeap* heap = createMinHeap(m + n);
    
    dist[source] = 0;
    insert(heap, source, 0);

    while (heap->size > 0) {
        HeapNode node = extractMin(heap);
        int u = node.vertex;
        int d = node.dist;

        if (d > dist[u]) continue;

        AdjNode* curr = adjList[u];
        while (curr != NULL) {
            int v = curr->dest;
            int weight = curr->weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                insert(heap, v, dist[v]);
            }
            curr = curr->next;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) {
            printf("INF "); 
        } else {
            printf("%d ", dist[i]);
        }
    }
    printf("\n");

    for (int i = 1; i <= n; i++) {
        AdjNode* curr = adjList[i];
        while (curr != NULL) {
            AdjNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(adjList);
    free(dist);
    free(heap->array);
    free(heap);

    return 0;
}