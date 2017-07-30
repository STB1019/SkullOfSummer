#!/bin/bash

#compile shared library
rm -f mathutils.o randutils.o
gcc -g -fPIC -c mathutils.c -o mathutils.o
gcc -g -fPIC -c randutils.c -o randutils.o
gcc -g -shared -Wl,-soname,libawesomeshared.so \
	mathutils.o randutils.o \
	-o libawesomeshared.so

rm -f mathutils.o randutils.o
#compile static library
gcc -g -c mathutils.c -o mathutils.o
gcc -g -c randutils.c -o randutils.o
ar -rc libawesomestatic.a mathutils.o randutils.o

#compile the program that will use the static library
gcc -g useawesome.c -L. -lawesomestatic -o useawesomeStatic

#compile the program that will use the dynamic library
gcc -g useawesome.c -L. -lawesomeshared -o useawesomeShared
