#include "utils.h"

/**
 * This function appends the given node to a specified list by
 * updating their pointers as needed
 */
void sos_appendNodeToList(sos_list_t * list, sos_node_t * node) {
    //Empty list
    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
    }
    else {
        list->tail->next = node;
        list->tail = node;
        node->next = NULL;
    }
}

/**
 * This function is used to initialize a list
 */
sos_list_t * sos_initList() {
    sos_list_t * tmp = malloc(sizeof(sos_list_t));

    if (tmp == NULL) {
        return NULL;
    }
    else {
        tmp->head = NULL;
        tmp->tail = NULL;
        return tmp;
    }
}

/**
 * Auxiliary function for the printList function
 */
static void _aux_printNode(sos_node_t * node, unsigned int depth) {
    if (node->is_sublist) {
        printf("[LIST %s]", node->label != NULL ? node->label : "<anon>");
        _sos_printList(node->payload, depth + 1);
        putchar('\n');
    }
    else {
        printf("[NODE %s]", node->label != NULL ? node->label : "<anon>");
        printf(" -> %s", node->payload);
    }
}

/**
 * This function recursively prints a nice representation of a list and
 * it is mainly used for debugging purposes
 */
void _sos_printList(sos_list_t * list, unsigned int depth) {
    if (depth == 0) {
        printf("[ROOT]");
    }
    sos_node_t * next_node = list->head;
    while (next_node != NULL) {
        putchar('\n');
        for (int i = 0; i < (depth + 1) * 3; i++) {
            putchar(' ');
        }
        _aux_printNode(next_node, depth + 1);
        next_node = next_node->next;
    }
}

/**
 * This function recursively frees all the memory dinamically allocated when
 * creating a list which is no longer useful
 */
void freeList(sos_list_t * list) {
    sos_node_t * node = list->head;

    while (node != NULL) {
        //Check if label is present
        if (node->label != NULL) {
            free(node->label);
        }

        if (node->is_sublist) {
            sos_list_t * sublist = (sos_list_t *) node->payload;
            freeList(sublist);
        }
        else {
            char * node_payload = (char *) node->payload;
            free(node_payload);
        }
        sos_node_t * tmp = node->next;
        free(node);
        node = tmp;
    }
    free(list);
}

/**
 * This function is used to skip all the whitespace found between two characters
 * i.e. all the ' ', '\n' or '\t' which appears between two non-whitespace characters
 * The function returns the first character read after the whitespace
 */
int skip_whitespace(FILE * file) {
    int read_char;

    do {
        read_char = fgetc(file);
        switch (read_char) {

        case ' ':
        case '\n':
        case '\t':
            break;

        default:
            return read_char;
        }
    } while (true);
}
