#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BidirectionalList.h"

#ifndef MEMORY_ERROR
#	define MEMORY_ERROR printf("Error: Cannot allocate memory.\n"); exit(1)
#endif

/**
 * Libreria che permette la gestione di una lista linkata doppiamente.
 * 
 * @author Michele Dusi <michele.dusi.it@ieee.org>
 * 
 */

/* STRUCTURES DEFINITIONS
 *
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
 * 
 */

/** 
 * Inizializzazione della lista vuota. 
 */
blinked_list* bl_initList() {
	blinked_list* new_list = malloc(sizeof(blinked_list));
	if (!new_list) {
		MEMORY_ERROR;
	}
	new_list->size = 0;
	new_list->head = NULL;
	new_list->tail = NULL;
	return new_list;
}

/**
 * Restituisce l'ultimo elemento della lista.
 */
static blinked_list_node* bl_getTail(blinked_list* l) {
	return l->tail;
}

/** 
 * Inserimento di un elemento in testa alla lista.
 */
void bl_insertElementFirst(blinked_list* l, void* new_element_data) {
	blinked_list_node* new_element = malloc(sizeof(blinked_list_node));
	if (!new_element) {
		MEMORY_ERROR;
	}
	new_element->data = new_element_data;
	
	new_element->next = l->head;
	l->head->prev = new_element;
	l->head = new_element;
	
	l->size++;
}

/**
 * Inserimento di un elemento in coda alla lista.
 */
void bl_insertElementLast(blinked_list* l, void* new_element_data) {
	blinked_list_node* new_element = malloc(sizeof(blinked_list_node));
	if (!new_element) {
		MEMORY_ERROR;
	}
	new_element->data = new_element_data;
	
	new_element->prev = l->tail;
	l->tail->next = new_element;
	l->tail = new_element;
	
	l->size++;
}

/**
 * Controlla che la posizione sia valida.
 */
static bool checkPositionValidity(blinked_list* l, int pos) {
	return (pos >= 0 && pos < l->size);
}

/**
 * Inserisce un elemento nella lista alla posizione desiderata.
 * Il primo elemento della lista ha posizione "0".
 * Se viene inserita una posizione superiore al numero di elementi, l'elemento viene inserito in coda.
 * Se viene inserita una posizione negativa, la funzione non viene eseguita.
 */
void bl_insertElementAtPosition(blinked_list* l, void* new_element_data, int pos) {
	if (!checkPositionValidity(l, pos)) {
		printf("Errore: Impossibile inserire un elemento nella posizione data.\n");
		// TODO Error
	} else if (pos == 0) {
		bl_insertElementFirst(l, new_element_data);
	} else if (pos == l->size - 1) {
		bl_insertElementLast(l, new_element_data);
	} else {
		blinked_list_node* new_element = malloc(sizeof(blinked_list_node));
		if (!new_element) {
			MEMORY_ERROR;
		}
		if (pos < l->size / 2) {
			// Scorro dall'inizio
			blinked_list_node* iterator = l->head;
			for (int i = 0; i < pos - 1 && i < l->size - 1; i++) {
				iterator = iterator->next;
			}
			new_element->next = iterator->next;
			new_element->prev = iterator;
			iterator->next = new_element;
			iterator->next->prev = new_element;
			
		} else {
			// Scorro dalla fine
			blinked_list_node* iterator = l->tail;
			for (int i = l->size - 1; i > pos + 1 && i >= 0; i--) {
				iterator = iterator->prev;
			}
			new_element->prev = iterator->prev;
			new_element->next = iterator;
			
			iterator->prev = new_element;
			iterator->prev->next = new_element;
			
		}
		new_element->data = new_element_data;
		l->size++;
	}
}

/**
 * Inserisce tutti gli elementi in coda alla prima lista.
 * Gli elementi da aggiungere vengono passati come "blinked_list*".
 * L'utilizzo di questa funzione provoca la cancellazione della seconda lista, pertanto è
 * sconsigliata se si vuole unire due liste differenti. In sostituzione, è possibile utilizzare
 * la funzione "bl_concatenateTwoLists" che ricopia le liste in questione senza modificare gli originali.
 */
