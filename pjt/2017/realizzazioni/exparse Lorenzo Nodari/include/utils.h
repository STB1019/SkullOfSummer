#ifndef P3_UTILS_INCLUDED
#define P3_UTILS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//I don't want clients to see this function
#ifdef UTILS_PRIVATE_INCLUDE

int skip_whitespace(FILE *);

#endif

/**
 * This macro is used to mask the actual function which prints a list by
 * calling it with a default recursion level of 0
 */
#define sos_printList(x) _sos_printList(x, 0)

/**
 * This structure is used to represent a node in a list.
 * Note that a (void *) is used in order to create the possibility
 * for a node to contain a list itself.
 * When dealing with this structure, the is_sublist flag can be checked in
 * order to determine how the payload should be cast
 * The label field is used only for JSON and XML documents to represent tags
 */
typedef struct node {
    char * label;
    void * payload;
    bool is_sublist;
    struct node * next;
} sos_node_t;

/**
 * This structure represents a list. It simply contains
 * a pointer to the head of the list and one to the tail
 */
typedef struct {
    sos_node_t * head;
    sos_node_t * tail;
} sos_list_t;

void sos_appendNodeToList(sos_list_t *, sos_node_t *);
void _sos_printList(sos_list_t *, unsigned int);
void freeList(sos_list_t *);
sos_list_t * sos_initList();


#endif
