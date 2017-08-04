#include <stdlib.h>
#include <stdio.h>

#include "Conversion.h"

#ifndef MEMORY_ERROR
#	define MEMORY_ERROR printf("Error: Cannot allocate memory.\n"); exit(1)
#endif

/**
 * Converte una lista linkata monodirezionale (ulinked_list) in ArrayList (arraylist).
 * La lista originale viene eliminata (ma non vengono eliminati i suoi elementi, che sono ovviamente
 * spostati nell'arraylist).
 */
arraylist* ul_convertToArrayList(ulinked_list* l) {
	arraylist* al = malloc(sizeof(arraylist));
	if (!al) {
		MEMORY_ERROR;
	}
	al->size = l->size;
	al->capacity = (int)(l->size * 1.5);
	al->array = malloc(sizeof(void*) * al->capacity);
	if (!(al->array)) {
		MEMORY_ERROR;
	}
	ulinked_list_node* iterator = l->head;
	for (int i = 0; i < l->size; i++) {
		al->array[i] = iterator->data;
		iterator = iterator->next;
	}
	ul_cleanList(l);
	return al;
}

/**
 * Copia una lista linkata monodirezionale in un arraylist.
 * La lista linkata originale non viene modificata o cancellata.
 */
arraylist* ul_copyToArrayList(ulinked_list* l, void* (*clone)(void*)) {
	return ul_convertToArrayList(ul_cloneOrderedList(l, clone));
}



/**
 * Converte una lista linkata monodirezionale (ulinked_list) in ArrayList (arraylist).
 * La lista originale viene eliminata (ma non vengono eliminati i suoi elementi, che sono ovviamente
 * spostati nell'arraylist).
 */
ulinked_list* al_convertToULinkedList(arraylist* l) {
	ulinked_list* ul = malloc(sizeof(ulinked_list));
	if (!ul) {
		MEMORY_ERROR;
	}
	ul->size = l->size;
	for (int i = l->size - 1; i >= 0; i--) {
		ul_insertElementFirst(ul, l->array[i]);
	}
	al_cleanList(l);
	return ul;
}

/**
 * Copia una lista linkata monodirezionale in un arraylist.
 * La lista linkata originale non viene modificata o cancellata.
 */
ulinked_list* al_copyToULinkedList(arraylist* l, void* (*clone)(void*)) {
	return al_convertToULinkedList(al_cloneOrderedList(l, clone));
}

