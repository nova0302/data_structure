
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

Node* createNode(void *data, size_t dataSize) {
  Node* newNode = (Node*)malloc(sizeof(Node));
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
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = newNode;
}

void freeList(Node* head) {
  Node* temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp->data);
    free(temp);
  }
}

Node* findNode(Node* head, void *target, int (*compareFunc)(void *, void *)) {
  Node* current = head;
  while (current != NULL) {
    // compareFunc should return 0 if data matches
    if (compareFunc(current->data, target) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

bool removeNode(Node** head, void *target, int (*compareFunc)(void *, void *)) {
  Node *current = *head;
  Node *previous = NULL;

  while (current != NULL) {
    if (compareFunc(current->data, target) == 0) {
      if (previous == NULL) {
        // Node to remove is the head
        *head = current->next;
      } else {
        previous->next = current->next;
      }
            
      free(current->data);
      free(current);
      return true; // Successfully removed
    }
    previous = current;
    current = current->next;
  }
  return false; // Not found
}

void dumpNode(Node* head, void (*printFunc)(void *)) {
    Node* current = head;
    printf("[ ");
    while (current != NULL) {
        printFunc(current->data); // Call the user's print logic
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf(" ]\n");
}
#ifdef USAGE
#include <stdio.h>

// User-defined comparison for integers
int compareInts(void *a, void *b) {
  return (*(int*)a - *(int*)b);
}

int main() {
  Node* list = NULL;
  int x = 10, y = 20;

  appendNode(&list, &x, sizeof(int));
  appendNode(&list, &y, sizeof(int));

  // Find 20
  int searchVal = 20;
  Node* found = findNode(list, &searchVal, compareInts);
  if (found) printf("Found: %d\n", *(int*)found->data);

  // Remove 10
  int removeVal = 10;
  if (removeNode(&list, &removeVal, compareInts)) {
    printf("Removed 10 successfully\n");
  }

  freeList(list);
  return 0;
}
#endif
