//#include <cstring>
#ifdef TEST
#include <stdio.h>
#include <stdint.h>
#include "circ_buf.h"

#define BUF_SIZE 256
uint8_t storage[BUF_SIZE];

typedef int (*arith_fun)(int,int);

int add(int a, int b) {
  return a + b;
}

int sub(int a, int b){return a-b;}

arith_fun arith_f[]={add, sub};

typedef struct pair {
  uint32_t addr; 
  uint32_t data; 
} pair;

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
#include <string.h>
#include "linked_list.h"

typedef struct Pair {
  uint32_t addr;
  uint32_t data;
} Pair;

typedef struct Triple {
  uint32_t addr;
  uint32_t data;
  uint32_t data1;
} Triple;

// Print logic for the pair struct
void printPair(void *p) {
  Pair *pPair = (Pair*)p;
  //Pair *pp = p;
  printf("{addr: 0x%X, data: 0x%x}", pPair->addr, pPair->data);
}

// Comparison logic (find/remove by address)
int comparePairAddr(void *a, void *b) {
  return ((Pair*)a)->addr - ((Pair*)b)->addr;
}

int addInt(int a, int b){
  int temp;
  temp =  a+b;
  return temp;
}

int main() {

  //int a = 10;
  //int *pN = &a;
  //int **ppN = &pN;
  //printf("*ppN: %p\n", *ppN);
  //printf("**ppN: %d\n", **ppN);

#ifdef TEST
  printf("sizeof(Node*) : %lu\n", sizeof(Node));
  {
    
    char cArr[16] = "He";
    char *pC=cArr;
    printf("strlen(cArr): %lu\n", strlen(cArr));
    printf("%c\n", *pC);
    printf("&pC: %p\n", &pC);
    printf("pC: %p\n", pC); //"H"
    pC++;
    printf("%c\n", *pC);
    printf("&pC: %p\n", &pC);
    printf("pC: %p\n", pC); //"e"

    printf("sizeof(uint32_t): %ld\n", sizeof(uint32_t));

  }
  {
    
    uint32_t nArr[] = {1,2,3};
    uint32_t *pN = nArr;

    printf("%d\n", *pN);
    printf("&pN: %p\n", &pN);
    printf("pN: %p\n", pN); //"H"
    pN++;
    printf("%d\n", *pN);
    printf("&pN: %p\n", &pN);
    printf("pN: %p\n", pN); //"H"
    pN++;
    printf("%d\n", *pN);
    printf("&pN: %p\n", &pN);
    printf("pN: %p\n", pN); //"H"
  }
  {
    
    Pair pairArr[2] ={{1,2},
		      {3,4}};
    Pair *pPair = pairArr;

    printf("%d\n", pPair->addr);
    printf("%d\n", pPair->data);
    printf("&pPair: %p\n", &pPair);
    printf("pPair: %p\n", pPair);
    pPair++;
    printf("%d\n", pPair->addr);
    printf("%d\n", pPair->data);
    printf("&pPair: %p\n", &pPair);
    printf("pPair: %p\n", pPair);
    //pPair++;
    //printf("%d\n", pPair->addr);
    //printf("&pPair: %p\n", &pPair);
    //printf("pPair: %p\n", pPair); //"H"
 

    //printf("%ls\n", pN);
    //printf("%p\n", &pN);
    //pN++;
    //printf("%ls\n", pN);
    //printf("%p\n", &pN);


    //for(int i=0; i<strlen(cArr); i++)
    //  printf("%c", *pC++);

  }
#endif
  // 1. Create and Append
  Pair p1 = {0xb1, 0xb2};
  Pair p2 = {0xb3, 0xa4};

  Triple t1 = {0xb1, 0xb2, 1};
  Triple t2 = {0xb3, 0xa4, 3};

  Node *List = NULL;
  appendNode(&List, &t1, sizeof(Triple));
  appendNode(&List, &t2, sizeof(Triple));

  //Pair p3;
  //memcpy(&p3, &p2, sizeof(Pair));
  //printf("p2.addr: %d\n", p2.addr);
  //printf("p3.addr: %d\n", p3.addr);

  Node* list = NULL;
  appendNode(&list, &p1, sizeof(Pair));
  appendNode(&list, &p2, sizeof(Pair));

  // 2. Dump
  printf("Initial List: ");
  dumpNode(list, printPair);

  // 3. Find
  Pair search = {0x1000, 0};
  Node* found = findNode(list, &search, comparePairAddr);
  if (found) printf("Found Addr 0x1000 with Data: 0x%X\n", ((Pair*)found->data)->data);

  // 4. Remove
  removeNode(&list, &search, comparePairAddr);
  printf("After Removal: ");
  dumpNode(list, printPair);

  freeList(list);
  return 0;
}
#endif
