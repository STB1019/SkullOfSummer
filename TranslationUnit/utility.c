#include "utility.h"
#include <string.h>
char* getStringOfFoo(foo f) {
    strcat(buffer, f.nome);
    strcat(buffer, " ");
    strcat(buffer, f.cognome);
    return buffer;
}
