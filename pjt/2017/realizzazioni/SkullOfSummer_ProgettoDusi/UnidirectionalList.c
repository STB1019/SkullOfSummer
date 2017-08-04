#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "UnidirectionalList.h"

#ifndef MEMORY_ERROR
#	define MEMORY_ERROR printf("Error: Cannot allocate memory.\n"); exit(1)
#endif

/**
 * Libreria che permette la gestione di una lista linkata.
 * 
 * @author Michele Dusi <michele.dusi.it@ieee.org>
 * 
 */

/** 
 * Inizializzazione della lista vuota. 
 */
ulinked_list* ul_initList() {
	ulinked_list* new_list = malloc(sizeof(ulinked_list));
	if (new_list == NULL) {
		MEMORY_ERROR;
	}
	new_list->size = 0;
	new_list->head = NULL;
	return new_list;
}

/**
 * Restituisce l'ultimo elemento della lista.
 */
static ulinked_list_node* ul_getTail(ulinked_list* l) {
	if (l->size == 0)
		return NULL; // Caso in cui la lista sia vuota
		
	ulinked_list_node* iterator = l->head;
	for (int i = 1; i < l->size; i++) {
		iterator = iterator->next;
	}
	return iterator;
}

/** 
 * Inserimento di un elemento in testa alla lista.
 */
void ul_insertElementFirst(ulinked_list* l, void* new_element_data) {
	ulinked_list_node* new_element = malloc(sizeof(ulinked_list_node));
	if (!new_element) {
		MEMORY_ERROR;
	}
	new_element->data = new_element_data;
	new_element->next = l->head;
	l->head = new_element;
	l->size++;
}

/**
 * Inserimento di un elemento in coda alla lista.
 */
void ul_insertElementLast(ulinked_list* l, void* new_element_data) {
	ulinked_list_node* new_element = malloc(sizeof(ulinked_list_node));
	if (!new_element) {
		MEMORY_ERROR;
	}
	new_element->data = new_element_data;
	new_element->next = NULL;
	
	if (l->size == EMPTY_SIZE)
		l->head = new_element;
	else
		ul_getTail(l)->next = new_element;
	l->size++;
}

/**
 * Inserisce un elemento nella lista alla posizione desiderata.
 * Il primo elemento della lista ha posizione "0".
 * Se viene inserita una posizione superiore al numero di elementi, l'elemento viene inserito in coda.
 * Se viene inserita una posizione negativa, la funzione non viene eseguita.
 */
void ul_insertElementAtPosition(ulinked_list* l, void* new_element_data, int pos) {
	if (pos < 0) {
		// TODO ERRORE
	} else if (pos == 0) {
		ul_insertElementFirst(l, new_element_data);
	} else {
		ulinked_list_node* new_element = malloc(sizeof(ulinked_list_node));
		if (!new_element) {
			MEMORY_ERROR;
		}
		ulinked_list_node* iterator = l->head;
		for (int i = 0; i < pos - 1 && i < l->size - 1; i++) {
			iterator = iterator->next;
		}
		new_element->data = new_element_data;
		new_element->next = iterator->next;
		iterator->next = new_element;
		l->size++;
	}
}

/**
 * Inserisce tutti gli elementi in coda alla prima lista.
 * Gli elementi da aggiungere vengono passati come "ulinked_list*".
 * L'utilizzo di questa funzione provoca la cancellazione della seconda lista, pertanto è
 * sconsigliata se si vuole unire due liste differenti. In sostituzione, è possibile utilizzare
 * la funzione "ul_concatenateTwoLists" che ricopia le liste in questione senza modificare gli originali.
 */
void ul_insertAllElementsLast(ulinked_list* l, ulinked_list* elements) {
	ul_getTail(l)->next = elements->head;
	l->size += elements->size;
	free(elements);
}

/**
 * Cancella il primo elemento della lista.
 */
void ul_deleteFirstElement(ulinked_list* l) {
	if (l->size != EMPTY_SIZE) {
		ulinked_list_node* aux = l->head;
		l->head = l->head->next;
		free(aux);
		l->size--;
	}
}

/**
 * Cancella l'ultimo elemento della lista.
 */
void ul_deleteLastElement(ulinked_list* l) {
	if (l->size == EMPTY_SIZE) {
		// TODO BOH
		// Non succede nulla?
	} else if (l->size == 1) {
		free(l->head);
		l->head = NULL;
		l->size--;
	} else {
		ulinked_list_node* iterator = l->head;
		for (int i = 1; i < l->size - 1; i++) {
			iterator->next = iterator->next->next;
		}
		free(iterator->next);
		iterator->next = NULL;
		l->size--;
	}
}


/**
 * Rimuove tutti gli elementi che soddisfano una data condizione.
 */
