#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

/**
 * Libreria che generalizza il concetto di lista permettendo la scelta automatica in funzione dell'implementazione interna.
 * L'utente è tenuto a specificare quale implementazione intende utilizzare (a seconda delle sue esigenze), scegliendo
 * fra quelle disponibili al momento:
 * 	- Arraylist [al] = implementato con un array interno.
 * 	- LinkedList [ul] = implementato con una lista linkata.
 * 	
 * Per intenderci, questa è la "classe wrapper" che fa da "padre" alle "classi figlie" ArrayList e UnidirectionalLinkedList.
 * 
 * @author Michele Dusi <michele.dusi.it@ieee.org>
 * 
 */

list* initList(l_type chosen_type) {
	list* l = malloc(sizeof(list));
	switch (chosen_type) {
		case ul:
			l->genericlist.ul = ul_initList();
			break;
		case bl:
			l->genericlist.bl = bl_initList();
			break;
		case al:
			l->genericlist.al = al_initList();
			break;
		default:
			TYPE_ERROR;
	}
	l->type = chosen_type;
	return l;
}

void cleanList(list* l) {
	switch (l->type) {
		case ul:
			ul_cleanList(l->genericlist.ul);
			break;
		case bl:
			bl_cleanList(l->genericlist.bl);
			break;
		case al:
			al_cleanList(l->genericlist.al);
			break;
		default:
			TYPE_ERROR;
	}
	free(l);
}

void purgeList(list* l) {
	switch (l->type) {
		case ul:
			ul_purgeList(l->genericlist.ul);
			break;
		case bl:
			bl_purgeList(l->genericlist.bl);
			break;
		case al:
			al_purgeList(l->genericlist.al);
			break;
		default:
			TYPE_ERROR;
	}
	free(l);
}

void insertElementFirst(list* l, void* new_element_data) {
	switch (l->type) {
		case ul:
			ul_insertElementFirst(l->genericlist.ul, new_element_data);
			break;
		case bl:
			bl_insertElementFirst(l->genericlist.bl, new_element_data);
			break;
		case al:
			al_insertElementFirst(l->genericlist.al, new_element_data);
			break;
		default:
			TYPE_ERROR;
	}
}

void insertElementLast(list* l, void* new_element_data) {
	switch (l->type) {
		case ul:
			ul_insertElementLast(l->genericlist.ul, new_element_data);
			break;
		case bl:
			bl_insertElementLast(l->genericlist.bl, new_element_data);
			break;
		case al:
			al_insertElementLast(l->genericlist.al, new_element_data);
			break;
		default:
			TYPE_ERROR;
	}
}

void insertElementAtPosition(list* l, void* new_element_data, int pos)  {
	switch (l->type) {
		case ul:
			ul_insertElementAtPosition(l->genericlist.ul, new_element_data, pos);
			break;
		case bl:
			bl_insertElementAtPosition(l->genericlist.bl, new_element_data, pos);
			break;
		case al:
			al_insertElementAtPosition(l->genericlist.al, new_element_data, pos);
			break;
		default:
			TYPE_ERROR;
	}
}

void deleteFirstElement(list* l) {
	switch (l->type) {
		case ul:
			ul_deleteFirstElement(l->genericlist.ul);
			break;
		case bl:
			bl_deleteFirstElement(l->genericlist.bl);
			break;
		case al:
			al_deleteFirstElement(l->genericlist.al);
			break;
		default:
			TYPE_ERROR;
	}
}

void deleteLastElement(list* l) {
	switch (l->type) {
		case ul:
			ul_deleteLastElement(l->genericlist.ul);
			break;
		case bl:
			bl_deleteLastElement(l->genericlist.bl);
			break;
		case al:
			al_deleteLastElement(l->genericlist.al);
			break;
		default:
			TYPE_ERROR;
	}
}

void deleteElementAtPosition(list* l, int pos) {
	switch (l->type) {
		case ul:
			ul_deleteElementAtPosition(l->genericlist.ul, pos);
			break;
		case bl:
			bl_deleteElementAtPosition(l->genericlist.bl, pos);
			break;
		case al:
			al_deleteElementAtPosition(l->genericlist.al, pos);
			break;
		default:
			TYPE_ERROR;
	}
}
void deleteElementsByConditions(list* l, bool (*condition)(void*)) {
	switch (l->type) {
		case ul:
			ul_deleteElementsByConditions(l->genericlist.ul, condition);
			break;
		case bl:
			bl_deleteElementsByConditions(l->genericlist.bl, condition);
			break;
		case al:
			al_deleteElementsByConditions(l->genericlist.al, condition);
			break;
		default:
			TYPE_ERROR;
	}
}

void* getHeadContent(list* l) {
	void* content = NULL;
	switch (l->type) {
		case ul:
			content = ul_getHeadContent(l->genericlist.ul);
			break;
		case bl:
			content = bl_getHeadContent(l->genericlist.bl);
			break;
		case al:
			content = al_getHeadContent(l->genericlist.al);
			break;
		default:
			TYPE_ERROR;
	}
	return content;
}

