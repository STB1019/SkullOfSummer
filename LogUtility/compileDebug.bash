#!/bin/bash

gcc -DQUICK_LOG=0 -c log.c -o log.o
gcc -DQUICK_LOG=0 -c testLog.c -o testLog.o

gcc -DQUICK_LOG=0 testLog.o log.o -o testLogDebug