void ul_deleteElementsByConditions(ulinked_list* l, bool (*condition)(void*)) {
	ulinked_list_node* iterator = l->head;
	ulinked_list_node* aux = NULL;
	while(iterator->next != NULL) {
		if (condition(iterator->next->data)) {
			// Cancellazione di iterator-terminal char>next
			aux = iterator->next;
			iterator->next = iterator->next->next;
			free(aux);
			l->size--;
		}
		iterator = iterator->next;
	}
	if (condition(l->head)) {
		ul_deleteFirstElement(l);
	}
}

/**
 * Restituisce il contenuto del primo elemento della lista.
 */
void* ul_getHeadContent(ulinked_list* l) {
	return l->head->data;
}

/**
 * Restituisce il contenuto del primo elemento.
 */
void* ul_extractHeadContent(ulinked_list* l) {
	if (l->size) {
		ulinked_list_node* aux = l->head;
		l->head = l->head->next;
		return aux->data;
	}
	return NULL;
}

/**
 * Estrae un elemento alla posizione desiderata, lo cancella dalla lista e lo restituisce come puntatore.
 */
static ulinked_list_node* ul_extractNodeAtPosition(ulinked_list* l, int pos) {
	if (pos < 0 || pos >= l->size) { // Così sto gestendo anche il caso "lista vuota"
		// TODO Errore
		return NULL;
	} else if (pos == 1) {
		ulinked_list_node* aux = l->head;
		l->head = l->head->next;
		l->size--;
		return aux;
	} else {
		ulinked_list_node* iterator = l->head;
		for (int i = 0; i < pos - 1 && i < l->size - 1; i++) {
			iterator = iterator->next;
		}
		ulinked_list_node* aux = iterator->next;
		iterator->next = iterator->next->next;
		l->size--;
		return aux;
	}
}

void* ul_extractElementAtPosition(ulinked_list* l, int pos) {
	return ul_extractNodeAtPosition(l, pos)->data;
}

/**
 * Rimuove un elemento alla posizione desiderata.
 */
void ul_deleteElementAtPosition(ulinked_list* l, int pos) {
	free(ul_extractElementAtPosition(l, pos));
}

/**
 * Restituisce il contenuto dell'ultimo elemento della lista.
 */
void* ul_getTailContent(ulinked_list* l) {
	if (l->size)
		return ul_getTail(l)->data;
	return NULL;
}

/**
 * Restituisce l'elemento ad una data posizione.
 * Se viene inserita una posizione superiore al numero di elementi presenti o un numero negativo, viene restituito NulL.
 */
static ulinked_list_node* ul_getElementAtPosition(ulinked_list* l, int pos) {
	if (pos < 0 || pos >= l->size)
		return NULL;
	
	ulinked_list_node* iterator = l->head;
	for (int i = 0; i < pos && i < l->size; i++) {
		iterator = iterator->next;
	}
	return iterator;
}

/**
 * Restituisce il contentuto di un elemento alla posizione desiderata.
 */
void* ul_getElementContentAtPosition(ulinked_list* l, int pos) {
	return ul_getElementAtPosition(l, pos)->data;
}

/**
 * Restituisce la quantità di elementi presenti nella lista.
 */
int ul_getListSize(ulinked_list* l) {
	return l->size;
}

/**
 * Restituisce la posizione dell'elemento corrispondente a quello cercato.
 * Se l'elemento non è presente all'interno della lista, viene restituito il valore -1.
 */
