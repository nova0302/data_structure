
#ifndef LLIST_H
#define LLIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// Function declarations
Node* createNode(void *data, size_t dataSize);
void appendNode(Node** head, void *data, size_t dataSize);
void freeList(Node* head);

// New functions
bool removeNode(Node** head, void *target, int (*compareFunc)(void *, void *));
Node* findNode(Node* head, void *target, int (*compareFunc)(void *, void *));

#endif /* LLIST_H */