void bl_insertAllElementsLast(blinked_list* l, blinked_list* elements) {
	l->tail->next = elements->head;
	elements->head->prev = l->tail;
	l->size += elements->size;
	free(elements);
}

/**
 * Cancella il primo elemento della lista.
 */
void bl_deleteFirstElement(blinked_list* l) {
	if (l->size != EMPTY_SIZE) {
		l->head = l->head->next;
		free(l->head->prev);
		l->head->prev = NULL;
		l->size--;
	}
}

/**
 * Cancella l'ultimo elemento della lista.
 */
void bl_deleteLastElement(blinked_list* l) {
	if (l->size != EMPTY_SIZE) {
		l->tail = l->tail->prev;
		free(l->tail->next);
		l->tail->next = NULL;
		l->size--;
	}
}


/**
 * Rimuove tutti gli elementi che soddisfano una data condizione.
 */
void bl_deleteElementsByConditions(blinked_list* l, bool (*condition)(void*)) {
	blinked_list_node* iterator = l->head;
	for (int i = 0; i < l->size - 1; i++) {
		if (condition(iterator->next->data)) {
			// Cancellazione di iterator->next
			iterator->next = iterator->next->next;
			free(iterator->next);
			iterator->next->prev = iterator;
			
			l->size--;
		}
		iterator = iterator->next;
	}
	if (condition(l->head)) {
		bl_deleteFirstElement(l);
	} else if (condition(l->tail)) {
		bl_deleteLastElement(l);
	}
}

/**
 * Restituisce il contenuto del primo elemento della lista.
 */
void* bl_getHeadContent(blinked_list* l) {
	return l->head->data;
}

/**
 * Restituisce il contenuto del primo elemento eliminandolo dalla lista.
 */
void* bl_extractHeadContent(blinked_list* l) {
	if (l->size != EMPTY_SIZE) {
		blinked_list_node* aux = l->head;
		l->head = l->head->next;
		free(l->head->prev);
		l->head->prev = NULL;
		return aux->data;
	}
	return NULL;
}

/**
 * Restituisce il contenuto dell'ultimo elemento eliminandolo dalla lista.
 */
void* bl_extractTailContent(blinked_list* l) {
	if (l->size != EMPTY_SIZE) {
		blinked_list_node* aux = l->tail;
		l->tail = l->tail->prev;
		free(l->tail->next);
		l->tail->next = NULL;
		return aux->data;
	}
	return NULL;
}

/**
 * Estrae un elemento alla posizione desiderata, lo cancella dalla lista e lo restituisce come puntatore.
 */
static blinked_list_node* bl_extractNodeAtPosition(blinked_list* l, int pos) {
	if (checkPositionValidity(l, pos)) {
		// Lista VUOTA o pos NON valida
		return NULL;
	} else if (pos == 1) {
		// HEAD
		return bl_extractHeadContent(l);
	} else if (pos == l->size - 1) {
		// TAIL
		return bl_extractTailContent(l);
	} else {
		blinked_list_node* aux;
		if (!new_element) {
			MEMORY_ERROR;
		}
		if (pos < l->size / 2) {
			// Scorro dall'inizio
			blinked_list_node* iterator = l->head;
			for (int i = 0; i < pos - 1 && i < l->size - 1; i++) {
				iterator = iterator->next;
			}
			new_element->next = iterator->next;
			new_element->prev = iterator;
			iterator->next = new_element;
			iterator->next->prev = new_element;
			
		} else {
			// Scorro dalla fine
			blinked_list_node* iterator = l->tail;
			for (int i = l->size - 1; i > pos + 1 && i >= 0; i--) {
				iterator = iterator->prev;
			}
			new_element->prev = iterator->prev;
			new_element->next = iterator;
			
			iterator->prev = new_element;
			iterator->prev->next = new_element;
			
		}
		new_element->data = new_element_data;
		l->size++;
	}
}

void* bl_extractElementAtPosition(blinked_list* l, int pos) {
	return bl_extractNodeAtPosition(l, pos)->data;
}

/**
 * Rimuove un elemento alla posizione desiderata.
 */
