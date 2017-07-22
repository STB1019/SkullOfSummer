#include <stdio.h>
#include <assert.h>

//compile it with gcc -O3 -o restrictAssert restrictAssert.c

int increase_with_no_restrict(int* a, int* b, int* c) {
    *a = *a + *c;
    *b = *b + *c;
}

int increase_with_restrict(int* restrict a, int* restrict b, int* restrict c) {
    *a = *a + *c;
    *b = *b + *c;
}

int main (int argc , char ** argv ) {
    int v1 = 1;
    int v2 = 2;
    int v3 = 1;

    // *********** contratto rispettato ****************
    v1 = 1; v2 = 2; v3 = 1; 
    increase_with_no_restrict(&v1, &v2, &v3); //funziona sempre
    assert(v1 == 2);
    assert(v2 == 3);
    v1 = 1; v2 = 2; v3 = 1;
    increase_with_restrict(&v1, &v2, &v3);
    assert(v1 == 2);
    assert(v2 == 3);

    // *************** contratto violato ****************
    v1 = 1; v2 = 2; v3 = 1;
    increase_with_no_restrict(&v1, &v2, &v1); //funziona sempre: non c'è restrict!
    assert(v1 == 2);
    assert(v2 == 4);
    v1 = 1; v2 = 2; v3 = 1;
    increase_with_restrict(&v1, &v2, &v1); //contratto di restrict violato!
    //qui, quando incremento a, in realtà sto incrementando anche c!
    assert(v1 == 2);
    assert(v2 == 4); //questa assert fallisce perché *c non è 2, ma 1!
}
