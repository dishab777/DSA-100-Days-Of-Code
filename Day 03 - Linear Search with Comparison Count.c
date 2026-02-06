#include<stdio.h>
int main()
{
    int n, i, c=0, k, a[100];
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    printf("Enter the elements of the array: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    printf("Enter the element to be searched: ");
    scanf("%d", &k);

    for(i = 0; i < n; i++)
    {
        c++; // Increment comparison count
        if(a[i] == k)
        {
            printf("Element found at index %d\n", i);
            printf("Number of comparisons: %d\n", c);
            return 0;
        }
    }

    printf("Element not found in the array.\n");
    printf("Number of comparisons: %d\n", c);
    return 0;
}