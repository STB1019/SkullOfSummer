#ifndef P3_JSON_INCLUDED
#define P3_JSON_INCLUDED

#ifdef JSON_C_INCLUDE
#	define UTILS_PRIVATE_INCLUDE
#   include <stdbool.h>
#   include <stdio.h>
#   include <string.h>
#   include "utils.h"
#endif

sos_list_t * parseJSON(FILE *);

#endif
