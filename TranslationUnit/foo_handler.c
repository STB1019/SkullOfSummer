#include "foo_handler.h"
#include <stdio.h>
#include <stdlib.h>

void handle_foo(foo f) {
     char* fullName = getStringOfFoo(f);
     FILE* out = fopen(fullName, "w");
     if (out == NULL) {
         exit(1);
     }
     fprintf(out, "eta di %s è %d\n", fullName, f.eta);
     fclose(out);
}
