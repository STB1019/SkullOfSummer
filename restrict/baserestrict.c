//compile via gcc -S -O3 -o baserestrict.s baserestrict.c

int increase(int* a, int* b, int* c) {
  *a = *a + *c;
  *b = *b + *c;
}
