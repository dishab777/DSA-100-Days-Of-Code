#include <stdio.h>
void findFirstNonRepeating(char* s) 
{
    int freq[26] = {0};
    
    for (int i = 0; s[i] != '\0'; i++) 
    {
        int index = s[i] - 'a';
        freq[index]++;
    }
    
    for (int i = 0; s[i] != '\0'; i++) 
    {
        int index = s[i] - 'a';
        if (freq[index] == 1) 
        {
            printf("%c\n", s[i]);
            return;
        }
    }
    
    printf("$\n");
}

int main() 
{
    char s[100005]; 
    
    if (scanf("%100004s", s) == 1) 
    {
        findFirstNonRepeating(s);
    }
    
    return 0;
}