#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dlfcn.h>

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
  void * handle;
  void* (*_memset1) (void* str, char ch, size_t n);
  void* (*_memset2) (void* str, char ch, size_t n);
  void* (*_memset_asm) (void* ptr, int value, size_t num);
  void* (*_memset_sse) (void* mem, int value, size_t num);
  char * error;

  handle = dlopen("./libmemsets.so", RTLD_LAZY);
  if (!handle){
     exit(EXIT_FAILURE);
  }
  dlerror();

  _memset1 = (void* (*) (void*, char, size_t)) dlsym(handle, "memset1");
  _memset2 = (void* (*) (void*, char, size_t)) dlsym(handle, "memset2");
  _memset_asm = (void* (*) (void*, int, size_t)) dlsym(handle, "memset_asm");
  _memset_sse = (void* (*) (void*, int, size_t)) dlsym(handle, "memset_sse");

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
    // FIXME: memset1()
    _memset1(mem, 61, sz);
  }
  stop = clock();
  printf("Int memset1: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);
  memset(mem, 0, sz);


  start = clock();
  for (i = 0; i < e; i++) {
    // FIXME: memset2()
    _memset2(mem, 61, sz);
  }
  stop = clock();
  printf("Int memset2: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);
 

  memset(mem, 0, sz);
  
  start = clock();
  for (i = 0; i < e; i++) {
    // FIXME: memset_asm()
    _memset_asm(mem, 61, sz);
  }
  stop = clock();

  printf("ASM memset: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);

  memset(mem, 0, sz);
  
  start = clock();
  for (i = 0; i < e; i++) {
    // FIXME: memset_sse()
   _memset_sse(mem, 61, sz);
  }
  stop = clock();

  printf("SSE memset: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);
  return 0;
}
