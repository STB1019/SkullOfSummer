#include "list.h"

#include <stdlib.h>

typedef struct list_cell {
	void* payload;
	struct list_cell* next;
} list_cell;

struct list {
	int size;
	list_cell* head;
	list_cell* tail;
};

list* initList() {
	list* retVal = malloc(sizeof(list));
	if (retVal == NULL) {
		exit(1);
	}

	retVal->head = NULL;
	retVal->size = 0;
	retVal->tail = NULL;

	return retVal;
}

void destroyList(list* lst) {
	list_cell* tmp = lst->head;
	list_cell* tmp2;

	while (tmp != NULL) {
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	free(lst);
}

void destroyListWithElement(list* lst, void (*d)(void*)) {
	list_cell* tmp = lst->head;
	list_cell* tmp2;

	while (tmp != NULL) {
		tmp2 = tmp->next;
		d(tmp->payload);
		free(tmp);
		tmp = tmp2;
	}
	free(lst);
}

void clearList(list* l) {
	list_cell* tmp = l->head;
	list_cell* tmp2;
	while (tmp != NULL) {
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	l->head = NULL;
	l->size = 0;
	l->tail = NULL;
}

void addHeadInList(list* l, void* el) {
	list_cell* new_cell = malloc(sizeof(list_cell));
	if (new_cell == NULL) {
		exit(1);
	}

	new_cell->payload = el;
	new_cell->next = l->head;

	l->size++;
	l->head = new_cell;
	if (l->tail == NULL) {
		l->tail = new_cell;
	}
}

void addTailInList(list* l, void* el) {
	list_cell* new_cell = malloc(sizeof(list_cell));
	if (new_cell == NULL) {
		exit(1);
	}

	new_cell->payload = el;
	new_cell->next = NULL;
	if (l->tail != NULL) {
		l->tail->next = new_cell;
	}

	l->size++;
	if (l->head == NULL) {
		l->head = new_cell;
	}
	l->tail = new_cell;

}

int getSizeOfList(const list* l) {
	return l->size;
}


bool isEmptyList(const list* l) {
	return l->size == 0;
}

void* popFromList(list* l) {
	if (isEmptyList(l)) {
		return NULL;
	}

	list_cell* cell = l->head;
	void* retVal = cell->payload;
	l->head = l->head->next;
	l->size--;
	if (isEmptyList(l)) {
		l->tail = NULL;
	}

	free(cell);
	return retVal;
}

void* getHeadOfList(const list* l) {
	if (isEmptyList(l)) {
		return NULL;
	}
	return l->head->payload;
}

void* getTailOfList(const list* l) {
	if (l->tail == NULL) {
		return NULL;
	}
	return l->tail->payload;
}

bool removeElementInList(list* l, bool (*f)(void*)) {
	list_cell* previous = NULL;
	list_cell* tmp = l->head;
	list_cell* tmp2;
	while (tmp != NULL) {
		tmp2 = tmp->next;
		if (f(tmp->payload)) {
			if (previous == NULL) {
				//head removal
				l->head = tmp->next;
			} else {
				previous->next = tmp->next;
			}
			l->size--;

			free(tmp);
			return true;
		}
		previous = tmp;
		tmp = tmp2;
	}
	return false;
}

bool removeAndDestroyElementInList(list* l, bool (*f)(void*), void (*d)(void*)) {
	list_cell* previous = NULL;
	list_cell* tmp = l->head;
	list_cell* tmp2;
	while (tmp != NULL) {
		tmp2 = tmp->next;
		if (f(tmp->payload)) {
			if (previous == NULL) {
				//head removal
				l->head = tmp->next;
			} else {
				previous->next = tmp->next;
			}
			l->size--;

			d(tmp->payload);
			free(tmp);
			return true;
		}
		previous = tmp;
		tmp = tmp2;
	}
	return false;
}
