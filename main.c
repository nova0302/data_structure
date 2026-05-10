// #include <cstring>

#include "linked_list.h"
#include <stdio.h>
#include <string.h>

typedef struct Pair {
  uint32_t addr;
  uint32_t data;
} Pair;

typedef struct Tripple {
  uint32_t addr;
  uint32_t data;
  uint32_t data1;
} Tripple;

// Print logic for the pair struct
void printPair(void *p) {
  Pair *pPair = (Pair *)p;
  // Pair *pp = p;
  printf("{addr: 0x%X, data: 0x%x}", pPair->addr, pPair->data);
}

void printTripple(void *p) {
  Tripple *pTripple = (Tripple *)p;
  printf("{addr: 0x%X, data: 0x%x, data1: 0x%x}\n", pTripple->addr,
         pTripple->data, pTripple->data1);
}
// Comparison logic (find/remove by address)
int comparePairAddr(void *a, void *b) {
  return ((Pair *)a)->addr - ((Pair *)b)->addr;
}

int addInt(int a, int b) {
  int temp;
  temp = a + b;
  return temp;
}
typedef struct {
  int *pnValue;
} MyValue;

void callByRef(int *pnA, int *pnB) {
  int temp = *pnA;
  *pnA = *pnB;
  *pnB = temp;
}

void callByValue(int nA, int nB) {
  int temp = nA;
  nA = nB;
  nB = temp;
}

int main() {

  int nA = 3;
  int nB = 6;
  printf("nA: %d, nB: %d\n", nA, nB);
  callByValue(nA, nB);
  printf("callByVal-> nA: %d, nB: %d\n", nA, nB);

  callByRef(&nA, &nB);
  printf("callByRef-> nA: %d, nB: %d\n", nA, nB);

  // MyValue myValueArr[2] = {{&nA}, {&nB}};
  MyValue myValueArr[2] = {&nA, &nB};
  MyValue *pMyValue = &myValueArr[1];
  printf("%d\n", *pMyValue->pnValue);
  *pMyValue->pnValue = 8;
  printf("%d\n", *pMyValue->pnValue);
  return 0;

  // int a = 10;
  // int *pN = &a;
  // int **ppN = &pN;
  // printf("*ppN: %p\n", *ppN);
  // printf("**ppN: %d\n", **ppN);

#ifdef TEST
  printf("sizeof(Node*) : %lu\n", sizeof(Node));
  {

    char cArr[16] = "He";
    char *pC = cArr;
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

    uint32_t nArr[] = {1, 2, 3};
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

    Pair pairArr[2] = {{1, 2}, {3, 4}};
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
    // pPair++;
    // printf("%d\n", pPair->addr);
    // printf("&pPair: %p\n", &pPair);
    // printf("pPair: %p\n", pPair); //"H"

    // printf("%ls\n", pN);
    // printf("%p\n", &pN);
    // pN++;
    // printf("%ls\n", pN);
    // printf("%p\n", &pN);

    // for(int i=0; i<strlen(cArr); i++)
    //   printf("%c", *pC++);
  }
#endif

  Tripple t1 = {0xb1, 0xb2, 1};
  Tripple t2 = {0xb3, 0xa4, 3};

  Node *pHead = createNode(&t1, sizeof(Tripple));
  // appendNode(&List, &t1, sizeof(Tripple));
  appendNode(&pHead, &t2, sizeof(Tripple));
  dumpNode(pHead, printTripple);

  // Pair p3;
  // memcpy(&p3, &p2, sizeof(Pair));
  // printf("p2.addr: %d\n", p2.addr);
  // printf("p3.addr: %d\n", p3.addr);
  // 1. Create and Append
  Pair p1 = {0xb1, 0xb2};
  Pair p2 = {0xb3, 0xa4};

  Node *list = createNode(&p1, sizeof(Pair));
  // appendNode(&list, &p1, sizeof(Pair));
  appendNode(&list, &p2, sizeof(Pair));

  // 2. Dump
  printf("Initial List: ");
  dumpNode(list, printPair);

  // 3. Find
  Pair search = {0x1000, 0};
  Node *found = findNode(list, &search, comparePairAddr);
  if (found)
    printf("Found Addr 0x1000 with Data: 0x%X\n", ((Pair *)found->data)->data);

  // 4. Remove
  removeNode(&list, &search, comparePairAddr);
  printf("After Removal: ");
  dumpNode(list, printPair);

  freeList(list);
  return 0;
}
