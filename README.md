# hashmap

## Error Codes

### hashtable_make()
NULL: Could not allocate memory for either of the pointers. or;
NULL: The input _max_size was leq 0.

### hashtable_add()
0:    Success, entry added.
1:    Fail, key already in table.
2:    Fail, accessing wrong datatype.
9:    Fail, implemenation issue. This should never occur.
10:   Success, entry added after table expanded.
11:   Fail, key already in table after table expanded. This should never occur
19:   Fail, implemenation issue after table expanded. This should never occur.

### hashtable_copy()
0:    Success, table copied.
10:   Fail, destination too small, random entries will be lost.
11:   Fail, duplicate key in source hashtable.
19:   Fail, implementation issue. This should never occur.

### _hashtable_get_internal().integer
HASH_INT_MAX:     Fail, wrong datatype
HASH_INT_MAX - 1: Fail, not in hashtable and hashtable full 
HASH_INT_MAX - 2: Fail, not in hashtable and hashtable not full

HASH_INT_MAX - x: Fail, reserved x = 0..=9

### hashtable_get_int()
HASH_INT_MAX: Fail

### hashtable_get_float()
NaN: Fail

### hashtable_get_ptr()
NULL: Fail