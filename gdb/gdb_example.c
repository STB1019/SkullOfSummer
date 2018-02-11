#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct list_cell_t {
	int int_payload;
	struct list_cell_t* next;
};

struct list_t {
	struct list_cell_t* head;
	int size;
};

struct list_cell_t* add_element(struct list_t* l, int el) {
	struct list_cell_t* cell = malloc(sizeof(struct list_cell_t)); //error! wrong size_t
	if (cell == NULL) {
		exit(2);
	}
	cell->int_payload = el,
	cell->next = NULL;

	if (l->head != NULL) {
		struct list_cell_t* tmp = l->head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = cell;
	} else {
		//empty list
		l->head = cell;
	}

	l->size += 1;

	return cell;
}

void printList(const struct list_t* l) {
	printf("[");
	struct list_cell_t* cell = l->head;
	
	while (cell != NULL) {
		printf("%d", cell->int_payload);
		if (cell->next != NULL) {
			printf(" ");
		}
		cell = cell->next;
	}
	printf("]");
}

int main() {
	struct list_t* l = malloc(sizeof(struct list_t));
	if (l == NULL) { //there is an error here!
		exit(1);
	}
	l->size = 0;
	l->head = NULL;
	
	add_element(l, 1);
	add_element(l, 1);
	add_element(l, 2);
	add_element(l, 3);
	add_element(l, 5);
	add_element(l, 8);

	printf("Fibonacci is:\n");
	printList(l);
	printf("\n");

	//no malloc deallocation!

	return 0;
}
