#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int hash(const char *_input) {
    int primes[] = {2,3,5,7,11,13,17,19,23,29,0};
    int index = 0;
    int hash = 0;
    int increment = 0;
    while ( (increment = _input[index] * primes[index]) != 0) {
        hash += increment;
        ++index;
    }
    
    return hash;
}

void _element_make_internal(struct element *_element, char *_string, union data _value, int _access_count) {
//    strncpy(_element->string, _string, min(sizeof(_element->string), strlen(_string + 1)) ); //uncomment when element key is fixed in length
    size_t length = ( strlen(_string) + 1 ) * sizeof(char);

    _element->string = malloc( length );
    memmove(_element->string, _string, length);
    _element->value = _value;
    _element->access_count = _access_count;
}

void _element_empty_internal(struct element *_element, hash_type type) {
    free(_element->string);
    _element->string = NULL;
    if (type == HASH_PTR) {
        free(_element->value.pointer);
    }
    _element->value.integer = 0;
    _element->access_count = 0;
}

struct _hashtable *internal_hashtable_make(size_t _max_size, hash_type _type) {
    if(NULL == 0) {
        struct _hashtable *table = (struct _hashtable*) calloc(1, sizeof(struct _hashtable) + (_max_size - 1) * sizeof(struct element));
        
        if(table != NULL) {
            table->max_size = _max_size;
            table->type = _type;
        }
        
        return table;
    } else {
        struct _hashtable *table = (struct _hashtable*) malloc(sizeof(struct _hashtable) + (_max_size - 1) * sizeof(struct element));
        
        if(table == NULL) return NULL;
        
        table->max_size = _max_size;
        table->type = _type;
        table->num_filled = 0;
        
        for (int i = 0, end = _max_size; i < end; i++) {
            table->list[i].string = NULL;
            table->list[i].value.integer = 0;
            table->list[i].access_count = 0;
        }
        return table;
    }
    
}

void _hashtable_empty_internal(struct _hashtable *ptr_table) {
    for (size_t i = 0, end = ptr_table->max_size; i < end; i++)
        if (ptr_table->list[i].string != NULL)
            _element_empty_internal(ptr_table->list + i, ptr_table->type);
    free(ptr_table);
}

int _hashtable_add_internal(struct _hashtable *ptr_table, char *_string, union data _value, int _access_count) {
    size_t index = hash(_string) % ptr_table->max_size;
    size_t iter_index = index;

    while (ptr_table->list[iter_index].string != NULL) {
        if (!strcmp(ptr_table->list[iter_index].string, _string))  return 1; // Error: Value already in hashtable
        
        ++iter_index;
        iter_index %= ptr_table->max_size;
        if (iter_index == index) return 9; // Error: Catastrophic, Loop should never continue this far
    }
    
    _element_make_internal(ptr_table->list + iter_index, _string, _value, _access_count);
    ++(ptr_table->num_filled);
    return 0; // Success: Added to hashtable
}

int _hashtable_copy_internal(struct _hashtable *ptr_src, struct _hashtable *ptr_dest) {
    if(ptr_src->num_filled > ptr_dest->max_size) return 10;
    
    for (int i = 0, counter = 0, end = min(ptr_src->num_filled, ptr_dest->max_size); counter < end; ++i) {
        if (ptr_src->list[i].string != NULL) {
            int code = _hashtable_add_internal(ptr_dest, ptr_src->list[i].string, ptr_src->list[i].value, ptr_src->list[i].access_count);
            if(code != 0) return 10 + code;
            ++counter;
        }
    }
    return 0;
}

int _hashtable_size_det_internal(struct _hashtable **_table, char *_string, union data _value) {
    struct _hashtable *ptr_table = *_table;
    
    if (ptr_table->num_filled >= ptr_table->max_size) {
            hashtable_resize(_table, ptr_table->num_filled * 2);
            int output = 0;
            if((output = _hashtable_add_internal(*_table, _string, _value, 0)) == 0) return 10; // Success: Not in hashtable and hashtable full. Hashtable extended
            else return 10 + output; // 1x Failure, x is single digit error code of add_internal 
    }
    
    return _hashtable_add_internal(ptr_table, _string, _value, 0);
}

union data _hashtable_get_internal(struct _hashtable **_table, char *_string) {
    struct _hashtable *ptr_table = *_table;
    int index = hash(_string) % ptr_table->max_size;
    int iter_index = index;
    while (ptr_table->list[iter_index].string != NULL ) {
        if (!strcmp(ptr_table->list[iter_index].string, _string)) {
            ++(ptr_table->list[iter_index].access_count);
            return ptr_table->list[iter_index].value; // Success
        }
        ++iter_index;
        iter_index %= ptr_table->max_size;
        
        if (iter_index == index) {
            union data error;
            error.integer = HASH_INT_MAX - 2;
            return error;
        }; // Error: Not in hashtable and hashtable full 
    }
    union data error;
    error.integer = HASH_INT_MAX - 1;
    return error; // Error: Not in hashtable and hashtable not full
}

