#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>

//#define DEBUG
//#include "mem_debug/mem_debug.h"


struct hello {
    int number;
    float other_number;

    double third_number;
};


int main() {
    {
        hashtable* Oliver = hashtable_make(10, HASH_PTR);

        hashtable_add_ptr(Oliver, "location", malloc( sizeof(struct hello) ));

        struct hello *ptr_location = (struct hello *) hashtable_get_ptr(Oliver, "location");

        if (ptr_location != NULL) {
            ptr_location->number = 10;

            printf("%d\n", ptr_location->number);
        }
        
        hashtable_empty(Oliver);

        /*
        hashtable oli_hashtable = hashtable_make(3, HASH_FLOAT);
        
        hashtable_add_float(oli_hashtable, "hello world", 1.5); // Hash 1.
        hashtable_add_float(oli_hashtable, "entry three", 1.2); // Hash 1.
        
        double fifteen =   hashtable_get_float(oli_hashtable, "hello world");
        void *twelve = hashtable_get_ptr(oli_hashtable, "entry three");
        void *error  = hashtable_get_ptr(oli_hashtable, "heyo");

        hashtable_empty(oli_hashtable);
        */
    }
    
    return 0;
}
