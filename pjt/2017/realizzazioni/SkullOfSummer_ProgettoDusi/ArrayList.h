#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include <stdbool.h>

typedef struct arraylist {
	int size;
	int capacity;
	void** array;
} arraylist;

arraylist* al_initListWithCapacity(int cap);
arraylist* al_initList();
void al_cleanList(arraylist* l);
void al_purgeList(arraylist* l);
void al_insertElementFirst(arraylist* l, void* new_element_data);
void al_insertElementLast(arraylist* l, void* new_element_data);
void al_insertElementAtPosition(arraylist* l, void* new_element_data, int pos);
void al_deleteFirstElement(arraylist* l);
void al_deleteLastElement(arraylist* l);
void al_deleteElementAtPosition(arraylist* l, int pos);
void al_deleteElementsByConditions(arraylist* l, bool (*condition)(void*));
void* al_getHeadContent(arraylist* l);
void* al_extractHeadContent(arraylist* l);
void* al_extractElementAtPosition(arraylist* l, int pos);
void* al_getTailContent(arraylist* l);
void* al_getElementContentAtPosition(arraylist* l, int pos);
int al_getListSize(arraylist* l);
int al_getElementPosition(arraylist* l, void* element_content);
bool al_containsElement(arraylist* l, bool (*condition)(void*));
void al_swapTwoElements(arraylist* l, int pos1, int pos2);
arraylist* al_cloneOrderedList(arraylist* l, void* (*clone)(void*));
arraylist* al_concatenateTwoLists(arraylist* l1, arraylist* l2, void* (*clone)(void*));
void* al_getMinimumContent(arraylist* l, int (*compare)(void*, void*));
void* al_getMaximumContent(arraylist* l, int (*compare)(void*, void*));
arraylist* al_getSubList(arraylist* l, int start_pos, int end_pos);
arraylist* al_cloneSubList(arraylist* l, int start_pos, int end_pos, void* (*clone)(void*));
void al_sortByOrder(arraylist* l, int (*compare)(void*, void*));
char* al_listToString(arraylist* l, char* (*toStringFunction)(void*));

#endif
