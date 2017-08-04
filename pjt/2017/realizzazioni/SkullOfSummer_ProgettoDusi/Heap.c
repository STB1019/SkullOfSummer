#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "Heap.h"

#define LIST_TYPE al

#define ARRAY_TO_HEAP(x) (x + 1)
#define HEAP_TO_ARRAY(x) (x - 1)

/**
 * Libreria che permette la creazione e gestione di un max-heap binario, implementato come arraylist.
 * 
 * @author Michele Dusi <michele.dusi.it@ieee.org>
 * 
 * <i>NOTA:</i> l'heap in questione è formalizzato unicamente come max-heap.
 * Questo significa che il nodo padre ha valore maggiore del nodo figlio. Per ottenere il min-heap
 * corrispondente, è sufficiente invertire l'output della funzione di comparazione.
 * 
 * <i>NOTA:</i> La numerazione degli elementi dell'Heap inizia da 1. Questo è dovuto alla facilità di implementazione
 * che si può ottenere adottando questo particolare accorgimento.
 * Dato un nodo [i], infatti, il nodo padre avrà indice (int)[i / 2], i nodi figli [i * 2] e [i * 2 + 1].
 */

/*
typedef struct binaryheap {
	list* genericlist;
	int (*comparefunction)(void*, void*);
} binaryheap;
*/

/**
 * Inizializza un max-heap binario e ne restituisce un puntatore.
 * Notare che la numerazione dell'heap comincia (con la radice) dal valore 1.
 */
binaryheap* bh_initHeap(int (*compare)(void*, void*)) {
	binaryheap* new_binaryheap = malloc(sizeof(binaryheap));
	if (!new_binaryheap) {
		printf("Error: OutOfMemory");
		exit(1);
	}
	new_binaryheap->genericlist = initList((l_type) LIST_TYPE);
	new_binaryheap->comparefunction = compare;
	return new_binaryheap;
}

/**
 * Elimina l'heap, ripulendo la memoria occupata dalla lista interna.
 * 
 * (!) Non elimina gli oggetti contenuti in esso; questo significa che sarà compito dell'utilizzatore
 * richiamare <i>free()</i> sulla porzione di memoria che li contiene.
 * (!) Non elimina la funzione utilizzata come comparatore degli elementi.
 */
void bh_cleanHeap(binaryheap* h) {
	cleanList(h->genericlist);
	free(h->genericlist);
	free(h);
}

/**
 * Elimina l'heap, ripulendo la memoria occupata dalla lista interna, dagli oggetti contenuti in essa
 * e dalla funzione comparatrice.
 * Questo significa che tutti gli elementi che compongono l'heap verranno irrimediabilmente persi, e non
 * potranno essere recuperati.
 */
void bh_purgeHeap(binaryheap* h) {
	purgeList(h->genericlist);
	free(h->genericlist);
	free(h->comparefunction);
	free(h);
}

/**
 * Inserisce un elemento all'interno dell'heap.
 * Non è possibile definire la posizione personalizzata in cui inserirlo poiché -per stessa implementazione dell'heap-
 * è la struttura stessa a definire la posizione di un elemento.
 */
void bh_insertElement(binaryheap* h, void* new_element_data) {
	insertElementLast(h->genericlist, new_element_data);
	int index = getListSize(h->genericlist);
	while (index > 1) {
		if (h->comparefunction(new_element_data, getElementContentAtPosition(h->genericlist, index / 2 - 1))) {
			swapTwoElements(h->genericlist, index / 2 - 1, index - 1);
			index /= 2;
		}
	}
}

/**
 * Restituisce il numero di elementi contenuti all'interno dell'Heap.
 */
int bh_getHeapSize(binaryheap* h) {
	return getListSize(h->genericlist);
}

/**
 * Restituisce la posizione di un elemento presente nell'heap.
 * Se assente, viene restituito il valore -1;
 */
int bh_getElementPosition(binaryheap* h, void* element_to_find) {
	return getElementPosition(h->genericlist, element_to_find);
}

/**
 * Prende in ingresso la posizione <i>relativa all'heap</i>.
 */
