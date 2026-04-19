#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

// stack && heap

Node* createNode(void *data, size_t dataSize) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) return NULL;

    newNode->data = malloc(dataSize);
    if (!newNode->data) {
        free(newNode);
        return NULL;
    }
    memcpy(newNode->data, data, dataSize);
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, void *data, size_t dataSize) {
    Node* newNode = createNode(data, dataSize);
    if (!newNode) return;

    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
}

Node* findNode(Node* head, void *target, int (*compareFunc)(void *, void *)) {
    Node* current = head;
    while (current != NULL) {
        if (compareFunc(current->data, target) == 0) return current;
        current = current->next;
    }
    return NULL;
}

bool removeNode(Node** head, void *target, int (*compareFunc)(void *, void *)) {
    Node *current = *head, *prev = NULL;
    while (current != NULL) {
        if (compareFunc(current->data, target) == 0) {
            if (prev == NULL) *head = current->next;
            else prev->next = current->next;
            free(current->data);
            free(current);
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

void dumpNode(Node* head, void (*printFunc)(void *)) {
    Node* current = head;
    printf("[ ");
    while (current != NULL) {
        printFunc(current->data);
        if (current->next) printf(" -> ");
        current = current->next;
    }
    printf(" ]\n");
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}
