#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* insertionSortList(struct ListNode* head) {
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode* curr = head;
    
    while (curr != NULL) {
        struct ListNode* prev = &dummy;
        
        while (prev->next != NULL && prev->next->val < curr->val) {
            prev = prev->next;
        }
        
        struct ListNode* next_node = curr->next;
        curr->next = prev->next;
        prev->next = curr;
        curr = next_node;
    }
    
    return dummy.next;
}

struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

void printList(struct ListNode* head) {
    printf("[");
    while (head != NULL) {
        printf("%d", head->val);
        if (head->next != NULL) printf(", ");
        head = head->next;
    }
    printf("]\n");
}

void freeList(struct ListNode* head) {
    struct ListNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct ListNode* head1 = createNode(4);
    head1->next = createNode(2);
    head1->next->next = createNode(1);
    head1->next->next->next = createNode(3);
    
    printf("Original: ");
    printList(head1);
    
    struct ListNode* sorted1 = insertionSortList(head1);
    
    printf("Sorted:   ");
    printList(sorted1);
    printf("Expected: [1, 2, 3, 4]\n\n");
    
    freeList(sorted1);
    
    struct ListNode* head2 = createNode(-1);
    head2->next = createNode(5);
    head2->next->next = createNode(3);
    head2->next->next->next = createNode(4);
    head2->next->next->next->next = createNode(0);
    
    printf("Original: ");
    printList(head2);
    
    struct ListNode* sorted2 = insertionSortList(head2);
    
    printf("Sorted:   ");
    printList(sorted2);
    printf("Expected: [-1, 0, 3, 4, 5]\n");
    
    freeList(sorted2);
    
    return 0;
}