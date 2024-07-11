main.out: main.c hashtable.h
	gcc hashtable.c main.c -o a.out

hashtable.h: implementation/hash.h implementation/internal_hash.h implementation/hash.c
	./gen_header.sh

clean:
	rm -f hashtable.h a.out
