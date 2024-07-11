#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include <stdint.h>

typedef struct _hashtable* hashtable;
typedef intptr_t hash_int;
typedef double hash_float;
typedef void*  hash_ptr;

#define HASH_INT_MAX INTPTR_MAX

typedef enum {
    HASH_INT,
    HASH_FLOAT,
    HASH_PTR
} hash_type;

hashtable *hashtable_make(size_t _max_size, hash_type _type);

void hashtable_empty(hashtable *_table);

void hashtable_resize(hashtable *_table, int _new_size);

int hashtable_add_int(hashtable *_table, char *_string, hash_int _value);
int hashtable_add_float(hashtable *_table, char *_string, hash_float _value);
int hashtable_add_ptr(hashtable *_table, char *_string, hash_ptr _value);

hash_int hashtable_get_int(hashtable *_table, char* _string);
hash_float hashtable_get_float(hashtable *_table, char* _string);
hash_ptr hashtable_get_ptr(hashtable *_table, char* _string);

int hashtable_remove(hashtable *_table, char *_string);

int hashtable_copy(hashtable *_src, hashtable *_dest);

int hashtable_optimize(hashtable *_src);

int hashtable_size(hashtable *_table);

int hashtable_maxsize(hashtable *_table);

#endif // HASH_H