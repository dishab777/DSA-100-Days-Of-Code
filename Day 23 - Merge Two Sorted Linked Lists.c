#include <stdio.h>
#include <stdlib.h>

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

// Function to build a linked list from standard input
struct Node* buildList(int size) {
    if (size <= 0) return NULL;

    struct Node* head = NULL;
    struct Node* tail = NULL;

    for (int i = 0; i < size; i++) {
        int val;
        scanf("%d", &val);
        struct Node* newNode = createNode(val);

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// Function to merge two sorted linked lists
struct Node* mergeSortedLists(struct Node* l1, struct Node* l2) {
    // Create a dummy node to simplify edge cases (like empty lists)
    struct Node dummy;
    struct Node* tail = &dummy;
    dummy.next = NULL;

    // Traverse both lists, appending the smaller value to the merged list
    while (l1 != NULL && l2 != NULL) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // If any elements remain in either list, append them
    if (l1 != NULL) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    return dummy.next;
}

int main() {
    int n, m;

    // Read the size of the first list
    if (scanf("%d", &n) != 1) return 1;
    struct Node* list1 = buildList(n);

    // Read the size of the second list
    if (scanf("%d", &m) != 1) return 1;
    struct Node* list2 = buildList(m);

    // Merge the two lists
    struct Node* mergedList = mergeSortedLists(list1, list2);

    // Print the merged list
    struct Node* current = mergedList;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");

    // Free the dynamically allocated memory
    current = mergedList;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}