// declared in hash.h

struct _hashtable **hashtable_make(size_t _max_size, hash_type _type) {
    if (_max_size <= 0) return NULL;
    
    struct _hashtable *table = internal_hashtable_make(_max_size, _type);
    if( table == NULL ) return NULL;
    
    struct _hashtable **output = (struct _hashtable**) malloc(sizeof(struct _hashtable*));
    if( output == NULL ) {
        _hashtable_empty_internal(table);
        return NULL;
    }
    
    *output = table;
    return output;
}

void hashtable_empty(struct _hashtable **_table) {
    _hashtable_empty_internal(*_table);
    free(_table);
}

void hashtable_resize(struct _hashtable **_table, int _new_size) {
    struct _hashtable *ptr_old_table = *_table;
    struct _hashtable *ptr_new_table = internal_hashtable_make(_new_size, ptr_old_table->type);
    _hashtable_copy_internal(ptr_old_table, ptr_new_table);
    _hashtable_empty_internal(ptr_old_table);
    *_table = ptr_new_table;
}

int hashtable_add_int(struct _hashtable **_table, char *_string, hash_int _value) {
    if ((**_table).type != HASH_INT) return 2;
    
    union data union_value;
    union_value.integer = _value;
    return _hashtable_size_det_internal(_table, _string, union_value);
}

int hashtable_add_float(struct _hashtable **_table, char *_string, hash_float _value) {
    if ((**_table).type != HASH_FLOAT) return 2;    
    
    union data union_value;
    union_value.floating = _value;
    return _hashtable_size_det_internal(_table, _string, union_value);
}

int hashtable_add_ptr(struct _hashtable **_table, char *_string, hash_ptr _value) {
    if ((**_table).type != HASH_PTR) return 2;
    
    union data union_value;
    union_value.pointer = _value;
    return _hashtable_size_det_internal(_table, _string, union_value);
}

hash_int hashtable_get_int(struct _hashtable **_table, char *_string) {
    if ((**_table).type != HASH_INT) return HASH_INT_MAX;
    return _hashtable_get_internal(_table, _string).integer;
}

hash_float hashtable_get_float(struct _hashtable **_table, char *_string) {
    if ((**_table).type != HASH_FLOAT) return NAN;
    return _hashtable_get_internal(_table, _string).floating;
}

hash_ptr hashtable_get_ptr(struct _hashtable **_table, char *_string) {
    if ((**_table).type != HASH_PTR) return NULL;
    union data output = _hashtable_get_internal(_table, _string);
    if (output.integer >= HASH_INT_MAX - 9) return NULL;
    else return output.pointer;
}

int hashtable_remove(struct _hashtable **_table, char *_string) {
    struct _hashtable *ptr_table = *_table;
    int index = hash(_string) % ptr_table->max_size;
    int iter_index = index;
    
    while (ptr_table->list[iter_index].string != NULL ) {
        if (!strcmp(ptr_table->list[iter_index].string, _string)) {
            _element_empty_internal( ptr_table->list + iter_index, ptr_table->type);
            --(ptr_table->num_filled);
            return 0;
        }
        ++iter_index;
        iter_index %= ptr_table->max_size;
        
        if (iter_index == index) return 2; // Error: Not in hashtable and hashtable full 
    }
    return 1; // Error: Not in hashtable and hashtable not full 
}

int hashtable_copy(struct _hashtable **_src, struct _hashtable **_dest) {
    return _hashtable_copy_internal(*_src, *_dest);
}

int hashtable_comparison(const void *lhs, const void *rhs) {
    return
        ( (const struct element*) lhs )->access_count == ( (const struct element*) rhs )->access_count ?  0 :
        ( (const struct element*) lhs )->access_count <  ( (const struct element*) rhs )->access_count ? +1 : 
                                                                                                         -1 ;
}

int hashtable_optimize(struct _hashtable **_src) {
    struct _hashtable *ptr_old_table = *_src;
    struct _hashtable *ptr_new_table = internal_hashtable_make((*_src)->max_size, ptr_old_table->type);
    
    qsort( ptr_old_table->list, ptr_old_table->max_size, sizeof(struct element), hashtable_comparison);
    
    _hashtable_copy_internal(ptr_old_table, ptr_new_table);
    _hashtable_empty_internal(ptr_old_table);
    
    *_src = ptr_new_table;
    return 0;
}

int hashtable_size(struct _hashtable **_table) {
    return (**_table).num_filled;
}

int hashtable_maxsize(struct _hashtable **_table) {
    return (**_table).max_size;
}
