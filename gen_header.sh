#!/bin/bash

touch hashtable.h

cat implementation/hash.h > hashtable.h

echo "
#ifdef IMPLEMENTATION
" >> hashtable.h

cat implementation/internal_hash.h >> hashtable.h

echo "

" >> hashtable.h

cat implementation/hash.c >> hashtable.h

echo "

#endif // IMPLEMENTATION
" >> hashtable.h