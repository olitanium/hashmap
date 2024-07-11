#ifndef MEM_DEBUG_H
#define MEM_DEBUG_H

#ifdef DEBUG

#include "stddef.h"

void *debug_malloc(size_t _size, int _line, char *_file, const char *_func);

void *d_calloc(int _count, size_t _size, int _line, char *_file, const char *_func);

void debug_free(void *_pointer, int _line, char *_file, const char *_func);

char *debug_strdup(const char *src, int _line, char *_file, const char *_func);

#define malloc(x) debug_malloc(x, __LINE__, __FILE__, __func__)
#define calloc(y, x) debug_calloc(y, x, __LINE__, __FILE__, __func__)
#define free(x)   debug_free(x, __LINE__, __FILE__, __func__)
#define strdup(x) debug_strdup(x, __LINE__, __FILE__, __func__)

#endif // DEBUG

#endif // MEM_DEBUG_H