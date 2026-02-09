#include <stdio.h>
#include <string.h>

int main() {
    char str[1001];
    if (scanf("%s", str) != 1) return 0;

    int len = strlen(str);
    int start = 0;
    int end = len - 1;
    char temp;

    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    printf("%s\n", str);

    return 0;
}