#include <stdbool.h>
bool isToeplitzMatrix(int **matrix, int matrixSize, int *matrixColSize)
{
    int rows = matrixSize;
    int cols = matrixColSize[0];
    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j < cols; j++)
        {
            if (matrix[i][j] != matrix[i - 1][j - 1])
            {
                return false;
            }
        }
    }

    return true;
}