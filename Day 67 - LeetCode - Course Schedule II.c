#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int dest;
    struct Node* next;
};

int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize) {
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

    int* result = (int*)malloc(numCourses * sizeof(int));
    int count = 0;

    while (front < rear) {
        int curr = queue[front++];
        result[count++] = curr;

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

    if (count == numCourses) {
        *returnSize = numCourses;
        return result;
    } else {
        *returnSize = 0;
        free(result);
        return NULL;
    }
}

// --- Helper Functions ---

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

void printResult(int* result, int size) {
    if (size == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d%s", result[i], i == size - 1 ? "" : ",");
    }
    printf("]\n");
}

int main() {
    // --- Test Case 1: Complex Valid Schedule ---
    // 4 courses. 
    // To take 1, finish 0. To take 2, finish 0. To take 3, finish 1 and 2.
    int num1 = 4;
    int size1 = 4;
    int raw1[][2] = {{1,0}, {2,0}, {3,1}, {3,2}};
    int** pre1 = createPrereqs(size1, raw1);
    
    int returnSize1;
    int* result1 = findOrder(num1, pre1, size1, NULL, &returnSize1);
    
    printf("Test Case 1 (Valid Schedule):\n");
    printf("Result:   ");
    printResult(result1, returnSize1);
    printf("Expected: [0,1,2,3] or [0,2,1,3]\n\n");
    
    freePrereqs(pre1, size1);
    free(result1);

    // --- Test Case 2: Impossible Schedule (Cycle) ---
    int num2 = 2;
    int size2 = 2;
    int raw2[][2] = {{1,0}, {0,1}};
    int** pre2 = createPrereqs(size2, raw2);

    int returnSize2;
    int* result2 = findOrder(num2, pre2, size2, NULL, &returnSize2);

    printf("Test Case 2 (Impossible Cycle):\n");
    printf("Result:   ");
    printResult(result2, returnSize2);
    printf("Expected: []\n");

    freePrereqs(pre2, size2);
    free(result2);

    return 0;
}