void bl_deleteElementAtPosition(blinked_list* l, int pos) {
	free(bl_extractElementAtPosition(l, pos));
}

/**
 * Restituisce il contenuto dell'ultimo elemento della lista.
 */
void* bl_getTailContent(blinked_list* l) {
	if (l->size)
		return bl_getTail(l)->data;
	return NULL;
}

/**
 * Restituisce l'elemento ad una data posizione.
 * Se viene inserita una posizione superiore al numero di elementi presenti o un numero negativo, viene restituito NulL.
 */
static blinked_list_node* bl_getElementAtPosition(blinked_list* l, int pos) {
	if (pos < 0 || pos >= l->size)
		return NULL;
	
	blinked_list_node* iterator = l->head;
	for (int i = 0; i < pos && i < l->size; i++) {
		iterator = iterator->next;
	}
	return iterator;
}

/**
 * Restituisce il contentuto di un elemento alla posizione desiderata.
 */
void* bl_getElementContentAtPosition(blinked_list* l, int pos) {
	return bl_getElementAtPosition(l, pos)->data;
}

/**
 * Restituisce la quantità di elementi presenti nella lista.
 */
int bl_getListSize(blinked_list* l) {
	return l->size;
}

/**
 * Restituisce la posizione dell'elemento corrispondente a quello cercato.
 * Se l'elemento non è presente all'interno della lista, viene restituito il valore -1.
 */
int bl_getElementPosition(blinked_list* l, void* element_content) {
	blinked_list_node* iterator = l->head;
	for (int i = 0; i < l->size; i++) {
		if (iterator->data == element_content) {
			return i;
		}
		iterator = iterator->next;
	}
	return -1;
}

/**
 * Verifica che all'interno della lista sia presente almeno un elemento che soddisfi una data condizione.
 */
bool bl_containsElement(blinked_list* l, bool (*condition)(void*)) {
	blinked_list_node* iterator = l->head;
	for (int i = 0; i < l->size; i++) {
		if (condition(iterator->data))
			return true;
		iterator = iterator->next;
	}
	return false;
}

/**
 * Scambia di posto due elementi della lista, date le loro posizioni.
 */
void bl_swapTwoElements(blinked_list* l, int pos1, int pos2) {
	if (pos1 == pos2 || pos1 >= l->size || pos2 >= l->size) {
		// DAFUQ
	} else {
		if (pos1 > pos2)
			INT_SWAP(pos1, pos2);		// Mi assicuro che pos1 < pos2
		// Scambio i due elementi
		blinked_list_node* aux = bl_extractElementAtPosition(l, pos1);
		bl_insertElementAtPosition(l, bl_extractElementAtPosition(l, pos2 - 1), pos1);
		bl_insertElementAtPosition(l, aux->data, pos2);
	}
}

/**
 * Clona una lista, data in ingresso una funzione per la clonazione del contenuto di un elemento.
 * Garantisce il mantenimento dell'ordine durante il processo.
 */
blinked_list* bl_cloneOrderedList(blinked_list* l, void* (*clone)(void*)) {
	// Inizializzo la nuova lista
	blinked_list* new_list = bl_initList();
	// Inizio la clonazione
	blinked_list_node* aux;
	// Clono la testa
	if (l->size) {
		aux = malloc(sizeof(blinked_list_node));
		if (!aux) {
			MEMORY_ERROR;
		}
		aux->data = clone(bl_getHeadContent(l));
		aux->next = NULL;
		new_list->head = aux;
	}
	// Clono il resto
	blinked_list_node* iterator = l->head;			// Utilizzo un secondo iteratore (il primo in realtà è aux) per evitare di ciclare sulle liste più di una volta.
	blinked_list_node* new_element;
	for (int i = 0; i < l->size; i++) {
		new_element = malloc(sizeof(blinked_list_node));
		if (!new_element) {
			MEMORY_ERROR;
		}
		new_element->data = clone(iterator->data);
		// Aggiorno i puntatori/iteratori
		aux->next = new_element;			// Aux tiene in memoria il penultimo elemento aggiunto alla nuova lista
		aux = aux->next;
		iterator = iterator->next;
	}
	new_element->next = NULL; // Coda
	// Fine
	return new_list;
}

