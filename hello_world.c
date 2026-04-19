#ifdef TEST
#include <stdio.h>
#include <stdint.h>
#include "circ_buf.h"

#define BUF_SIZE 256
uint8_t storage[BUF_SIZE];

typedef int (*arith_fun)(int,int);

int add(int a, int b){return a+b;}
int sub(int a, int b){return a-b;}

arith_fun arith_f[]={add, sub};

typedef struct pair {
  uint32_t addr; 
  uint32_t data; 
} pair;

typedef struct llist {

}llist_t;


int main(){

  circbuf_t cb;
  circbuf_init(&cb, storage, BUF_SIZE);
  uint8_t tx[] = {1, 2, 3, 4, 5};
  circbuf_put(&cb, tx, sizeof(tx));
  uint8_t rx[10];
  uint32_t n = circbuf_get(&cb, rx, sizeof(rx));
  
  for(int i=0; i<4; i++){
    //printf("%d : Hello World\n", i);
    //printf("%d + %d = %d", i,i, add(i,i));
    printf("%d + %d = %u\n", i,i, arith_f[i%2](i,i));
  }
  uint32_t nAge = 32;
  uint32_t nHeight = 15;
  sub(nAge, nHeight);
  add(nAge, nHeight);

  return 0;
}
#else

#include <stdio.h>
#include "linked_list.h"

typedef struct pair {
  uint32_t addr;
  uint32_t data;
} pair;

// Print logic for the pair struct
void printPair(void *p) {
  pair *pp = (pair*)p;
  printf("{addr: 0x%X, data: 0x%X}", pp->addr, pp->data);
}

// Comparison logic (find/remove by address)
int comparePairAddr(void *a, void *b) {
  return ((pair*)a)->addr - ((pair*)b)->addr;
}

int main() {
  Node* list = NULL;

  // 1. Create and Append
  pair p1 = {0x1000, 0xAAAA};
  pair p2 = {0x2000, 0xBBBB};
  appendNode(&list, &p1, sizeof(pair));
  appendNode(&list, &p2, sizeof(pair));

  // 2. Dump
  printf("Initial List: ");
  dumpNode(list, printPair);

  // 3. Find
  pair search = {0x1000, 0};
  Node* found = findNode(list, &search, comparePairAddr);
  if (found) printf("Found Addr 0x1000 with Data: 0x%X\n", ((pair*)found->data)->data);

  // 4. Remove
  removeNode(&list, &search, comparePairAddr);
  printf("After Removal: ");
  dumpNode(list, printPair);

  freeList(list);
  return 0;
}
#endif
