#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* createNode(int val)
{
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

struct ListNode* reverse(struct ListNode* head)
{
    struct ListNode* prev = NULL;
    while(head)
    {
        struct ListNode* nextNode = head->next;
        head->next = prev;
        prev = head;
        head = nextNode;
    }
    return prev;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
    l1 = reverse(l1);
    l2 = reverse(l2);
    
    int carry = 0;
    struct ListNode* head = NULL;
    
    while(l1 || l2 || carry)
    {
        int sum = carry;
        
        if(l1)
        {
            sum += l1->val;
            l1 = l1->next;
        }
        
        if(l2)
        {
            sum += l2->val;
            l2 = l2->next;
        }
        
        struct ListNode* newNode = createNode(sum % 10);
        newNode->next = head;
        head = newNode;
        
        carry = sum / 10;
    }
    
    return head;
}

void insert(struct ListNode** head, int val)
{
    if(*head == NULL)
    {
        *head = createNode(val);
        return;
    }
    
    struct ListNode* temp = *head;
    while(temp->next)
        temp = temp->next;
        
    temp->next = createNode(val);
}

void printList(struct ListNode* head)
{
    while(head)
    {
        printf("%d", head->val);
        if(head->next)
            printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

int main()
{
    int n1, n2, x;
    struct ListNode* l1 = NULL;
    struct ListNode* l2 = NULL;
    
    scanf("%d", &n1);
    for(int i = 0; i < n1; i++)
    {
        scanf("%d", &x);
        insert(&l1, x);
    }
    
    scanf("%d", &n2);
    for(int i = 0; i < n2; i++)
    {
        scanf("%d", &x);
        insert(&l2, x);
    }
    
    struct ListNode* result = addTwoNumbers(l1, l2);
    printList(result);
    
    return 0;
}
