#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

typedef struct list list;

list* initList();

typedef struct list_cell {
	void* payload;
	struct list_cell* next;
} list_cell;

void destroyList(list* l);

void destroyListWithElement(list* l, void (*d)(void*));

void clearList(list* l);

void addHeadInList(list* l, void* el);

void addTailInList(list* l, void* el);

int getLengthOfList(const list* l);

bool isEmptyList(const list* l);

void* popFromList(list* l);

void* getHeadOfList(const list* l);

void* getTailOfList(const list* l);

bool removeElementInList(list* l, bool (*f)(void*));

bool removeAndDestroyElementInList(list* l, bool (*f)(void*), void (*d)(void*));

#endif /* LIST_H_ */
