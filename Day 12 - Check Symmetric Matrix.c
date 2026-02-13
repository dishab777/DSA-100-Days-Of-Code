#include <stdio.h>

int main()
{
    int m, n;
    int isSymmetric = 1;
    int matrix[100][100];

    if (scanf("%d %d", &m, &n) != 2)
        return 1;

    if (m != n)
    {
        printf("Not Symmetric\n");
        return 0;
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] != matrix[j][i])
            {
                isSymmetric = 0;
                break;
            }
        }
        if (!isSymmetric)
        {
            break;
        }
    }
    if (isSymmetric)
    {
        printf("Symmetric\n");
    }
    else
    {
        printf("Not Symmetric\n");
    }

    return 0;
}