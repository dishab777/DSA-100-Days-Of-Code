#include <stdio.h>

int mySqrt(int x) {
    if (x == 0 || x == 1) {
        return x;
    }
    
    int left = 1;
    int right = x / 2; 
    int ans = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        long long square = (long long)mid * mid;
        
        if (square == x) {
            return mid;
        }
        
        if (square < x) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return ans;
}

int main() {
    int x1 = 4;
    printf("Input: %d\n", x1);
    printf("Square Root: %d\n", mySqrt(x1));
    printf("Expected:    2\n\n");
    
    int x2 = 8;
    printf("Input: %d\n", x2);
    printf("Square Root: %d\n", mySqrt(x2));
    printf("Expected:    2\n\n");
    
    int x3 = 2147395600; 
    printf("Input: %d\n", x3);
    printf("Square Root: %d\n", mySqrt(x3));
    printf("Expected:    46339\n");
    
    return 0;
}