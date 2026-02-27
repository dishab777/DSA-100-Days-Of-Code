#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the structure for a linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to calculate the length of a linked list
int getLength(struct Node* head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

int main() {
    int n, m;

    // 1. Build the first linked list
    if (scanf("%d", &n) != 1) return 1;
    struct Node* head1 = NULL;
    struct Node* tail1 = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        struct Node* newNode = createNode(val);
        if (head1 == NULL) {
            head1 = newNode;
            tail1 = newNode;
        } else {
            tail1->next = newNode;
            tail1 = newNode;
        }
    }

    // 2. Build the second linked list
    if (scanf("%d", &m) != 1) return 1;
    struct Node* head2 = NULL;
    struct Node* tail2 = NULL;
    for (int i = 0; i < m; i++) {
        int val;
        scanf("%d", &val);
        struct Node* newNode = createNode(val);
        if (head2 == NULL) {
            head2 = newNode;
            tail2 = newNode;
        } else {
            tail2->next = newNode;
            tail2 = newNode;
        }
    }

    // 3. Calculate lengths of both lists
    int len1 = getLength(head1);
    int len2 = getLength(head2);

    struct Node* curr1 = head1;
    struct Node* curr2 = head2;

    // 4. Advance the pointer of the longer list by the difference in lengths
    if (len1 > len2) {
        int diff = len1 - len2;
        for (int i = 0; i < diff; i++) {
            curr1 = curr1->next;
        }
    } else if (len2 > len1) {
        int diff = len2 - len1;
        for (int i = 0; i < diff; i++) {
            curr2 = curr2->next;
        }
    }

    // 5. Traverse both lists simultaneously to find the intersection
    int intersectionFound = 0;
    int intersectionValue = -1;

    while (curr1 != NULL && curr2 != NULL) {
        // We compare the data values here to simulate the intersection
        // In a true shared-memory linked list, you would compare pointers: if (curr1 == curr2)
        if (curr1->data == curr2->data) {
            intersectionFound = 1;
            intersectionValue = curr1->data;
            break;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    // 6. Print the result
    if (intersectionFound) {
        printf("%d\n", intersectionValue);
    } else {
        printf("No Intersection\n");
    }

    // Clean up memory (Standard practice)
    struct Node* temp;
    while (head1 != NULL) {
        temp = head1;
        head1 = head1->next;
        free(temp);
    }
    while (head2 != NULL) {
        temp = head2;
        head2 = head2->next;
        free(temp);
    }

    return 0;
}