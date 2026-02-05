#include <stdio.h>
#include <limits.h>

int maxProfit(int* prices, int pricesSize) {
    int minPrice = INT_MAX;
    int maxProfit = 0;

    for (int i = 0; i < pricesSize; i++) {
        if (prices[i] < minPrice)
            minPrice = prices[i];
        if (prices[i] - minPrice > maxProfit)
            maxProfit = prices[i] - minPrice;
    }

    return maxProfit;
}

int main() {
    int prices[] = {7, 1, 5, 3, 6, 4};
    int n = sizeof(prices) / sizeof(prices[0]);

    int profit = maxProfit(prices, n);
    printf("Maximum Profit: %d\n", profit);

    return 0;
}