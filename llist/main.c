#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Pair {
  uint32_t addr;
  uint32_t data;
} Pair;

typedef struct Node {
  void *data;
  struct Node *next;

} Node;

Node *createNode(void *data, uint32_t datasize) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = malloc(datasize);
  memcpy(newNode->data, data, datasize);
  newNode->next = NULL;
  return newNode;
}

void appendNode(Node **head, void *data, uint32_t datasize) {
  Node *newNode = createNode(data, datasize);
  if (*head == NULL) {
    *head = newNode;
    return;
  }
  Node *temp = *head;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = newNode;
}

void printPair(Pair pair) {
  printf("addr:0x%x data:0x%x \n", pair.addr, pair.data);
}

void printList(Node *list) {

  while (list != NULL) {
    printPair(*(Pair *)list->data);
    list = list->next;
  }
  printPair(*(Pair *)list->data);
  return;
}

int main() {
  Pair p1 = {0xa0, 0xb0};
  Pair p2 = {0xa1, 0xb1};
  Pair p3 = {0xa2, 0xb2};
  printPair(p1);
  printPair(p2);
  printPair(p3);

  Node *list = createNode(&p1, sizeof(Pair));
  appendNode(&list, &p2, sizeof(Pair));
  appendNode(&list, &p3, sizeof(Pair));
  printf("\n");
  printList(list);
}
