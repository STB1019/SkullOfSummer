#!/bin/bash

gcc -DQUICK_LOG=7 -c log.c -o log.o
gcc -DQUICK_LOG=7 -c testLog.c -o testLog.o

gcc -DQUICK_LOG=7 testLog.o log.o -o testLogRelease
