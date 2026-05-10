#include <stdio.h>
#include <stdlib.h>

struct Node {
    double data;
    struct Node* next;
};

void insertSorted(struct Node** head, double val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;

    if (*head == NULL || (*head)->data >= val) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* curr = *head;
        while (curr->next != NULL && curr->next->data < val) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
}

void bucketSort(double* arr, int n) {
    if (n <= 0) return;

    struct Node** buckets = (struct Node**)calloc(n, sizeof(struct Node*));

    for (int i = 0; i < n; i++) {
        int bucketIdx = n * arr[i];
        if (bucketIdx >= n) {
            bucketIdx = n - 1;
        }
        insertSorted(&buckets[bucketIdx], arr[i]);
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        struct Node* curr = buckets[i];
        while (curr != NULL) {
            arr[index++] = curr->data;
            struct Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    free(buckets);
}

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) return 0;
    
    double* arr = (double*)malloc(n * sizeof(double));
    if (arr == NULL) return 1;
    
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }
    
    bucketSort(arr, n);
    
    for (int i = 0; i < n; i++) {
        printf("%.4f", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    free(arr);
    return 0;
}