/**
 * Clona una lista, data in ingresso una funzione per la clonazione del contenuto di un elemento.
 * Non garantisce il mantenimento dell'ordine durante il processo, ma permette una maggiore velocità (FORSE). // TODO CONTROLLARE
 * In particolare, a fine esecuzione la lista ottenuta avrà ordine inverso.
 * 
 * @deprecated Use cloneOrderedList instead.
 */
blinked_list* bl_cloneUnorderedList(blinked_list* l, void* (*clone)(void*)) {
	// Inizializzo la nuova lista
	blinked_list* new_list = malloc(sizeof(blinked_list));
	if (!new_list) {
		MEMORY_ERROR;
	}
	new_list->size = 0;
	new_list->head = NULL;
	// Clono gli elementi della lista originaria
	blinked_list_node* iterator = l->head;
	for (int i = 0; i < l->size; i++) {
		bl_insertElementFirst(new_list, clone(iterator->data));
		iterator = iterator->next;
	}
	// Restituisco la lista creata
	return new_list;
}

/**
 * Unisce gli elementi di due liste in un'unica nuova lista.
 * Le liste originali <b>NON</b> vengono modificate.
 * E' possibile personalizzare il processo di clonazione attraverso la funzione <i>clone</i> passata come parametro.
 */
blinked_list* bl_concatenateTwoLists(blinked_list* l1, blinked_list* l2, void* (*clone)(void*)) {
	blinked_list* new_list = bl_cloneOrderedList(l1, clone);
	bl_insertAllElementsLast(new_list, bl_cloneOrderedList(l2, clone));
	return new_list;
}

/**
 * Data una lista e una relazione d'ordine definita sui suoi elementi, la funzione
 * restitutisce il nodo con contenuto "massimo".
 * La relazione deve essere implementata come una funzione che prende in ingresso il contenuto di due nodi, 
 * e li confronta restituendo:
 * - un numero negativo se il primo dato è "minore" del secondo (stando alla relazione).
 * - 0 se i due dati sono considerati uguali dalla relazione d'ordine.
 * - un numero positivo se il primo dato è "maggiore" del secondo (stando alla relazione).
 */
static blinked_list_node* bl_getMinimumElement(blinked_list* l, int (*compare)(void*, void*)) {
	blinked_list_node* iterator = l->head->next;
	blinked_list_node* minimum = l->head;
	for (int i = 1; i < l->size; i++) {
		if (compare(iterator->data, minimum->data) < 0) {
			minimum = iterator;
		}
	}
	return minimum;
}

/**
 * Data una lista e una relazione d'ordine definita sui suoi elementi, la funzione
 * restitutisce l'elemento "minimo".
 * La relazione deve essere implementata come una funzione che prende in ingresso il contenuto di due nodi, 
 * e li confronta restituendo:
 * - un numero negativo se il primo dato è "minore" del secondo (stando alla relazione).
 * - 0 se i due dati sono considerati uguali dalla relazione d'ordine.
 * - un numero positivo se il primo dato è "maggiore" del secondo (stando alla relazione).
 */
void* bl_getMinimumContent(blinked_list* l, int (*compare)(void*, void*)) {
	return bl_getMinimumElement(l, compare)->data;
}

/**
 * Data una lista e una relazione d'ordine definita sui suoi elementi, la funzione
 * restitutisce il nodo con contenuto "massimo".
 * La relazione deve essere implementata come una funzione che prende in ingresso il contenuto di due nodi, 
 * e li confronta restituendo:
 * - un numero negativo se il primo dato è "minore" del secondo (stando alla relazione).
 * - 0 se i due dati sono considerati uguali dalla relazione d'ordine.
 * - un numero positivo se il primo dato è "maggiore" del secondo (stando alla relazione).
 */
static blinked_list_node* bl_getMaximumElement(blinked_list* l, int (*compare)(void*, void*)) {
	blinked_list_node* iterator = l->head->next;
	blinked_list_node* maximum = l->head;
	for (int i = 1; i < l->size; i++) {
		if (compare(iterator->data, maximum->data) > 0) {
			maximum = iterator;
		}
	}
	return maximum;
}