void bh_deleteElementAtPosition(binaryheap* h, int pos) {
	while (HEAP_TO_ARRAY(pos) < getListSize(h->genericlist)) {
		// Controllo che non sia alla fine (aka: che abbia figli)
		if (pos * 2 + 1 > getListSize(h->genericlist)) {
			// Non ho figli
			swapTwoElements(h->genericlist, HEAP_TO_ARRAY(pos), HEAP_TO_ARRAY(getListSize(h->genericlist)));	// L'elemento da eliminare va scambiato con l'elemento in fondo
			while (h->comparefunction(
					getElementContentAtPosition(h->genericlist, HEAP_TO_ARRAY(pos)),
					getElementContentAtPosition(h->genericlist, HEAP_TO_ARRAY(pos / 2))) > 0) {
				swapTwoElements(h->genericlist, HEAP_TO_ARRAY(pos), HEAP_TO_ARRAY(pos * 2));
			}
			break;
			
		} else if (pos * 2 + 1 == getListSize(h->genericlist)) {
			// Ho un figlio solo
			// E' il caso più semplice, perchè non devo aggiornare ulteriormente i collegamenti.
			swapTwoElements(h->genericlist, HEAP_TO_ARRAY(pos), HEAP_TO_ARRAY(pos * 2));
			break;
			
		} else {
			// Controllo i figli
			if (h->comparefunction(
					getElementContentAtPosition(h->genericlist, HEAP_TO_ARRAY(pos * 2)),				// Figlio SX (1)
					getElementContentAtPosition(h->genericlist, HEAP_TO_ARRAY(pos * 2 + 1))) > 0) {		// Figlio DX (2)
				// Il primo figlio è maggiore
				swapTwoElements(h->genericlist, HEAP_TO_ARRAY(pos), HEAP_TO_ARRAY(pos * 2));
				pos = pos * 2;
			} else {
				// Il secondo figlio è maggiore
				swapTwoElements(h->genericlist, HEAP_TO_ARRAY(pos), HEAP_TO_ARRAY(pos * 2 + 1));
				pos = pos * 2 + 1;
			}
		}
	}
	deleteLastElement(h->genericlist);
}

/**
 * Cancella un elemento dell'Heap, dato come parametro il suo riferimento.
 */
void bh_deleteElementByContent(binaryheap* h, void* element_to_delete) {
	int pos = bh_getElementPosition(h, element_to_delete);
	bh_deleteElementAtPosition(h, pos);
}

/**
 * Cancella dall'heap tutti gli elementi che soddisfano una data condizione, assicurandosi
 * che la struttura rimanga costantemente ben formattata (i.e. fa in modo che non venga infranta la
 * proprietà di heap).
 */
void bh_deleteElementsByConditions(binaryheap* h, bool (*condition)(void*)) {
	for (int i = getListSize(h->genericlist); i > 0; i--) {		// Scorro a partire dal fondo perché questo mi permette di eseguire un nuemro inferiore di istruzioni (nell'altra funzione)
		if (condition(getElementContentAtPosition(h->genericlist, HEAP_TO_ARRAY(i)))) {
			bh_deleteElementAtPosition(h, i);
		}
	}
}

/**
 * Cancella la radice dell'heap e risistema i nodi restanti.
 */
void bh_deleteFirstElement(binaryheap* h) {
	bh_deleteElementAtPosition(h, 0);
}

/**
 * Restituisce l'elemento dell'heap alla posizione desiderata.
 * <i>NOTA:</i> Gli indici dell'heap iniziano la numerazione dal valore 1.
 */
void* bh_getElementAtPosition(binaryheap* h, int pos) {
	return getElementContentAtPosition(h->genericlist, HEAP_TO_ARRAY(pos));
}

/**
 * Restituisce un elemento alla posizione desiderata, eliminandolo dall'heap.
 */
void* bh_extractElementAtPosition(binaryheap* h, int pos) {
	void* aux = getElementContentAtPosition(h->genericlist, HEAP_TO_ARRAY(pos));
	bh_deleteElementAtPosition(h, pos);
	return aux;
}

/**
 * Estrae dall'heap tutti gli elementi che soddisfano una data condizione, assicurandosi
 * che la struttura rimanga costantemente ben formattata (i.e. fa in modo che non venga infranta la
 * proprietà di heap).
 * Gli elementi estratti vengono inseriti all'interno di una lista e restituiti al termine dell'esecuzione.
 */
list* bh_extractElementsByConditions(binaryheap* h, bool (*condition)(void*)) {
	list* extracted = initList((l_type) al);
	for (int i = getListSize(h->genericlist); i > 0; i--) {		// Scorro a partire dal fondo perché questo mi permette di eseguire un nuemro inferiore di istruzioni (nell'altra funzione)
		if (condition(getElementContentAtPosition(h->genericlist, HEAP_TO_ARRAY(i)))) {
			void* elem_extracted = bh_extractElementAtPosition(h, i);
			insertElementLast(extracted, elem_extracted);
		}
	}
	return extracted;
}

/**
 * Restituisce la lista interna all'heap.
 */
