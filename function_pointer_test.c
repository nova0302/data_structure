#include <stdio.h>
#include "stdint.h"

int add(int a, int b){
  return a+b;
}

int sub(int a, int b){
  return a-b;
}

typedef int (*arith_fun)(int,int);

arith_fun arith_f[]={add, sub};

int main(){

  for(int i=0; i<4; i++){
    //printf("%d : Hello World\n", i);
    //printf("%d + %d = %d", i,i, add(i,i));
    printf("%d + %d = %d", i,i, arith_f[i%2]);
  }
  uint32_t nAge = 32;
  uint32_t nHeight = 15;
  sub(nAge, nHeight);
  add(nAge, nHeight);

  return 0;
}
