#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} MyLinkedList;

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* obj = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    obj->head = NULL;
    obj->size = 0;
    return obj;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
    if (index < 0 || index >= obj->size) {
        return -1;
    }
    
    Node* current = obj->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->val;
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = obj->head;
    obj->head = newNode;
    obj->size++;
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = NULL;
    
    if (obj->head == NULL) {
        obj->head = newNode;
    } else {
        Node* current = obj->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    obj->size++;
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    if (index > obj->size) return;
    
    if (index <= 0) {
        myLinkedListAddAtHead(obj, val);
        return;
    }
    
    if (index == obj->size) {
        myLinkedListAddAtTail(obj, val);
        return;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    
    Node* current = obj->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    obj->size++;
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    if (index < 0 || index >= obj->size) return;
    
    Node* temp;
    if (index == 0) {
        temp = obj->head;
        obj->head = obj->head->next;
    } else {
        Node* current = obj->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
    }
    
    free(temp);
    obj->size--;
}

void myLinkedListFree(MyLinkedList* obj) {
    Node* current = obj->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(obj);
}

// Helper function to print the current state of the list
void printList(MyLinkedList* obj) {
    Node* current = obj->head;
    printf("Current List: ");
    while (current != NULL) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL (Size: %d)\n", obj->size);
}

int main() {
    // 1. Initialize the linked list
    MyLinkedList* obj = myLinkedListCreate();
    printf("Initialized Linked List.\n");

    // 2. Add 1 at head
    myLinkedListAddAtHead(obj, 1);
    printf("\nAdded 1 at head.\n");
    printList(obj);

    // 3. Add 3 at tail
    myLinkedListAddAtTail(obj, 3);
    printf("\nAdded 3 at tail.\n");
    printList(obj);

    // 4. Add 2 at index 1
    myLinkedListAddAtIndex(obj, 1, 2);
    printf("\nAdded 2 at index 1.\n");
    printList(obj); // List should be 1 -> 2 -> 3

    // 5. Get value at index 1
    int val1 = myLinkedListGet(obj, 1);
    printf("\nValue at index 1: %d (Expected: 2)\n", val1);

    // 6. Delete node at index 1
    myLinkedListDeleteAtIndex(obj, 1);
    printf("\nDeleted node at index 1.\n");
    printList(obj); // List should be 1 -> 3

    // 7. Get value at index 1
    int val2 = myLinkedListGet(obj, 1);
    printf("\nValue at index 1: %d (Expected: 3)\n", val2);

    // Clean up memory
    myLinkedListFree(obj);
    printf("\nFreed the Linked List memory.\n");

    return 0;
}