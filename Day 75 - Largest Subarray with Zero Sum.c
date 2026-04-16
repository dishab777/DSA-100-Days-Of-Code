#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 5002

typedef struct HashNode {
    int key;     
    int value;   
    struct HashNode* next;
} HashNode;
HashNode* hashTable[HASH_SIZE] = {NULL};
int hash(int key) {
    int h = key % HASH_SIZE;
    return h < 0 ? h + HASH_SIZE : h;
}
void insert(int key, int value) {
    int h = hash(key);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[h];
    hashTable[h] = newNode;
}
int search(int key) {
    int h = hash(key);
    HashNode* curr = hashTable[h];
    
    while (curr != NULL) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }
    return -1;
}
void freeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* curr = hashTable[i];
        while (curr != NULL) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

int maxLenSubarray(int arr[], int n) {
    int max_len = 0;
    int current_sum = 0;
    
    for (int i = 0; i < n; i++) {
        current_sum += arr[i];
        
        if (arr[i] == 0 && max_len == 0) {
            max_len = 1;
        }
        
        if (current_sum == 0) {
            max_len = i + 1;
        }
        
        int prev_index = search(current_sum);
        if (prev_index != -1) {
    
            int current_len = i - prev_index;
            if (current_len > max_len) {
                max_len = current_len;
            }
        } 
        else 
        {
            insert(current_sum, i);
        }
    }
    
    return max_len;
}

int main() {
    int arr[] = {15, -2, 2, -8, 1, 7, 10, 23};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Evaluating array for longest 0-sum subarray...\n");
    
    int result = maxLenSubarray(arr, n);
    
    printf("Result: %d\n", result);
    
    freeHashTable();
    
    return 0;
}