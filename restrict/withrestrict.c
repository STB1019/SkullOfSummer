//compile via gcc -S -O3 -o baserestrict.s baserestrict.c

int increase(int* restrict a, int* restrict b, int* restrict c) {
  *a = *a + *c;
  *b = *b + *c;
}
