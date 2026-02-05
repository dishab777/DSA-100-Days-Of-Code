#include <stdio.h>
#include <stdlib.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    *returnSize = 2;                              // Tell the system we are returning 2 numbers
    int *result = (int *)malloc(2 * sizeof(int)); // Create the result array

    // Outer loop: Pick the first number
    for (int i = 0; i < numsSize; i++)
    {
        // Inner loop: Check all subsequent numbers
        for (int j = i + 1; j < numsSize; j++)
        {

            if (nums[i] + nums[j] == target)
            {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }

    return 0;
}