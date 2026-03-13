#include <stdio.h>

int leastInterval(char* tasks, int tasksSize, int n) {
    int freqs[26] = {0};
    int max_freq = 0;

    for (int i = 0; i < tasksSize; i++) {
        int index = tasks[i] - 'A';
        freqs[index]++;
        if (freqs[index] > max_freq) {
            max_freq = freqs[index];
        }
    }

    int max_count = 0;
    for (int i = 0; i < 26; i++) {
        if (freqs[i] == max_freq) {
            max_count++;
        }
    }

    int intervals = (max_freq - 1) * (n + 1) + max_count;

    return intervals > tasksSize ? intervals : tasksSize;
}

// Helper to print tasks array
void printTasks(char* tasks, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("\"%c\"", tasks[i]);
        if (i < size - 1) printf(",");
    }
    printf("]\n");
}

int main() {
    // Example 1
    char tasks1[] = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n1 = 2;
    int size1 = sizeof(tasks1) / sizeof(tasks1[0]);
    
    printf("Tasks: ");
    printTasks(tasks1, size1);
    printf("n = %d\n", n1);
    printf("Result: %d (Expected: 8)\n\n", leastInterval(tasks1, size1, n1));

    // Example 2
    char tasks2[] = {'A', 'C', 'A', 'B', 'D', 'B'};
    int n2 = 1;
    int size2 = sizeof(tasks2) / sizeof(tasks2[0]);
    
    printf("Tasks: ");
    printTasks(tasks2, size2);
    printf("n = %d\n", n2);
    printf("Result: %d (Expected: 6)\n\n", leastInterval(tasks2, size2, n2));

    // Example 3
    char tasks3[] = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n3 = 3;
    int size3 = sizeof(tasks3) / sizeof(tasks3[0]);
    
    printf("Tasks: ");
    printTasks(tasks3, size3);
    printf("n = %d\n", n3);
    printf("Result: %d (Expected: 10)\n", leastInterval(tasks3, size3, n3));

    return 0;
}