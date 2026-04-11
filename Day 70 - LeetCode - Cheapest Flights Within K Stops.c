#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findCheapestPrice(int n, int** flights, int flightsSize, int* flightsColSize, int src, int dst, int k) {
    int* dist = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;
    
    for (int i = 0; i <= k; i++) {
        int* temp = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            temp[j] = dist[j];
        }
        
        for (int j = 0; j < flightsSize; j++) {
            int u = flights[j][0];
            int v = flights[j][1];
            int weight = flights[j][2];
            
            if (dist[u] != INT_MAX && dist[u] + weight < temp[v]) {
                temp[v] = dist[u] + weight;
            }
        }
        
        free(dist);
        dist = temp;
    }
    
    int result = dist[dst] == INT_MAX ? -1 : dist[dst];
    free(dist);
    
    return result;
}

int** createFlights(int size, int raw[][3]) {
    if (size == 0) return NULL;
    int** flights = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        flights[i] = (int*)malloc(3 * sizeof(int));
        flights[i][0] = raw[i][0];
        flights[i][1] = raw[i][1];
        flights[i][2] = raw[i][2];
    }
    return flights;
}

void freeFlights(int** flights, int size) {
    for (int i = 0; i < size; i++) free(flights[i]);
    free(flights);
}

int main() {
    int n = 4;
    int size = 5;
    int raw[][3] = {
        {0, 1, 100}, 
        {1, 2, 100}, 
        {2, 0, 100}, 
        {1, 3, 600}, 
        {2, 3, 200}
    };
    int src = 0;
    int dst = 3;
    int k = 1;
    
    int** flights = createFlights(size, raw);
    
    printf("Evaluating Cheapest Flights...\n");
    printf("Source: %d | Destination: %d | Max Stops (K): %d\n\n", src, dst, k);
    
    int result = findCheapestPrice(n, flights, size, NULL, src, dst, k);
    
    printf("Cheapest Price: %d\n", result);
    printf("Expected:       700\n");
    
    freeFlights(flights, size);

    return 0;
}