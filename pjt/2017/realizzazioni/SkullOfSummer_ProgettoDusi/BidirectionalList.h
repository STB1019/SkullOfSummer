#ifndef BIDIRECTIONALLIST_H_
#define BIDIRECTIONALLIST_H_

#include <stdbool.h>

#ifndef SIZE_OPERATIONS
#	define SIZE_OPERATIONS
#	define INT_SWAP(a, b) a = a + b; b = a - b; a = a - b
#	define EMPTY_SIZE 0
#endif

#ifndef STRING_FORMATTING
#	define STRING_FORMATTING
	const char STRING_TITLE[] = "LISTA [size: %-10d]\n";
	const int STRING_TITLE_LENGTH = 26;
#endif

typedef struct blinked_list_node {
	void* data;
	struct blinked_list_node* next;
	struct blinked_list_node* prev;
} blinked_list_node;

typedef struct blinked_list {
	int size;
	blinked_list_node* head;
	blinked_list_node* tail;	
} blinked_list;

blinked_list* bl_initList();
void bl_cleanList(blinked_list* l);
void bl_purgeList(blinked_list* l);
void bl_insertElementFirst(blinked_list* l, void* new_element_data);
void bl_insertElementLast(blinked_list* l, void* new_element_data);
void bl_insertElementAtPosition(blinked_list* l, void* new_element_data, int pos);
void bl_insertAllElementsLast(blinked_list* l, blinked_list* elements);
void bl_deleteFirstElement(blinked_list* l);
void bl_deleteLastElement(blinked_list* l);
void bl_deleteElementAtPosition(blinked_list* l, int pos);
void bl_deleteElementsByConditions(blinked_list* l, bool (*condition)(void*));
void* bl_getHeadContent(blinked_list* l);
void* bl_extractHeadContent(blinked_list* l);
void* bl_extractElementAtPosition(blinked_list* l, int pos);
void* bl_getTailContent(blinked_list* l);
void* bl_getElementContentAtPosition(blinked_list* l, int pos);
int bl_getListSize(blinked_list* l);
int bl_getElementPosition(blinked_list* l, void* element_content);
bool bl_containsElement(blinked_list* l, bool (*condition)(void*));
void bl_swapTwoElements(blinked_list* l, int pos1, int pos2);
blinked_list* bl_cloneOrderedList(blinked_list* l, void* (*clone)(void*));
blinked_list* bl_cloneUnorderedList(blinked_list* l, void* (*clone)(void*));
blinked_list* bl_concatenateTwoLists(blinked_list* l1, blinked_list* l2, void* (*clone)(void*));
void* bl_getMinimumContent(blinked_list* l, int (*compare)(void*, void*));
void* bl_getMaximumContent(blinked_list* l, int (*compare)(void*, void*));
blinked_list* bl_getSubList(blinked_list* l, int start_pos, int end_pos);
blinked_list* bl_cloneSubList(blinked_list* l, int start_pos, int end_pos, void* (*clone)(void*));
void bl_sortByOrder(blinked_list* l, int (*compare)(void*, void*));
char* bl_listToString(blinked_list* l, char* (*toString)(void*));

#endif
