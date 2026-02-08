#include <stdio.h>
#include <stdbool.h>

bool isPowerOfTwo(int n) {
    if (n <= 0) return false;
    return (n & (n - 1)) == 0;
}

int main() 
{
    int n;
    if (scanf("%d", &n) != 1) return 0;

    if (isPowerOfTwo(n)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}