void* extractHeadContent(list* l) {
	void* content = NULL;
	switch (l->type) {
		case ul:
			content = ul_extractHeadContent(l->genericlist.ul);
			break;
		case bl:
			content = bl_extractHeadContent(l->genericlist.bl);
			break;
		case al:
			content = al_extractHeadContent(l->genericlist.al);
			break;
		default:
			TYPE_ERROR;
	}
	return content;
}

void* extractElementAtPosition(list* l, int pos) {
	void* content = NULL;
	switch (l->type) {
		case ul:
			content = ul_extractElementAtPosition(l->genericlist.ul, pos);
			break;
		case bl:
			content = bl_extractElementAtPosition(l->genericlist.bl, pos);
			break;
		case al:
			content = al_extractElementAtPosition(l->genericlist.al, pos);
			break;
		default:
			TYPE_ERROR;
	}
	return content;
}

void* getTailContent(list* l) {
	void* content = NULL;
	switch (l->type) {
		case ul:
			content = ul_getTailContent(l->genericlist.ul);
			break;
		case bl:
			content = bl_getTailContent(l->genericlist.bl);
			break;
		case al:
			content = al_getTailContent(l->genericlist.al);
			break;
		default:
			TYPE_ERROR;
	}
	return content;
}

void* getElementContentAtPosition(list* l, int pos) {
	void* content = NULL;
	switch (l->type) {
		case ul:
			content = ul_getElementContentAtPosition(l->genericlist.ul, pos);
			break;
		case bl:
			content = bl_getElementContentAtPosition(l->genericlist.bl, pos);
			break;
		case al:
			content = al_getElementContentAtPosition(l->genericlist.al, pos);
			break;
		default:
			TYPE_ERROR;
	}
	return content;
}

int getListSize(list* l) {
	switch (l->type) {
		case ul:
			return ul_getListSize(l->genericlist.ul);
		case bl:
			return bl_getListSize(l->genericlist.bl);
		case al:
			return al_getListSize(l->genericlist.al);
		default:
			TYPE_ERROR;
	}
}

int getElementPosition(list* l, void* element_content) {
	switch (l->type) {
		case ul:
			return ul_getElementPosition(l->genericlist.ul, element_content);
		case bl:
			return bl_getElementPosition(l->genericlist.bl, element_content);
		case al:
			return al_getElementPosition(l->genericlist.al, element_content);
		default:
			TYPE_ERROR;
	}
}

bool containsElement(list* l, bool (*condition)(void*)) {
	switch (l->type) {
		case ul:
			return ul_containsElement(l->genericlist.ul, condition);
		case bl:
			return bl_containsElement(l->genericlist.bl, condition);
		case al:
			return al_containsElement(l->genericlist.al, condition);
		default:
			TYPE_ERROR;
	}
}

void swapTwoElements(list* l, int pos1, int pos2) {
	switch (l->type) {
		case ul:
			ul_swapTwoElements(l->genericlist.ul, pos1, pos2);
			break;
		case bl:
			bl_swapTwoElements(l->genericlist.bl, pos1, pos2);
			break;
		case al:
			al_swapTwoElements(l->genericlist.al, pos1, pos2);
			break;
		default:
			TYPE_ERROR;
	}
}

list* cloneOrderedList(list* l, void* (*clone)(void*)) {
	list* cloned_list = malloc(sizeof(list));
	cloned_list->type = l->type;
	switch (l->type) {
		case ul:
			cloned_list->genericlist.ul = ul_cloneOrderedList(l->genericlist.ul, clone);
			break;
		case bl:
			cloned_list->genericlist.bl = bl_cloneOrderedList(l->genericlist.bl, clone);
			break;
		case al:
			cloned_list->genericlist.al = al_cloneOrderedList(l->genericlist.al, clone);
			break;
		default:
			TYPE_ERROR;
	}
	return cloned_list;
}

list* concatenateTwoLists(list* l1, list* l2, void* (*clone)(void*)) {
	list* cloned_list = malloc(sizeof(list));
	if (l1->type == l2->type) {
		cloned_list->type = l1->type;
	} else {
		// ERRORE
		printf("Error: this library does not support list merging with different list types.\n");
		exit(1);
	}
	switch (cloned_list->type) {
		case ul:
			cloned_list->genericlist.ul = ul_concatenateTwoLists(l1->genericlist.ul, l2->genericlist.ul, clone);
			break;
		case bl:
			cloned_list->genericlist.bl = bl_concatenateTwoLists(l1->genericlist.bl, l2->genericlist.bl, clone);
			break;
		case al:
			cloned_list->genericlist.al = al_concatenateTwoLists(l1->genericlist.al, l2->genericlist.al, clone);
			break;
		default:
			TYPE_ERROR;
	}
	return cloned_list;
}

