#include<stdio.h>

int power(int a, int b)
{
    if (b == 0)
        return 1;
    else
        return a * power(a, b - 1);
}

int main()
{
    int a, b;
    printf("Enter the base and exponent: ");
    scanf("%d %d", &a, &b);
    printf("%d raised to the power of %d is %d\n", a, b, power(a, b));
    return 0;
}