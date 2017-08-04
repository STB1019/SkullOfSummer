#ifndef HEAP_H_
#define HEAP_H_

#include "List.h"

typedef struct binaryheap {
	list* genericlist;
	int (*comparefunction)(void*, void*);
} binaryheap;

binaryheap* bh_initHeap(int (*compare)(void*, void*));
void bh_cleanHeap(binaryheap* h);
void bh_purgeHeap(binaryheap* h);
void bh_insertElement(binaryheap* h, void* new_element_data);
int bh_getHeapSize(binaryheap* h);
int bh_getElementPosition(binaryheap* h, void* element_to_find);
void bh_deleteElementAtPosition(binaryheap* h, int pos);
void bh_deleteElementByContent(binaryheap* h, void* element_to_delete);
void bh_deleteElementsByConditions(binaryheap* h, bool (*condition)(void*));
void bh_deleteFirstElement(binaryheap* h);
void* bh_getElementAtPosition(binaryheap* h, int pos);
void* bh_extractElementAtPosition(binaryheap* h, int pos);
list* bh_extractElementsByConditions(binaryheap* h, bool (*condition)(void*));
list* bh_getElementList(binaryheap* h);
void* bh_getMaximumContent(binaryheap* h);
void* bh_getMinimumContent(binaryheap* h);
char* heapToString(binaryheap* h, char* (*toStringFunction)(void*));

#endif
