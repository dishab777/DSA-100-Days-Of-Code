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

int main() {
    int n;
    
    // Read the number of elements
    if (scanf("%d", &n) != 1) return 1;

    // Handle the case for 0 elements
    if (n <= 0) {
        return 0;
    }

    struct Node* head = NULL;
    struct Node* tail = NULL;

    // Read the elements and build the linked list
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        
        struct Node* newNode = createNode(val);
        
        // If the list is empty, make the new node the head
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            // Otherwise, append to the end of the list
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Traverse the linked list and print the elements
    struct Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");

    // Free the allocated memory to prevent memory leaks
    current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}