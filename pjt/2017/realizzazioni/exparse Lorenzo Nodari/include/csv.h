#ifndef P3_CSV_INCLUDED
#define P3_CSV_INCLUDED

#ifdef CSV_C_INCLUDE
#   define UTILS_PRIVATE_INCLUDE
#   include <stdio.h>
#   include <stdlib.h>
#   include <stdbool.h>
#   include <string.h>
#   include "utils.h"
#endif

sos_list_t * parseCSV(FILE *);

#endif
