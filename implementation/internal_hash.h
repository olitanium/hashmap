#ifndef INTERNAL_HASH_H
#define INTERNAL_HASH_H

#define min(a, b) (a) < (b) ? (a) : (b)

union data {
    hash_int integer;
    hash_ptr pointer;
    hash_float floating;
};

struct element {
    union data value;
    int access_count;
    char* string;
};

struct _hashtable {
    hash_type type;
    size_t max_size;
    int num_filled;
    struct element list[1]; // size of list == max_size
};

int hash(const char* _input);

void _element_make_internal(struct element* _element, char* _string, union data _value, int _access_count);

void _element_empty_internal(struct element* _pointer, hash_type _type);

struct _hashtable *internal_hashtable_make(size_t _max_size, hash_type _type);

void _hashtable_empty_internal(struct _hashtable *_table);

int _hashtable_size_det_internal(struct _hashtable **_table, char *_string, union data _value);

union data _hashtable_get_internal(struct _hashtable **_table, char *_string);

int _hashtable_copy_internal(struct _hashtable *ptr_src, struct _hashtable *ptr_dest);

#endif // INTERNAL_HASH_H
