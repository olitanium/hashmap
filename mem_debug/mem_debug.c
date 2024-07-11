#include "mem_debug.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int alloc = 0;
static int dealloc = 0;

void *debug_malloc(size_t _size, int _line, char *_file, const char *_func) {
    void *output = malloc(_size);
    if(output != NULL) {
        printf("%p allocated %u bytes on line %d in function %s\n", output, _size,  _line, _func);
        ++alloc;
    }
    else printf("Failed to allocated %u bytes on line %d in function %s\n", _size, _line, _func);
    
    return output;
}

void *d_calloc(int _count, size_t _size, int _line, char *_file, const char *_func) {
    void *output = calloc(_count, _size);
    if(output != NULL) {
        printf("%p allocated %u bytes on line %d in function %s\n", output, _size,  _line, _func);
        ++alloc;
    }
    else printf("Failed to allocated %u bytes on line %d in function %s\n", _size, _line, _func);
    
    return output;
}

void debug_free(void *_pointer, int _line, char *_file, const char *_func) {
    if(_pointer != NULL) {
        printf("%p freed on line %d in function %s\n", _pointer, _line, _func);
        free(_pointer);
        ++dealloc;
    } 
    else printf("Attempted to free null pointer on line %d in function %s\n", _line, _func);
}
/* 
char *debug_strdup(const char *src, int _line, char *_file, const char *_func) {
    char *dst = malloc(strlen (src) + 1);  // Space for length plus null
     
    if(dst != NULL) {
        printf("%p allocating string on line %d in function %s\n", dst, _line, _func);
        ++alloc;
        strcpy(dst, src);                      // Copy the characters     
    } else {
        printf("Failed to allocated string on line %d in function %s\n", _line, _func);
    }
    
    return dst;          // Return new string or null
}
 */