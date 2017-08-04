#!/bin/bash

gcc $1 -c -g -I ./include -Wpedantic c/*.c test/main.c
gcc -o ezparse *.o
rm *.o
