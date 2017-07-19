#!/bin/bash

gcc -UUSERESTRICT -O3 -S -o testWithoutRestrict.s testrestrict.c
gcc -DUSERESTRICT -O3 -S -o testWithRestrict.s testrestrict.c

gcc -UUSERESTRICT -O3 -o testWithoutRestrict testrestrict.c
gcc -DUSERESTRICT -O3 -o testWithRestrict testrestrict.c
