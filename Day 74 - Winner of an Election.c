#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareStrings(const void* a, const void* b) 
{
    return strcmp((const char*)a, (const char*)b);
}

void findWinner(int n, char (*votes)[55]) 
{
    qsort(votes, n, 55 * sizeof(char), compareStrings);

    int max_votes = 0;
    char winner[55] = "";

    int current_count = 0;
    char current_candidate[55] = "";

    for (int i = 0; i < n; i++) 
    {
        if (i == 0 || strcmp(votes[i], current_candidate) != 0) 
        {
            strcpy(current_candidate, votes[i]);
            current_count = 1;
        }
        else 
        {
            current_count++;
        }
        if (current_count > max_votes) 
        {
            max_votes = current_count;
            strcpy(winner, current_candidate);
        }
    }
    printf("%s %d\n", winner, max_votes);
}

int main() 
{
    int n;
    
    if (scanf("%d", &n) != 1) 
    return 0;

    char (*votes)[55] = malloc(n * sizeof(*votes));
    if (votes == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) 
    {
        scanf("%54s", votes[i]);
    }

    findWinner(n, votes);

    free(votes);

    return 0;
}