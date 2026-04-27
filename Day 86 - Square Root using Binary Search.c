#include <stdio.h>

int integerSquareRoot(long long n) {
    if (n == 0 || n == 1) {
        return n;
    }
    
    long long left = 1;
    
    long long right = n / 2; 
    long long ans = 0;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        long long square = mid * mid;
        
        if (square == n) {
            return mid;
        }
        
        if (square < n) {
            ans = mid;
            left = mid + 1;
        } 

        else {
            right = mid - 1;
        }
    }
    
    return ans;
}

int main() {
    long long n;
    
    if (scanf("%lld", &n) != 1) return 0;
    
    int result = integerSquareRoot(n);
    printf("%d\n", result);
    
    return 0;
}