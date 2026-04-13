#include <stdio.h>
#include <stdbool.h>

void findFirstRepeated(char* s) {
    bool seen[26] = {false};
    
    for (int i = 0; s[i] != '\0'; i++) {
        int index = s[i] - 'a';
        
        if (seen[index]) {
            printf("%c\n", s[i]);
            return;
        }
        
        seen[index] = true;
    }
    printf("-1\n");
}

int main() 
{
    char s[100005]; 
    if (scanf("%100004s", s) == 1) 
    {
        findFirstRepeated(s);
    }
    return 0;
}