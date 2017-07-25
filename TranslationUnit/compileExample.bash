#!/bin/bash

gcc -c foo_handler.c -o foo_handler.o
gcc -c utility.c -o utility.o
gcc -c my_awesome_program.c -o my_awesome_program.o

gcc foo_handler.o utility.o my_awesome_program.o -o my_awesome_program
./my_awesome_program

