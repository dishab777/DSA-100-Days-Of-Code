#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new doubly linked list node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

int main() {
    int n;
    
    // Read the number of elements
    if (scanf("%d", &n) != 1) return 1;

    // Handle empty list case
    if (n <= 0) {
        return 0;
    }

    struct Node* head = NULL;
    struct Node* tail = NULL;

    // Build the doubly linked list
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        struct Node* newNode = createNode(val);
        
        // If the list is empty, make the new node the head and tail
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            // Append to the end of the list and update pointers
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Traverse the doubly linked list in forward order
    struct Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");

    // Free the dynamically allocated memory
    current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}