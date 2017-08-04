#define CSV_C_INCLUDE
#include "csv.h"

#define DEFAULT_BUFF_SIZE 256

/**
 * [PRIVATE]
 * This function is used to parse a single CSV field and return its content as a node
 * of a sos_list_t structure. The bool * parameter is used to comunicate to the caller
 * wheter we parsed the last field in a line.
 */
static sos_node_t * _csv_parseElement(FILE * file, bool * line_end, bool * file_end) {
    size_t dimension = DEFAULT_BUFF_SIZE;
    size_t buffer_index = 0;
    char read_char;
    char * buffer = malloc(dimension);

    //Parsing flags
    bool are_we_in_quotes = false;
    bool possible_quotes_escape = false;
    bool done = false;
    bool first_char_we_read = true;

    if (buffer == NULL) {
        return NULL;
    }

    do {
        read_char = fgetc(file);

        switch (read_char) {
        case EOF:
            if (first_char_we_read) {
                done = true;
                (*line_end) = true;
                (*file_end) = true;
            }
            else {
                free(buffer);
                (*file_end) = false;
                return NULL;
            }
            break;

        case '\"':
            if (first_char_we_read) {
                are_we_in_quotes = true;
            }
            else if (are_we_in_quotes && !possible_quotes_escape) {
                possible_quotes_escape = true;
            }
            else if (are_we_in_quotes && possible_quotes_escape) {
                buffer[buffer_index++] = '\"';
                possible_quotes_escape = false;
            }
            else {
                are_we_in_quotes = false;
            }
            break;

        case ',':
            if (are_we_in_quotes && !possible_quotes_escape) {
                buffer[buffer_index++] = read_char;
            }
            else {
                done = true;
                (*line_end) = false;
            }
            break;

        case '\n':
            if (are_we_in_quotes && !possible_quotes_escape) {
                buffer[buffer_index++] = read_char;
            }
            else {
                done = true;
                (*file_end) = false;
                (*line_end) = true;
            }
            break;

        default:
            buffer[buffer_index++] = read_char;
            break;
        }

        //Reallocates buffer space if needed
        if (buffer_index == dimension) {
            dimension *= 2;
            void * new_buffer = realloc(buffer, dimension);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            else {
                buffer = new_buffer;
            }
        }

        first_char_we_read = false;
    } while (!done);

    //Here we check if we finished reading the input, so that we don't create
    //an useless empty node
    if(feof(file)) {
        free(buffer);
        return NULL;
    }

    //And now we finally finish all we need to do by creating the structures we need and
    //returning the node to the caller
    buffer[buffer_index++] = '\0';

    sos_node_t * node = (sos_node_t *) malloc(sizeof(sos_node_t));
    if (node == NULL) {
        free(buffer);
        return NULL;
    }
    char * str = strndup(buffer, buffer_index);
    if (str == NULL) {
        free(buffer);
        free(node);
        return NULL;
    }

    node->label = NULL;
    node->payload = str;
    node->next = NULL;
    node->is_sublist = false;

    free(buffer);
    return node;
}

/**
 * [PRIVATE]
 * Parses a CSV record line and returns a sos_node_t structure
 * which contains a sublist formed by each of the record fields.
 * The bool * parameter is used to give informations to the caller
 * about wheter the end of the file was reached during parsing or not
 *
 */
static sos_node_t * _csv_parseLine(FILE * file, bool * file_end) {
    sos_list_t * fields_list = sos_initList();
    sos_node_t * tmp_node;
    bool line_end = false;

    if (fields_list == NULL) {
        return NULL;
    }

    do {
        tmp_node = _csv_parseElement(file, &line_end, file_end);
        if (tmp_node == NULL && !(*file_end)) {
            freeList(fields_list);
            return NULL;
        }
        else if (tmp_node == NULL && (*file_end)) {
            freeList(fields_list);
            return NULL;
        }
        else {
            sos_appendNodeToList(fields_list, tmp_node);
        }
    } while (!line_end);

    tmp_node = malloc(sizeof(sos_node_t));
    if (tmp_node == NULL) {
        freeList(fields_list);
        return NULL;
    }

    //We need to create an empty label to allow JSON conversion compatibility
    char * label = malloc(3 * sizeof(char));
    if (label == NULL) {
    	freeList(fields_list);
    	return NULL;
    }
    strcpy(label, "\"\"");

    tmp_node->label = label;
    tmp_node->payload = (void *) fields_list;
    tmp_node->is_sublist = true;

    return tmp_node;
}

/**
 * This function parses a CSV file and returns a pointer to a sos_list_t structure
 * containing the file data. The structure is useful as it is used to convert between
 * different file formats.
 */
sos_list_t * parseCSV(FILE * file) {
    sos_list_t * data = malloc(sizeof(sos_list_t));
    bool reached_eof = false;

    if (data == NULL) {
        return NULL;
    }

    do {
        sos_node_t * list_node = _csv_parseLine(file, &reached_eof);
        if (list_node == NULL && !(reached_eof)) {
            freeList(data);
            return NULL;
        }
        else if (list_node != NULL) {
            sos_appendNodeToList(data, list_node);
        }
    } while (!reached_eof);

    return data;
}
