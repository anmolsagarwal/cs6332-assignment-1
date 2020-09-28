#include <stddef.h>
#include <stdlib.h>
void* memset1(void* mem, int value, size_t num) {
  char* m = mem;
  char v = value;
  while (num-- != 0)
    *(m + num) = v;
  return mem;
}

void* memset2(void* str, char ch, size_t n){
	int i;
	//type cast the str from void* to char*
	char *s = (char*) str;
	//fill "n" elements/blocks with ch
	for(i=0; i<n; i++)
		s[i]=ch;
    return str;
}    

void* memset_asm(void* ptr, int value, size_t num) {
  asm("rep stosl;" : : "a"(value | (value << 8) | (value << 16) | (value << 24)), "D" ((size_t) ptr), "c" (num / 4));
  asm("rep stosb;" : : "a"(value), "D" (((size_t) ptr) + ((num / 4) * 4)),
     "c" (num - ((num / 4) * 4)));
  return ptr;
}

void* memset_sse(void* mem, int value, size_t num) {
  value = value | (value << 8);
  for (; num >= 16; num -= 16) {
    asm(
      "movd %0, %%xmm0    \n\t"
      "movdqu %%xmm0, 0(%1) \n\t"
    : : "r" (value), "r" (mem));
    }
    return mem;
}



void memcpy1(void *dest, void *src, size_t size){
	void *temp = malloc(size);
	int i;
	for(i=0; i<size; i++){
		*((char*)temp+i) = *((char*)src+i);
	}
	for(i=0; i<size; i++){
		*((char*)dest+i) = *((char*)temp+i);
	}
	free(temp);
}
