#include <stdio.h>

long long calculateHours(int* piles, int pilesSize, int speed) {
    long long totalHours = 0; 
    for (int i = 0; i < pilesSize; i++) {
        totalHours += (piles[i] + speed - 1) / speed;
    }
    return totalHours;
}

int minEatingSpeed(int* piles, int pilesSize, int h) {
    int left = 1;
    int right = 0;
    
    for (int i = 0; i < pilesSize; i++) {
        if (piles[i] > right) {
            right = piles[i];
        }
    }
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (calculateHours(piles, pilesSize, mid) <= h) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

int main() {
    int piles1[] = {3, 6, 7, 11};
    int h1 = 8;
    int size1 = sizeof(piles1) / sizeof(piles1[0]);
    printf("Piles: [3, 6, 7, 11] | Guards return in: 8 hours\n");
    printf("Minimum Speed: %d\n", minEatingSpeed(piles1, size1, h1));
    printf("Expected:      4\n\n");
    
    int piles2[] = {30, 11, 23, 4, 20};
    int h2 = 5;
    int size2 = sizeof(piles2) / sizeof(piles2[0]);
    printf("Piles: [30, 11, 23, 4, 20] | Guards return in: 5 hours\n");
    printf("Minimum Speed: %d\n", minEatingSpeed(piles2, size2, h2));
    printf("Expected:      30\n\n");
    
    int piles3[] = {30, 11, 23, 4, 20};
    int h3 = 6;
    int size3 = sizeof(piles3) / sizeof(piles3[0]);
    printf("Piles: [30, 11, 23, 4, 20] | Guards return in: 6 hours\n");
    printf("Minimum Speed: %d\n", minEatingSpeed(piles3, size3, h3));
    printf("Expected:      23\n");
    
    return 0;
}