#include "conversion.h"

static bool convertToJSONObject(FILE * file, sos_list_t * file_scheme);
static bool convertToJSONArray(FILE * file, sos_list_t * file_scheme);

static bool convertToJSONObject(FILE * file, sos_list_t * file_scheme) {
	if (file == NULL) {
		return false;
	}

	fprintf(file, "{");

	sos_node_t * current_node = file_scheme->head;
	while (current_node != NULL) {
		//Check if this node has a label
		if (current_node->label != NULL) {
			fprintf(file, "%s:", current_node->label);
		}

		if (!current_node->is_sublist) {
			//Print the content of the node
			fprintf(file, "%s", current_node->payload);
		}
		else {
			//Now we need to determine if this sublist will be expressed with a JSON array or object
			//Since the differ only in the fact that array values have no labels, we check the first element
			//of the sublist to check whether it has a label or not
			//The fact that all of the members of the list will have the same characteristic is just an assumption made
			//to avoid the need of validation
			bool is_array = false;
			sos_list_t * node_payload = (sos_list_t *) current_node->payload;
			if (node_payload->head->label == NULL) {
				is_array = true;
			}

			//Now we write the representation of the sublist
			if (is_array) {
				if (!convertToJSONArray(file, node_payload)) {
					return false;
				}
			}
			else {
				if (!convertToJSONObject(file, node_payload)) {
					return false;
				}
			}
		}

		//Here we check if we still have fields to write
		//Trailing newline is
		if (current_node->next == NULL) {
			fprintf(file, "}");
		}
		else {
			fputc(',', file);
		}

		current_node = current_node->next;
	}

	return true;
}

static bool convertToJSONArray(FILE * file, sos_list_t * file_scheme) {
	if (file == NULL) {
		return false;
	}

	fprintf(file, "[");

	sos_node_t * current_node = file_scheme->head;
	while (current_node != NULL) {
		//We don't check if a node has a label because in JSON arrays you cant have labels

		if (!current_node->is_sublist) {
			//Print the content of the node
			fprintf(file, "%s", current_node->payload);
		}
		else {
			//Like in convertToJSONObject() we need to determine if this sublist is an array or an object
			//The same assumption is made
			bool is_array = false;
			sos_list_t * node_payload = (sos_list_t *) current_node->payload;
			if (node_payload->head->label == NULL) {
				is_array = true;
			}

			//Now we write the representation of the sublist
			if (is_array) {
				if (!convertToJSONArray(file, node_payload)) {
					return false;
				}
			}
			else {
				if (!convertToJSONObject(file, node_payload)) {
					return false;
				}
			}
		}

		//Here we check if we still have fields to write
		if (current_node->next == NULL) {
			fprintf(file, "]");
		}
		else {
			fputc(',', file);
		}

		current_node = current_node->next;
	}

	return true;
}

bool convertToJSON(sos_list_t * scheme, char * file_name) {
	FILE * file = fopen(file_name, "w");
	if (file == NULL) {
		return false;
	}

	bool done = convertToJSONObject(file, scheme);
	fclose(file);
	return done;
}
