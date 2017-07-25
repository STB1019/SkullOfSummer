#include "utility.h"
#include "foo_handler.h"
#include <stdio.h>

int main() {
     foo paolo_rossi = {"Paolo", "Rossi", 24};
     printf("%s\n", getStringOfFoo(paolo_rossi));
     handle_foo(paolo_rossi);
}
