#ifndef LINKED_LIST_H
#define LINKED_LIST_H

//#include <cmath>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct Node {
    void        *data;
    struct Node *next;
} Node;

// Function declarations
Node* createNode(void *data, size_t dataSize);
void appendNode(Node** head, void *data, size_t dataSize);
Node* findNode(Node* head, void *target, int (*compareFunc)(void *, void *));
bool removeNode(Node** head, void *target, int (*compareFunc)(void *, void *));
void dumpNode(Node* head, void (*printFunc)(void *));
void freeList(Node* head);

#endif
