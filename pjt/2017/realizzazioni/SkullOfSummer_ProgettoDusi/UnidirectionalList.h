#ifndef UNIDIRECTIONALLIST_H_
#define UNIDIRECTIONALLIST_H_

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

typedef struct ulinked_list_node {
	void* data;
	struct ulinked_list_node* next;
} ulinked_list_node;

typedef struct ulinked_list {
	int size;
	ulinked_list_node* head;
} ulinked_list;


ulinked_list* ul_initList();
void ul_cleanList(ulinked_list* l);
void ul_purgeList(ulinked_list* l);
void ul_insertElementFirst(ulinked_list* l, void* new_element_data);
void ul_insertElementLast(ulinked_list* l, void* new_element_data);
void ul_insertElementAtPosition(ulinked_list* l, void* new_element_data, int pos);
void ul_insertAllElementsLast(ulinked_list* l, ulinked_list* elements);
void ul_deleteFirstElement(ulinked_list* l);
void ul_deleteLastElement(ulinked_list* l);
void ul_deleteElementAtPosition(ulinked_list* l, int pos);
void ul_deleteElementsByConditions(ulinked_list* l, bool (*condition)(void*));
void* ul_getHeadContent(ulinked_list* l);
void* ul_extractHeadContent(ulinked_list* l);
void* ul_extractElementAtPosition(ulinked_list* l, int pos);
void* ul_getTailContent(ulinked_list* l);
void* ul_getElementContentAtPosition(ulinked_list* l, int pos);
int ul_getListSize(ulinked_list* l);
int ul_getElementPosition(ulinked_list* l, void* element_content);
bool ul_containsElement(ulinked_list* l, bool (*condition)(void*));
void ul_swapTwoElements(ulinked_list* l, int pos1, int pos2);
ulinked_list* ul_cloneOrderedList(ulinked_list* l, void* (*clone)(void*));
ulinked_list* ul_cloneUnorderedList(ulinked_list* l, void* (*clone)(void*));
ulinked_list* ul_concatenateTwoLists(ulinked_list* l1, ulinked_list* l2, void* (*clone)(void*));
void* ul_getMinimumContent(ulinked_list* l, int (*compare)(void*, void*));
void* ul_getMaximumContent(ulinked_list* l, int (*compare)(void*, void*));
ulinked_list* ul_getSubList(ulinked_list* l, int start_pos, int end_pos);
ulinked_list* ul_cloneSubList(ulinked_list* l, int start_pos, int end_pos, void* (*clone)(void*));
void ul_sortByOrder(ulinked_list* l, int (*compare)(void*, void*));
char* ul_listToString(ulinked_list* l, char* (*toString)(void*));

#endif