/**
 * Data una lista e una relazione d'ordine definita sui suoi elementi, la funzione
 * restitutisce l'elemento "massimo".
 * La relazione deve essere implementata come una funzione che prende in ingresso il contenuto di due nodi, 
 * e li confronta restituendo:
 * - un numero negativo se il primo dato è "minore" del secondo (stando alla relazione).
 * - 0 se i due dati sono considerati uguali dalla relazione d'ordine.
 * - un numero positivo se il primo dato è "maggiore" del secondo (stando alla relazione).
 */
void* bl_getMaximumContent(blinked_list* l, int (*compare)(void*, void*)) {
	return bl_getMaximumElement(l, compare)->data;
}

/**
 * Restituisce la sottolista che parte dall'elemento di indice start_pos all'elemento di end_pos.
 * L'elemento end_pos è <emph>escluso</emph>, mentre viene incluso l'elemento start_pos.
 * 
 * <i>NOTA:</i> Non viene creata una nuova lista, gli elementi della lista originaria non vengono modificati.
 * Pertanto un qualsiasi cambiamento alla lista originaria può provocare modifiche alla sottolista, e viceversa.
 * 
 * <i>NOTA:</i>Si consiglia di non fare operazioni sugli estremi della sottolista. Questa funzione restituisce una lista
 * comoda per operazioni di lettura o, al massimo, inserimento/rimozione <emph>al centro</emph> della sottolista.
 */
blinked_list* bl_getSubList(blinked_list* l, int start_pos, int end_pos) {
	blinked_list* sublist = malloc(sizeof(blinked_list));
	if (!sublist) {
		MEMORY_ERROR;
	}
	sublist->size = end_pos - start_pos;
	sublist->head = bl_getElementAtPosition(l, start_pos);
	return sublist;
}

/**
 * Restituisce una sottolista che parte dall'elemento di indice start_pos fino all'elemento di indice end_pos;
 * La lista originale non viene modificata, e ogni singolo elemento viene clonato dalla funzione passata come parametro.
 */
blinked_list* bl_cloneSubList(blinked_list* l, int start_pos, int end_pos, void* (*clone)(void*)) {
	return bl_cloneOrderedList(bl_getSubList(l, start_pos, end_pos), clone);
}

/**
 * Ordina una lista in modo <i>crescente</i> secondo una relazione d'ordine definita dall'utente e passata come parametro.
 * La relazione deve essere implementata come una funzione che prende in ingresso il contenuto di due nodi, 
 * e li confronta restituendo:
 * - un numero negativo se il primo dato è "minore" del secondo (stando alla relazione).
 * - 0 se i due dati sono considerati uguali dalla relazione d'ordine.
 * - un numero positivo se il primo dato è "maggiore" del secondo (stando alla relazione).
 */
void bl_sortByOrder(blinked_list* l, int (*compare)(void*, void*)) {
	// TODODODODODODODODODODODODODODODOD
}

/**
 * Restituisce una stringa che rappresenta gli elementi contenuti all'interno della lista.
 * Per rappresentare ogni singolo nodo viene passata come parametro la funzione che converte in stringa il contenuto
 * di un elemento. E' necessario fornire anche la dimensione massima della stringa di un singolo elemento.
 */
char* bl_listToString(blinked_list* l, char* (*toString)(void*)) {
	// MOLTO PROBABILMENTE (aka: quasi sicuramente) CONTIENE ERRORI.
	char* s;
	// STRING_TITLE_LENGTH + max_data_length * l->size
	int max_data_length = 20; // TODO Allocazione dinamica della memoria
	s = malloc(sizeof(STRING_TITLE_LENGTH + max_data_length * l->size));
	if (!s) {
		MEMORY_ERROR;
	}
	sprintf(s, STRING_TITLE, l->size);
	blinked_list_node* iterator = l->head;
	for (int i = 0; i < l->size; i++) {
		strcat(s, toString(iterator->data));
		iterator = iterator->next;
	}
	return s;
}
