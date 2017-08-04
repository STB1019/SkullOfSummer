#define JSON_C_INCLUDE
#include "json.h"

#define TOKEN_BUFFER_SIZE 64
#define DELIMITERS_NUM 4

//Function masks
#define _json_parseLabel(x) _json_parseToken(x, NULL)

//Functions declarations
static char * _json_parseToken(FILE * file, int * delimiter_found);
static sos_list_t * _json_parseObject(FILE * file);
static sos_list_t * _json_parseArray(FILE * file);
static bool _aux_appendComplexValueNode(sos_list_t * main_list, sos_list_t * payload_list, char * label);
static bool _aux_appendSimpleValueNode(sos_list_t * main_list, char * payload, char * label);
sos_list_t * parseJSON(FILE * file);

/**
 * This function reads from the file, skipping any whitespace and stopping
 * when a delimiter character is found. It returns a dinamically allocated
 * string containing the parsed token, without the trailing delimiter and returns
 * information at the caller about the found delimiter through the int * parameter
 * Note that the delimiter is actually read from the file, so next reads from the file
 * will not read it again.
 */
static char * _json_parseToken(FILE * file, int * delimiter_found) {
    int delimiters[DELIMITERS_NUM] = {':', '}', ']', ','};
    size_t dimension = TOKEN_BUFFER_SIZE;
    char * buffer = malloc(dimension);
    unsigned int buffer_index = 0;
    int read_char = 0;

    bool done = false;
    bool in_quotes = false;

    if (buffer == NULL) {
        return NULL;
    }

    while (!done) {
        read_char = fgetc(file);

        //We check if we found a delimiter
        for (int i = 0; i < DELIMITERS_NUM; i++) {
            if (read_char == delimiters[i] && !in_quotes) {
                done = true;
                //Check for possible parameter suppression
                if (delimiter_found != NULL) {
                    (* delimiter_found) = delimiters[i];
                }
            }
        }

        //In case we did not found a delimiter we act accordingly
        switch (read_char) {

        case '\"':
            in_quotes = !in_quotes;
            buffer[buffer_index++] = read_char;
            break;

        //Tabs and newlines are ignored (for simplicity)
        case '\n':
        case '\t':
            break;

        case ' ':
            if (in_quotes) {
                buffer[buffer_index++] = read_char;
            }
            break;

        default:
            if (!done) {
                buffer[buffer_index++] = read_char;
            }

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
    }

    //Now that we are done we return the read string
    //We don't check if str is NULL as in that case we would return NULL anyways
    buffer[buffer_index++] = '\0';
    char * str = strndup(buffer, buffer_index);
    free(buffer);
    return str;
}

/**
 * This auxiliary function is used to allocate a sos_node_t structure containing
 * a complex value (i.e array or object) and append is to the given list.
 * The main purpose of this function is to avoid repeating code and allow other functions
 * to be clearer.
 *
 * Parameters:
 * - main_list: the list in which we will put our new node
 * - payload_list: the list that will be the payload of the new node
 * - label: the label to be assigned to the new node
 *
 * Return value:
 * The function returns true if everything is ok, false otherwise
 *
 * NOTE: If something goes wrong the function frees only the memory it allocated, so the caller function
 *       still needs to free what she allocated
 */
static bool _aux_appendComplexValueNode(sos_list_t * main_list, sos_list_t * payload_list, char * label) {
    sos_node_t * appended_node = malloc(sizeof(sos_node_t));
    if (appended_node == NULL) {
        return false;
    }

    if (payload_list == NULL) {
        free(appended_node);
        return false;
    }

    appended_node->label = label;
    appended_node->payload = payload_list;
    appended_node->is_sublist = true;
    sos_appendNodeToList(main_list, appended_node);
    return true;
}

/**
 * This functions has the same exact purpose of _aux_appendComplexValueNode, but handles simple values
 */
static bool _aux_appendSimpleValueNode(sos_list_t * main_list, char * payload, char * label) {
    sos_node_t * appended_node = malloc(sizeof(sos_node_t));
    if (appended_node == NULL) {
        return false;
    }

    if (payload == NULL) {
        free(appended_node);
        return false;
    }

    appended_node->label = label;
    appended_node->payload = payload;
    appended_node->is_sublist = false;
    sos_appendNodeToList(main_list, appended_node);
    return true;
}

static sos_list_t * _json_parseObject(FILE * file) {
    sos_list_t * returned_list = sos_initList();
    sos_list_t * tmp_list;
    int read_char = 0;
    int found_delimiter = 0;

    bool done = false;
    bool everything_ok = true;

    if (returned_list == NULL) {
        return NULL;
    }

    while (!done && everything_ok) {
        //Since we are parsing an object we assume we always find a label before a value
        char * label = _json_parseToken(file, &found_delimiter);
        if (label == NULL) {
            everything_ok = false;
            break;
        }
        else if (found_delimiter == ',') {
        	free(label);
            continue;
        }
        else if (found_delimiter == '}') {
            done = true;
            //An empty string is returned in this case and is not assigned to any node, so it needs to be freed
            free(label);
            break;
        }

        //Now we determine the type of value associated to this label
        read_char = skip_whitespace(file);

        switch (read_char) {

        case ',':
            break;

        case '}':
            done = true;
            break;

        //We found an array
        case '[':
            tmp_list = _json_parseArray(file);
            everything_ok = _aux_appendComplexValueNode(returned_list, tmp_list, label);
            break;
        //We found an object
        case '{':
            tmp_list = _json_parseObject(file);
            everything_ok = _aux_appendComplexValueNode(returned_list, tmp_list, label);
            break;

        //We found a simple value
        default:
            //We put back the first char of the field and then parse its value
            ungetc(read_char, file);
            char * payload = _json_parseToken(file, &found_delimiter);
            everything_ok = _aux_appendSimpleValueNode(returned_list, payload, label);

            if (found_delimiter == '}') {
                done = true;
            }
        }
    }
    //We check for any error
    if (!everything_ok) {
        freeList(returned_list);
        return NULL;
    }
    else {
        return returned_list;
    }
}

static sos_list_t * _json_parseArray(FILE * file) {
    sos_list_t * returned_list = sos_initList();
    sos_list_t * tmp_list;
    int read_char = 0;

    bool done = false;
    bool everything_ok = true;

    if (returned_list == NULL) {
        return NULL;
    }

    while (!done && everything_ok) {

        read_char = skip_whitespace(file);

        switch (read_char) {

        case ',':
            break;

        case ']':
            done = true;
            break;

        case '[':
            tmp_list = _json_parseArray(file);
            everything_ok = _aux_appendComplexValueNode(returned_list, tmp_list, NULL);
            break;

        case '{':
            tmp_list = _json_parseObject(file);
            everything_ok = _aux_appendComplexValueNode(returned_list, tmp_list, NULL);
            break;

        default:
            ungetc(read_char, file);
            int found_delimiter = 0;
            char * payload = _json_parseToken(file, &found_delimiter);
            everything_ok = _aux_appendSimpleValueNode(returned_list, payload, NULL);

            if (found_delimiter == ']') {
                done = true;
            }
        }
    }

    if (!everything_ok) {
        freeList(returned_list);
        return NULL;
    }
    else {
        return returned_list;
    }
}

/**
 * This functions is the public interface of the parser
 */
sos_list_t * parseJSON(FILE * file) {
    int first_char = skip_whitespace(file);

    if (first_char != '{') {
        return NULL;
    }
    else {
        return _json_parseObject(file);
    }
}
