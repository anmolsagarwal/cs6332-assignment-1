void* memset1(void* str, char ch, size_t n);
void* memset2(void* str, char ch, size_t n);
void* memset_asm(void* ptr, int value, size_t num);
void* memset_sse(void* mem, int value, size_t num);