list* bh_getElementList(binaryheap* h) {
	return h->genericlist;
}

/**
 * Restituisce l'elemento massimo dell'Heap, che per stessa definizione di max-heap si trova in testa.
 */
void* bh_getMaximumContent(binaryheap* h) {
	return getHeadContent(h->genericlist);
}

/**
 * Restituisce l'elemento minimo dell'heap, attraversandolo di padre in figlio.
 * Per ogni iterazione viene selezionato il figlio con valore inferiore.
 * L'algoritmo ha complessità log_2(n).
 */
void* bh_getMinimumContent(binaryheap* h) {
	int minimum_index = 1;
	while (minimum_index < getListSize(h->genericlist)) {
		if (h->comparefunction(
				getElementContentAtPosition(h->genericlist, HEAP_TO_ARRAY(minimum_index * 2)),
				getElementContentAtPosition(h->genericlist, HEAP_TO_ARRAY(minimum_index * 2 + 1))) > 0) {
			minimum_index = minimum_index * 2;
		} else {
			minimum_index = minimum_index * 2 + 1;
		}
	}
	return getElementContentAtPosition(h->genericlist, minimum_index);
}
#ifndef STRING_FORMAT_HEAP
	#define STRING_FORMAT_HEAP
	#define SPACING "----"
	#define NODE_STRING_LENGTH 30
#endif

/**
 * Funzione interna ricorsiva per la rappresentazione di una sotto-heap.
 */
static char* getSubtreeString(binaryheap* h, char* (*toStringFunction)(void*), int index, int level) {
	char* str = malloc ((int)(getListSize(h->genericlist) / pow(2, level)) * NODE_STRING_LENGTH * sizeof(char)); // Calcolo dello spazio necessario
	// Figlio sx
	for (int i = 0; i < level; i++) {
		strcat(str, SPACING);
	}
	strcat(str, toStringFunction(getElementContentAtPosition(h->genericlist, HEAP_TO_ARRAY(index * 2))));
	strcat(str, "\n");
	if (index * 2 <= getListSize(h->genericlist)) {
		strcat(str, getSubtreeString(h, toStringFunction, index * 2, level + 1));
	}
	// Figlio dx
	for (int i = 0; i < level; i++) {
		strcat(str, SPACING);
	}
	strcat(str, toStringFunction(getElementContentAtPosition(h->genericlist, HEAP_TO_ARRAY(index * 2 + 1))));
	strcat(str, "\n");
	if (index * 2 + 1 <= getListSize(h->genericlist)) {
		strcat(str, getSubtreeString(h, toStringFunction, index * 2 + 1, level + 1));
	}
	return str;
	
}

/**
 * Restituisce la rappresentazione dell'Heap binario come stringa.
 */
char* heapToString(binaryheap* h, char* (*toStringFunction)(void*)) {
	return getSubtreeString(h, toStringFunction, 1, 0);
}

///////////////////////////////////////////////////////////////////////////
// TEST

typedef struct {
	char first_letters[2];
	int three_numbers;
	char last_letters[2];
} string;

char getRandomChar() {
	return (char)((rand() % ('Z' - 'A')) + 'A');
}

string* initString() {
	string* new = malloc(sizeof(string));
	if (!new) {
		printf("ERRORE NULL");
	}
	new->first_letters[0] = getRandomChar();
	new->first_letters[1] = getRandomChar();
	new->three_numbers = rand() % 1000;
	new->last_letters[0] = getRandomChar();
	new->last_letters[1] = getRandomChar();
	return new;
}

char* stringifyMyStruct(void* my_object) {
	char* created_string = malloc(sizeof(char) * 13);
	sprintf(created_string, "[%c%c %03d %c%c] ", 
		((string*)my_object)->first_letters[0],
		((string*)my_object)->first_letters[1],
		((string*)my_object)->three_numbers,
		((string*)my_object)->last_letters[0],
		((string*)my_object)->last_letters[1]);
	return created_string;
}

int compareMyStruct(void* obj1, void* obj2) {
	return strcmp(
		stringifyMyStruct(((string*)obj1)), 
		stringifyMyStruct(((string*)obj2)));
}

int main(void) {
	
	binaryheap* heap = bh_initHeap(compareMyStruct);
	char* string_of_list = malloc(1024);
	
	srand(time(NULL));
	
	int dim = 10;
	
	for (int i = 0; i < dim; i++) {
		bh_insertElement(heap, initString());
	}
	
	string_of_list = heapToString(heap, stringifyMyStruct);
	printf("%s", string_of_list);
	
}

