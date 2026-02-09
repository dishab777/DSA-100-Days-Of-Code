#include <stdio.h>

void reverseString(char* s, int sSize) {
    int left = 0;
    int right = sSize - 1;
    char temp;

    while (left < right) {
        temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
}

int main() {
    char s[] = {'h', 'e', 'l', 'l', 'o'};
    int size = 5;

    reverseString(s, size);

    for (int i = 0; i < size; i++) {
        printf("%c", s[i]);
    }
    printf("\n");

    return 0;
}