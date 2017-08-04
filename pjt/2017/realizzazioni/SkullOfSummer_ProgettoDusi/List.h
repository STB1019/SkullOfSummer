#ifndef LIST_H_
#define LIST_H_

#include "UnidirectionalList.h"
#include "BidirectionalList.h"
#include "ArrayList.h"

#include "Conversion.h"

#ifndef TYPE_ERROR
	#define TYPE_ERROR printf("Error: unknown type.\n"); exit(1)
#endif

typedef enum l_type {ul, bl, al} l_type;
const int list_t_number = 3;

typedef struct list {
	l_type type;
	/**
	 * 'ul' -> Unidirectional Linked List
	 * 'bl' -> Bidirectional Linked List
	 * 'al' -> Array List
	 */
	union {
		ulinked_list* ul;
		blinked_list* bl;
		arraylist* al;
	} genericlist;
} list;

list* initList(l_type chosen_type);
void cleanList(list* l);
void purgeList(list* l);
void insertElementFirst(list* l, void* new_element_data);
void insertElementLast(list* l, void* new_element_data);
void insertElementAtPosition(list* l, void* new_element_data, int pos);
void deleteFirstElement(list* l);
void deleteLastElement(list* l);
void deleteElementAtPosition(list* l, int pos);
void deleteElementsByConditions(list* l, bool (*condition)(void*));
void* getHeadContent(list* l);
void* extractHeadContent(list* l);
void* extractElementAtPosition(list* l, int pos);
void* getTailContent(list* l);
void* getElementContentAtPosition(list* l, int pos);
int getListSize(list* l);
int getElementPosition(list* l, void* element_content);
bool containsElement(list* l, bool (*condition)(void*));
void swapTwoElements(list* l, int pos1, int pos2);
list* cloneOrderedList(list* l, void* (*clone)(void*));
list* concatenateTwoLists(list* l11, list* l22, void* (*clone)(void*));
void* getMinimumContent(list* l, int (*compare)(void*, void*));
void* getMaximumContent(list* l, int (*compare)(void*, void*));
list* getSubList(list* l, int start_pos, int end_pos, void* (*clone)(void*));
list* cloneSubList(list* l, int start_pos, int end_pos, void* (*clone)(void*));
void sortByOrder(list* l, int (*compare)(void*, void*));
char* listToString(list* l, char* (*toStringFunction)(void*));

void convertInnerListTypeTo(list* l, l_type new_type);
#endif
