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
elementT *init_list ( elementT element ) {
	elementT *head;

	head = (elementT *)malloc(sizeof(elementT));
	head->name = (char *)malloc(sizeof(char));
	head->pos_node = (char *)malloc(sizeof(char));
	head->neg_node = (char *)malloc(sizeof(char));

	head->type = element.type;
	strcpy ( head->name, element.name );
	strcpy ( head->pos_node, element.pos_node );
	strcpy ( head->neg_node, element.neg_node );
	head->value = element.value;
	head->next = NULL;

	return head;
}

/** Add a new item to list **/
elementT *add_element ( elementT *tail, elementT element ) {
	elementT *node;

	node = (elementT *)malloc(sizeof(elementT));
	
	node->name = (char *)malloc(sizeof(char));
	node->pos_node = (char *)malloc(sizeof(char));
	node->neg_node = (char *)malloc(sizeof(char));

	node->type = element.type;
	strcpy ( node->name, element.name );
	strcpy ( node->pos_node, element.pos_node );
	strcpy ( node->neg_node, element.neg_node );
	node->value = element.value;

	tail->next = node;
	tail = node;
	tail->next = NULL;

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
void print_list ( elementT *head ) {
	elementT *curr;

	curr = head;
	while ( curr != NULL ) {

		printf ( "%c%s %s %s %lf\n", curr->type, curr->name, curr->pos_node, curr->neg_node, curr->value );
		curr = curr->next;
	}
}


