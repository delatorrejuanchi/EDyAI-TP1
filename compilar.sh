gcc -c util.c -Wall -pedantic
gcc -c glist.c -Wall -pedantic
gcc -o parte1 parte1.c glist.o util.o -Wall -pedantic
gcc -o parte2 parte2.c glist.o util.o -Wall -pedantic
