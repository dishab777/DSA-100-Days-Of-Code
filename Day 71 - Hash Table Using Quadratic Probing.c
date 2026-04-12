#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// --- Data Structures ---

typedef struct {
    int key;
    bool isOccupied;
} HashEntry;

typedef struct {
    HashEntry* entries;
    int size;
} HashTable;

// --- Hash Table Functions ---

// Initialize the hash table
HashTable* createTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->entries = (HashEntry*)malloc(size * sizeof(HashEntry));
    
    for (int i = 0; i < size; i++) {
        table->entries[i].isOccupied = false;
    }
    return table;
}

// Base Hash Function: h(k)
int hash(int key, int size) {
    // Handle potential negative keys safely
    int h = key % size;
    return h < 0 ? h + size : h;
}

// Quadratic Probing Insert
void insert(HashTable* table, int key) {
    int idx = hash(key, table->size);
    int m = table->size;
    
    // Probing loop: h(k, i) = (h(k) + i*i) % m
    for (int i = 0; i < m; i++) {
        int pos = (idx + i * i) % m;
        
        // If we find an empty slot, claim it!
        if (!table->entries[pos].isOccupied) {
            table->entries[pos].key = key;
            table->entries[pos].isOccupied = true;
            return;
        }
        
        // If the key already exists, do nothing (prevent duplicates)
        if (table->entries[pos].key == key) {
            return;
        }
    }
    // Note: If the loop finishes, the table is too full or probing failed 
    // (Quadratic probing works best when 'm' is a prime number and table is < 50% full).
}

// Quadratic Probing Search
bool search(HashTable* table, int key) {
    int idx = hash(key, table->size);
    int m = table->size;
    
    for (int i = 0; i < m; i++) {
        int pos = (idx + i * i) % m;
        
        // If we hit an empty slot before finding the key, it doesn't exist
        if (!table->entries[pos].isOccupied) {
            return false;
        }
        
        // If we find the exact key, success!
        if (table->entries[pos].key == key) {
            return true;
        }
    }
    
    return false;
}

// Clean up memory
void freeTable(HashTable* table) {
    free(table->entries);
    free(table);
}

// --- Main Execution ---

int main() {
    int m, q;
    
    // Read table size and number of operations
    if (scanf("%d", &m) != 1) return 0;
    if (scanf("%d", &q) != 1) return 0;
    
    HashTable* table = createTable(m);
    
    char operation[10];
    int key;
    
    // Process operations
    for (int i = 0; i < q; i++) {
        scanf("%s %d", operation, &key);
        
        if (strcmp(operation, "INSERT") == 0) {
            insert(table, key);
        } else if (strcmp(operation, "SEARCH") == 0) {
            if (search(table, key)) {
                printf("FOUND\n");
            } else {
                printf("NOT FOUND\n");
            }
        }
    }
    
    freeTable(table);
    return 0;
}