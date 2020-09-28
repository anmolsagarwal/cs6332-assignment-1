#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "memsets.c"

void check(char* mem, int sz, int val) {
  for (int i = 0; i < sz; i++) {
    if (*(mem + i) != val) {
      printf("Failed at %i (%x)!\n", i, *(mem + i));
      break;
      }
  }
}

int main(int argc, char** argv) {
  unsigned int i, e = 1024, sz = 1024 * 1024;
  clock_t start, stop;
  char* mem = (char*) malloc(sz);

  start = clock();
  for (i = 0; i < e; i++) {
    memset(mem, 61, sz);
  }
  stop = clock();
  printf("Standard memset: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);

  memset(mem, 0, sz);

  start = clock();
  for (i = 0; i < e; i++) {
    memset1(mem, 61, sz);
  }
  stop = clock();
  printf("Int memset1: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);
  memset(mem, 0, sz);


  start = clock();
  for (i = 0; i < e; i++) {
    memset2(mem, 61, sz);
  }
  stop = clock();
  printf("Int memset2: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);
 

  memset(mem, 0, sz);
  
  start = clock();
  for (i = 0; i < e; i++) {
    memset_asm(mem, 61, sz);
  }
  stop = clock();

  printf("ASM memset: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);

  memset(mem, 0, sz);
  
  start = clock();
  for (i = 0; i < e; i++) {
    memset_sse(mem, 61, sz);
  }
  stop = clock();

  printf("SSE memset: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);
  return 0;
}