int ul_getElementPosition(ulinked_list* l, void* element_content) {
	ulinked_list_node* iterator = l->head;
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
bool ul_containsElement(ulinked_list* l, bool (*condition)(void*)) {
	ulinked_list_node* iterator = l->head;
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
void ul_swapTwoElements(ulinked_list* l, int pos1, int pos2) {
	if (pos1 == pos2 || pos1 >= l->size || pos2 >= l->size) {
		// DAFUQ
	} else {
		if (pos1 > pos2)
			INT_SWAP(pos1, pos2);		// Mi assicuro che pos1 < pos2
		// Scambio i due elementi
		ulinked_list_node* aux = ul_extractElementAtPosition(l, pos1);
		ul_insertElementAtPosition(l, ul_extractElementAtPosition(l, pos2 - 1), pos1);
		ul_insertElementAtPosition(l, aux->data, pos2);
	}
}

/**
 * Clona una lista, data in ingresso una funzione per la clonazione del contenuto di un elemento.
 * Garantisce il mantenimento dell'ordine durante il processo.
 */
ulinked_list* ul_cloneOrderedList(ulinked_list* l, void* (*clone)(void*)) {
	// Inizializzo la nuova lista
	ulinked_list* new_list = ul_initList();
	// Inizio la clonazione
	ulinked_list_node* aux;
	// Clono la testa
	if (l->size) {
		aux = malloc(sizeof(ulinked_list_node));
		if (!aux) {
			MEMORY_ERROR;
		}
		aux->data = clone(ul_getHeadContent(l));
		aux->next = NULL;
		new_list->head = aux;
	}
	// Clono il resto
	ulinked_list_node* iterator = l->head;			// Utilizzo un secondo iteratore (il primo in realtà è aux) per evitare di ciclare sulle liste più di una volta.
	ulinked_list_node* new_element;
	for (int i = 0; i < l->size; i++) {
		new_element = malloc(sizeof(ulinked_list_node));
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
ulinked_list* ul_cloneUnorderedList(ulinked_list* l, void* (*clone)(void*)) {
	// Inizializzo la nuova lista
	ulinked_list* new_list = malloc(sizeof(ulinked_list));
	if (!new_list) {
		MEMORY_ERROR;
	}
	new_list->size = 0;
	new_list->head = NULL;
	// Clono gli elementi della lista originaria
	ulinked_list_node* iterator = l->head;
	for (int i = 0; i < l->size; i++) {
		ul_insertElementFirst(new_list, clone(iterator->data));
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
ulinked_list* ul_concatenateTwoLists(ulinked_list* l1, ulinked_list* l2, void* (*clone)(void*)) {
	ulinked_list* new_list = ul_cloneOrderedList(l1, clone);
	ul_insertAllElementsLast(new_list, ul_cloneOrderedList(l2, clone));
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
static ulinked_list_node* ul_getMinimumElement(ulinked_list* l, int (*compare)(void*, void*)) {
	ulinked_list_node* iterator = l->head->next;
	ulinked_list_node* minimum = l->head;
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
void* ul_getMinimumContent(ulinked_list* l, int (*compare)(void*, void*)) {
	return ul_getMinimumElement(l, compare)->data;
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
static ulinked_list_node* ul_getMaximumElement(ulinked_list* l, int (*compare)(void*, void*)) {
	ulinked_list_node* iterator = l->head->next;
	ulinked_list_node* maximum = l->head;
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
void* ul_getMaximumContent(ulinked_list* l, int (*compare)(void*, void*)) {
	return ul_getMaximumElement(l, compare)->data;
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
ulinked_list* ul_getSubList(ulinked_list* l, int start_pos, int end_pos) {
	ulinked_list* sublist = malloc(sizeof(ulinked_list));
	if (!sublist) {
		MEMORY_ERROR;
	}
	sublist->size = end_pos - start_pos;
	sublist->head = ul_getElementAtPosition(l, start_pos);
	return sublist;
}

/**
 * Restituisce una sottolista che parte dall'elemento di indice start_pos fino all'elemento di indice end_pos;
 * La lista originale non viene modificata, e ogni singolo elemento viene clonato dalla funzione passata come parametro.
 */
ulinked_list* ul_cloneSubList(ulinked_list* l, int start_pos, int end_pos, void* (*clone)(void*)) {
	return ul_cloneOrderedList(ul_getSubList(l, start_pos, end_pos), clone);
}

/**
 * Ordina una lista in modo <i>crescente</i> secondo una relazione d'ordine definita dall'utente e passata come parametro.
 * La relazione deve essere implementata come una funzione che prende in ingresso il contenuto di due nodi, 
 * e li confronta restituendo:
 * - un numero negativo se il primo dato è "minore" del secondo (stando alla relazione).
 * - 0 se i due dati sono considerati uguali dalla relazione d'ordine.
 * - un numero positivo se il primo dato è "maggiore" del secondo (stando alla relazione).
 */
void ul_sortByOrder(ulinked_list* l, int (*compare)(void*, void*)) {
	// TODODODODODODODODODODODODODODODOD
}

/**
 * Restituisce una stringa che rappresenta gli elementi contenuti all'interno della lista.
 * Per rappresentare ogni singolo nodo viene passata come parametro la funzione che converte in stringa il contenuto
 * di un elemento. E' necessario fornire anche la dimensione massima della stringa di un singolo elemento.
 */
char* ul_listToString(ulinked_list* l, char* (*toString)(void*)) {
	// MOLTO PROBABILMENTE (aka: quasi sicuramente) CONTIENE ERRORI.
	char* s;
	// STRING_TITLE_LENGTH + max_data_length * l->size
	int max_data_length = 20; // TODO Allocazione dinamica della memoria
	s = malloc(sizeof(STRING_TITLE_LENGTH + max_data_length * l->size));
	if (!s) {
		MEMORY_ERROR;
	}
	sprintf(s, STRING_TITLE, l->size);
	ulinked_list_node* iterator = l->head;
	for (int i = 0; i < l->size; i++) {
		strcat(s, toString(iterator->data));
		iterator = iterator->next;
	}
	return s;
}