void* getMinimumContent(list* l, int (*compare)(void*, void*)) {
	void* content = NULL;
	switch (l->type) {
		case ul:
			content = ul_getMinimumContent(l->genericlist.ul, compare);
			break;
		case bl:
			content = bl_getMinimumContent(l->genericlist.bl, compare);
			break;
		case al:
			content = al_getMinimumContent(l->genericlist.al, compare);
			break;
		default:
			TYPE_ERROR;
	}
	return content;
}

void* getMaximumContent(list* l, int (*compare)(void*, void*)) {
	void* content = NULL;
	switch (l->type) {
		case ul:
			content = ul_getMaximumContent(l->genericlist.ul, compare);
			break;
		case bl:
			content = bl_getMaximumContent(l->genericlist.bl, compare);
			break;
		case al:
			content = al_getMaximumContent(l->genericlist.al, compare);
			break;
		default:
			TYPE_ERROR;
	}
	return content;
}

list* getSubList(list* l, int start_pos, int end_pos, void* (*clone)(void*)) {
	list* sublist = malloc(sizeof(list));
	sublist->type = l->type;
	switch (l->type) {
		case ul:
			sublist->genericlist.ul = ul_getSubList(l->genericlist.ul, start_pos, end_pos);
			break;
		case bl:
			sublist->genericlist.bl = bl_getSubList(l->genericlist.bl, start_pos, end_pos);
			break;
		case al:
			sublist->genericlist.al = al_getSubList(l->genericlist.al, start_pos, end_pos);
			break;
		default:
			TYPE_ERROR;
	}
	return sublist;
}

list* cloneSubList(list* l, int start_pos, int end_pos, void* (*clone)(void*)) {
	list* sublist = malloc(sizeof(list));
	sublist->type = l->type;
	switch (l->type) {
		case ul:
			sublist->genericlist.ul = ul_cloneSubList(l->genericlist.ul, start_pos, end_pos, clone);
			break;
		case bl:
			sublist->genericlist.bl = bl_cloneSubList(l->genericlist.bl, start_pos, end_pos, clone);
			break;
		case al:
			sublist->genericlist.al = al_cloneSubList(l->genericlist.al, start_pos, end_pos, clone);
			break;
		default:
			TYPE_ERROR;
	}
	return sublist;
}

void sortByOrder(list* l, int (*compare)(void*, void*)) {
	switch (l->type) {
		case ul:
			ul_sortByOrder(l->genericlist.ul, compare);
			break;
		case bl:
			bl_sortByOrder(l->genericlist.bl, compare);
			break;
		case al:
			al_sortByOrder(l->genericlist.al, compare);
			break;
		default:
			TYPE_ERROR;
	}
}

char* listToString(list* l, char* (*toStringFunction)(void*)) {
	switch (l->type) {
		case ul:
			return ul_listToString(l->genericlist.ul, toStringFunction);
			break;
		case bl:
			return bl_listToString(l->genericlist.bl, toStringFunction);
			break;
		case al:
			return al_listToString(l->genericlist.al, toStringFunction);
			break;
		default:
			TYPE_ERROR;
	}
	return NULL;
}

/* Conversione */

/**
 * A causa dell'implementazione della struct "list", essa contiene il riferimento ad un arraylist o ad una linkedlist (singola o doppia).
 * E' possibile modificare il tipo interno della lista attraverso questa funzione, per rendere più semplici alcune operazioni
 * su particolari tipi di liste.
 */
void convertInnerListTypeTo(list* l, l_type new_type) {
	switch (new_type) {
		// Analizzo il tipo di DESTINAZIONE:
		case ul:
			// Conversione in UL
			switch (l->type) {
				case ul:
					// Identity
					break;
				case bl:
					l->genericlist.ul = bl_convertToULinkedList(l->genericlist.bl);
					break;
				case al:
					l->genericlist.ul = al_convertToULinkedList(l->genericlist.al);
					break;
			}
			l->type = ul;
			break;
		case bl:
			// Conversione in BL
			switch (l->type) {
				case ul:
					l->genericlist.ul = bl_convertToULinkedList(l->genericlist.bl);
					break;
				case bl:
					// Identity
					break;
				case al:
					l->genericlist.ul = bl_convertToULinkedList(l->genericlist.bl);
					break;
			}
			l->type = bl;
			break;
		case al:
			// Conversione in AL
			switch (l->type) {
				case ul:
					l->genericlist.al = ul_convertToArrayList(l->genericlist.ul);
					break;
				case bl:
					l->genericlist.al = bl_convertToArrayList(l->genericlist.bl);
					break;
				case al:
					// Identity
					break;
			}
			l->type = al;
			break;
		default:
			TYPE_ERROR;
	}
	
	// Ho due switch innestati.
	// TODO -> matrice di puntatori a funzione dove il primo indice della cella indica il tipo di provenienza,
	// il secondo indice il tipo di destinazione (FUTURA IMPLEMENTAZIONE).
}






