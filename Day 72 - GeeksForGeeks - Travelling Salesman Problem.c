#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int tsp(int mask, int pos, int n, int** cost, int** dp) {
    if (mask == (1 << n) - 1) {
        return cost[pos][0];
    }
    
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }
    
    int ans = INT_MAX;
    
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = cost[pos][city] + tsp(mask | (1 << city), city, n, cost, dp);
            ans = MIN(ans, newAns);
        }
    }
    
    return dp[mask][pos] = ans;
}

int total_cost(int** cost, int n) {
    int num_masks = 1 << n;
    int** dp = (int**)malloc(num_masks * sizeof(int*));
    for (int i = 0; i < num_masks; i++) {
        dp[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    
    int result = tsp(1, 0, n, cost, dp);
    
    for (int i = 0; i < num_masks; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int** createCostMatrix(int n, int raw[]) {
    int** cost = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        cost[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            cost[i][j] = raw[i * n + j];
        }
    }
    return cost;
}

void freeCostMatrix(int** cost, int n) {
    for (int i = 0; i < n; i++) free(cost[i]);
    free(cost);
}

int main() {
    int n = 4;
    int raw_costs[] = {
        0, 10, 15, 20,
        10, 0, 35, 25,
        15, 35, 0, 30,
        20, 25, 30, 0
    };
    
    int** costMatrix = createCostMatrix(n, raw_costs);
    
    printf("Executing TSP with DP + Bitmasking...\n\n");
    
    int min_cost = total_cost(costMatrix, n);
    
    printf("Minimum Cost for the Tour: %d\n", min_cost);
    printf("Expected Output:           80\n");
    
    freeCostMatrix(costMatrix, n);

    return 0;
}