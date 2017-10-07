#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/***** Element structure *****/
typedef struct element {
	char type;
	char *name;
	char *pos_node;
	char *neg_node;
	double value;
	struct element *next;
}elementT;

/** Initialize list with elements **/ 
elementT *init_list ( elementT *element ) {
	elementT *head;

	// Bind memory for head.
	head = (elementT *)malloc(sizeof(elementT));

	// Bind memory for variables of struct element.
	head->name = (char *)malloc((strlen(element->name)+1)*sizeof(char));
	head->pos_node = (char *)malloc((strlen(element->pos_node)+1)*sizeof(char));
	head->neg_node = (char *)malloc((strlen(element->neg_node)+1)*sizeof(char));

	// Assign values to variables of node.
	head->type = element->type;
	strcpy ( head->name, element->name );
	strcpy ( head->pos_node, element->pos_node );
	strcpy ( head->neg_node, element->neg_node );
	head->value = element->value;
	
	head->next = NULL;

	// Free memory of temporary element.
	free(element->name);
	free(element->pos_node);
	free(element->neg_node);
	element->name = NULL;
	element->pos_node = NULL;
	element->neg_node = NULL;
	
	free(element);
	element=NULL;

	return head;
}

/** Add a new item to list **/
elementT *add_element ( elementT *tail, elementT *element ) {
	elementT *node;

	// Bind memory for node.
	node = (elementT *)malloc(sizeof(elementT));
	
	// Bind memory for variables of specific node.
	node->name = (char *)malloc((strlen(element->name)+1)*sizeof(char));
	node->pos_node = (char *)malloc((strlen(element->pos_node)+1)*sizeof(char));
	node->neg_node = (char *)malloc((strlen(element->neg_node)+1)*sizeof(char));

	// Assign values to variables of specific node.
	node->type = element->type;
	strcpy ( node->name, element->name );
	strcpy ( node->pos_node, element->pos_node );
	strcpy ( node->neg_node, element->neg_node );
	node->value = element->value;

	// Link node with existed list.
	tail->next = node;
	tail = node;
	tail->next = NULL;

	// Deallocate memory for temporary element.
	free(element->name);
	free(element->pos_node);
	free(element->neg_node);
	element->name = NULL;
	element->pos_node = NULL;
	element->neg_node = NULL;

	free ( element );
	element=NULL;

	return tail;
}

/** Delete all items from list **/
void delete_list ( elementT *head ) {
	elementT *curr;

	curr = head;
	while ( curr != NULL ) {
		head = curr->next;

		free ( curr->name );
		free ( curr->pos_node );
		free ( curr->neg_node );

		curr->name 		= NULL;
		curr->pos_node 	= NULL;
		curr->neg_node 	= NULL;

		free ( curr );
		curr = head;
	}
}

/** Print list **/
void print_used_list ( elementT *head ) {
	elementT *curr;

	curr = head;
	while ( curr != NULL ) {

		printf ( "%c %s %s %s %lf\n", curr->type, curr->name, curr->pos_node, curr->neg_node, curr->value );
		curr = curr->next;
	}
}
