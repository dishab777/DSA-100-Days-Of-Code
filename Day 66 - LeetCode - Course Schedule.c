#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int dest;
    struct Node* next;
};

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    int* inDegree = (int*)calloc(numCourses, sizeof(int));
    struct Node** adjList = (struct Node**)calloc(numCourses, sizeof(struct Node*));

    for (int i = 0; i < prerequisitesSize; i++) {
        int course = prerequisites[i][0];
        int prereq = prerequisites[i][1];

        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->dest = course;
        newNode->next = adjList[prereq];
        adjList[prereq] = newNode;

        inDegree[course]++;
    }

    int* queue = (int*)malloc(numCourses * sizeof(int));
    int front = 0, rear = 0;

    for (int i = 0; i < numCourses; i++) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int completedCount = 0;

    while (front < rear) {
        int curr = queue[front++];
        completedCount++;

        struct Node* temp = adjList[curr];
        while (temp != NULL) {
            int dependentCourse = temp->dest;
            inDegree[dependentCourse]--;

            if (inDegree[dependentCourse] == 0) {
                queue[rear++] = dependentCourse;
            }
            temp = temp->next;
        }
    }

    for (int i = 0; i < numCourses; i++) {
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            struct Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(adjList);
    free(inDegree);
    free(queue);

    return completedCount == numCourses;
}

// --- Helper for creating 2D array ---
int** createPrereqs(int size, int raw[][2]) {
    if (size == 0) return NULL;
    int** prereqs = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        prereqs[i] = (int*)malloc(2 * sizeof(int));
        prereqs[i][0] = raw[i][0];
        prereqs[i][1] = raw[i][1];
    }
    return prereqs;
}

void freePrereqs(int** prereqs, int size) {
    for (int i = 0; i < size; i++) free(prereqs[i]);
    free(prereqs);
}

int main() {
    // --- Test Case 1: Valid Schedule ---
    // 2 courses. To take 1, you must finish 0. [1, 0]
    int num1 = 2;
    int size1 = 1;
    int raw1[][2] = {{1, 0}};
    int** pre1 = createPrereqs(size1, raw1);
    
    printf("Test Case 1:\n");
    if (canFinish(num1, pre1, size1, NULL)) {
        printf("Result: true (Expected: true)\n\n");
    } else {
        printf("Result: false (Expected: true)\n\n");
    }
    freePrereqs(pre1, size1);

    // --- Test Case 2: Impossible Schedule (Cycle) ---
    // 2 courses. To take 1 you must finish 0. To take 0 you must finish 1.
    // [1, 0] and [0, 1]
    int num2 = 2;
    int size2 = 2;
    int raw2[][2] = {{1, 0}, {0, 1}};
    int** pre2 = createPrereqs(size2, raw2);

    printf("Test Case 2:\n");
    if (canFinish(num2, pre2, size2, NULL)) {
        printf("Result: true (Expected: false)\n");
    } else {
        printf("Result: false (Expected: false)\n");
    }
    freePrereqs(pre2, size2);

    return 0;
}