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

// Function to delete the first occurrence of a key
struct Node* deleteFirstOccurrence(struct Node* head, int key) {
    // Case 1: Empty list
    if (head == NULL) {
        return NULL;
    }

    // Case 2: The key is at the head node
    if (head->data == key) {
        struct Node* temp = head;
        head = head->next; // Move head to the next node
        free(temp);        // Free the old head
        return head;
    }

    // Case 3: The key is somewhere else in the list
    struct Node* current = head;
    struct Node* prev = NULL;

    // Traverse the list to find the key
    while (current != NULL && current->data != key) {
        prev = current;
        current = current->next;
    }

    // If the key was not found in the list
    if (current == NULL) {
        return head;
    }

    // Unlink the node from the linked list and free it
    prev->next = current->next;
    free(current);

    return head;
}

int main() {
    int n;
    
    // Read the size of the list
    if (scanf("%d", &n) != 1) return 1;

    // Handle 0 or negative size
    if (n <= 0) return 0;

    struct Node* head = NULL;
    struct Node* tail = NULL;

    // Build the linked list
    for (int i = 0; i < n; i++) {
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

    int key;
    // Read the key to delete
    if (scanf("%d", &key) != 1) return 1;

    // Delete the first occurrence of the key
    head = deleteFirstOccurrence(head, key);

    // Print the modified linked list
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" ");
        }
        temp = temp->next;
    }
    printf("\n");

    // Free the remaining dynamically allocated memory
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}