#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/***** Diode structure *****/
typedef struct diode {
	char *name;
	char *pos_node;
	char *neg_node;
	char *model_name;
	int area;
}diodeT;

/***** Transistor MOS structure *****/
typedef struct mos {
	char *name;
	char *drain;
	char *gate;
	char *source;
	char *body;
	char *model_name;
	double length;
	double width;
}mosT;

/***** Transistor BJT structure *****/
typedef struct bjt {
	char *name;
	char *collector;
	char *base;
	char *emitter;
	char *model_name;
	int area;
}bjtT;

/***** Elements union structure *****/
typedef struct elements_union{
	char type;
	diodeT *diode;
	mosT *mos;
	bjtT *bjt;
	struct elements_union *next;
}elemunT;

/** Dealocate used memory that is no longer necessary **/
void free_unused_node(elemunT *element){

	// Free all items of diode.
	if (element->type == 'D' || element->type == 'd' ) {

		free(element->diode->name);
		element->diode->name=NULL;
		free(element->diode->pos_node);
		element->diode->pos_node=NULL;
		free(element->diode->neg_node);
		element->diode->neg_node=NULL;
		free(element->diode->model_name);
		element->diode->model_name=NULL;
		free(element->diode);
		element->diode=NULL;
		free(element);		
		element = NULL;
	// Free all items of mos.
	}else if (element->type == 'M' || element->type == 'm'){

		free(element->mos->name);
		element->mos->name=NULL;
		free(element->mos->drain);
		element->mos->drain=NULL;
		free(element->mos->gate);
		element->mos->gate=NULL;
		free(element->mos->source);
		element->mos->source=NULL;
		free(element->mos->body);
		element->mos->body=NULL;
		free(element->mos->model_name);
		element->mos->model_name=NULL;
		free(element->mos);
		element->mos=NULL;
		free(element);
		element=NULL;
	// Free all items of bjt.
	}else {

		free(element->bjt->name);
		element->bjt->name=NULL;
		free(element->bjt->collector);
		element->bjt->collector=NULL;
		free(element->bjt->base);
		element->bjt->base=NULL;
		free(element->bjt->emitter);
		element->bjt->emitter=NULL;
		free(element->bjt->model_name);
		element->bjt->model_name=NULL;
		free(element->bjt);
		element->bjt=NULL;
		free(element);
		element=NULL;
	}
}

/** Initialize list with unused elements **/
elemunT *init_node (elemunT *element ){
	elemunT *head;

	if ( element->type == 'D' || element->type == 'd' ) {
		// Bind memory for head and diode.
		head = (elemunT *)malloc(sizeof(elemunT));
		head->diode = (diodeT *)malloc(sizeof(diodeT));
		
		// Bind memory for variables of struct diode.
		head->diode->name = (char *)malloc((strlen(element->diode->name)+1)*sizeof(char));
		head->diode->pos_node = (char *)malloc((strlen(element->diode->pos_node)+1)*sizeof(char));
		head->diode->neg_node = (char *)malloc((strlen(element->diode->neg_node)+1)*sizeof(char));
		head->diode->model_name = (char *)malloc((strlen(element->diode->model_name)+1)*sizeof(char));

		// Assign values to variables of node.
		head->type = element->type;
		strcpy ( head->diode->name, element->diode->name );
		strcpy ( head->diode->pos_node, element->diode->pos_node );
		strcpy ( head->diode->neg_node, element->diode->neg_node );
		strcpy ( head->diode->model_name, element->diode->model_name );
		head->diode->area = element->diode->area;

		head->mos=NULL;
		head->bjt=NULL;

		free_unused_node(element);
	}else if ( element->type == 'M' || element->type == 'm' ) {

		// Bind memory for head and mos.
		head = (elemunT *)malloc(sizeof(elemunT));
		head->mos = (mosT *)malloc(sizeof(mosT));

		// Bind memory for variables of struct mos.
		head->mos->name = (char *)malloc((strlen(element->mos->name)+1)*sizeof(char));
		head->mos->drain = (char *)malloc((strlen(element->mos->drain)+1)*sizeof(char));
		head->mos->gate = (char *)malloc((strlen(element->mos->gate)+1)*sizeof(char));
		head->mos->source = (char *)malloc((strlen(element->mos->source)+1)*sizeof(char));	
		head->mos->body = (char *)malloc((strlen(element->mos->body)+1)*sizeof(char));
		head->mos->model_name = (char *)malloc((strlen(element->mos->model_name)+1)*sizeof(char));

		// Assign values for variables of node.
		head->type = element->type;
		strcpy ( head->mos->name, element->mos->name );
		strcpy ( head->mos->drain, element->mos->drain );
		strcpy ( head->mos->gate, element->mos->gate );
		strcpy ( head->mos->source, element->mos->source );
		strcpy ( head->mos->body, element->mos->body );
		strcpy ( head->mos->model_name, element->mos->model_name );
		head->mos->length = element->mos->length;
		head->mos->width = element->mos->width;

		head->diode=NULL;
		head->bjt=NULL;

		free_unused_node(element);
	}else if( element->type == 'Q' || element->type == 'q') {

		// Bind memory for head and bjt.
		head = (elemunT *)malloc(sizeof(elemunT));
		head->bjt = (bjtT *)malloc(sizeof(bjtT));

		// Bind memory for variables of struct mos.
		head->bjt->name = (char *)malloc((strlen(element->bjt->name)+1)*sizeof(char));
		head->bjt->collector = (char *)malloc((strlen(element->bjt->collector)+1)*sizeof(char));
		head->bjt->base = (char *)malloc((strlen(element->bjt->base)+1)*sizeof(char));
		head->bjt->emitter = (char *)malloc((strlen(element->bjt->emitter)+1)*sizeof(char));	
		head->bjt->model_name = (char *)malloc((strlen(element->bjt->model_name)+1)*sizeof(char));

		// Assign values for variables of node.
		head->type = element->type;
		strcpy ( head->bjt->name, element->bjt->name );
		strcpy ( head->bjt->collector, element->bjt->collector );
		strcpy ( head->bjt->base, element->bjt->base );
		strcpy ( head->bjt->emitter, element->bjt->emitter );
		strcpy ( head->bjt->model_name, element->bjt->model_name );
		head->bjt->area = element->bjt->area;

		head->diode=NULL;
		head->mos=NULL;
		
		free_unused_node(element);
	}

	head->next = NULL;

	return head; 
}

/** Add a new item to list **/
elemunT *add_node (elemunT *tail, elemunT *element) {
	elemunT *node;

	if ( element->type == 'D' || element->type == 'd' ) {

		// Typecast node tail and element to diodeT.
		node = (elemunT *)malloc(sizeof(elemunT));
		node->diode=(diodeT *)malloc(sizeof(diodeT));

		// Bind memory for variables of struct diode.
		node->diode->name = (char *)malloc((strlen(element->diode->name)+1)*sizeof(char));
		node->diode->pos_node = (char *)malloc((strlen(element->diode->pos_node)+1)*sizeof(char));
		node->diode->neg_node = (char *)malloc((strlen(element->diode->neg_node)+1)*sizeof(char));
		node->diode->model_name = (char *)malloc((strlen(element->diode->model_name)+1)*sizeof(char));

		// Assign values to variables of node.
		node->type = element->type;
		strcpy ( node->diode->name, element->diode->name );
		strcpy ( node->diode->pos_node, element->diode->pos_node );
		strcpy ( node->diode->neg_node, element->diode->neg_node );
		strcpy ( node->diode->model_name, element->diode->model_name );
		node->diode->area = element->diode->area;

		node->mos=NULL;
		node->bjt=NULL;

		free_unused_node(element);
	}else if ( element->type == 'M' || element->type == 'm' ) {

		// Typecast node tail and element to mosT.
		node = (elemunT *)malloc(sizeof(elemunT));
		node->mos=(mosT *)malloc(sizeof(mosT));

		// Bind memory for variables of struct mos.
		node->mos->name = (char *)malloc((strlen(element->mos->name)+1)*sizeof(char));
		node->mos->drain = (char *)malloc((strlen(element->mos->drain)+1)*sizeof(char));
		node->mos->gate = (char *)malloc((strlen(element->mos->gate)+1)*sizeof(char));
		node->mos->source = (char *)malloc((strlen(element->mos->source)+1)*sizeof(char));	
		node->mos->body = (char *)malloc((strlen(element->mos->body)+1)*sizeof(char));
		node->mos->model_name = (char *)malloc((strlen(element->mos->model_name)+1)*sizeof(char));

		// Assign values for variables of node.
		node->type = element->type;
		strcpy ( node->mos->name, element->mos->name );
		strcpy ( node->mos->drain, element->mos->drain );
		strcpy ( node->mos->gate, element->mos->gate );
		strcpy ( node->mos->source, element->mos->source );
		strcpy ( node->mos->body, element->mos->body );
		strcpy ( node->mos->model_name, element->mos->model_name );
		node->mos->length = element->mos->length;
		node->mos->width = element->mos->width;

		node->diode=NULL;
		node->bjt=NULL;

		free_unused_node(element);
	}else if( element->type == 'Q' || element->type == 'q') {

		// Typecast node tail and element to bjtT.
		node = (elemunT *)malloc(sizeof(elemunT));
		node->bjt=(bjtT *)malloc(sizeof(bjtT));

		// Bind memory for variables of struct mos.
		node->bjt->name = (char *)malloc((strlen(element->bjt->name)+1)*sizeof(char));
		node->bjt->collector = (char *)malloc((strlen(element->bjt->collector)+1)*sizeof(char));
		node->bjt->base = (char *)malloc((strlen(element->bjt->base)+1)*sizeof(char));
		node->bjt->emitter = (char *)malloc((strlen(element->bjt->emitter)+1)*sizeof(char));	
		node->bjt->model_name = (char *)malloc((strlen(element->bjt->model_name)+1)*sizeof(char));

		// Assign values for variables of node.
		node->type = element->type;
		strcpy ( node->bjt->name, element->bjt->name );
		strcpy ( node->bjt->collector, element->bjt->collector );
		strcpy ( node->bjt->base, element->bjt->base );
		strcpy ( node->bjt->emitter, element->bjt->emitter );
		strcpy ( node->bjt->model_name, element->bjt->model_name );
		node->bjt->area = element->bjt->area;
		
		node->diode=NULL;
		node->mos=NULL;

		free_unused_node(element);
	}

	// Link node with list.
	tail->next = node;
	tail = node;
	tail->next = NULL;

	return tail;
}

/** Delete all times from list. **/
void delete_nodes ( elemunT *head ){
	elemunT *curr;

	curr = head;
	while ( curr != NULL ){
		head = curr->next;
		free_unused_node ( curr );
		curr = head;
	}
}

/** Print list of unused elements. **/
void print_unused_list ( elemunT *head ){
	elemunT *curr;

	curr = head;
	while( curr != NULL ){

		if ( curr->type == 'D' || curr->type == 'd' ){

			printf( "%c%s %s %s %s %d\n", curr->type, curr->diode->name, \
				curr->diode->pos_node, curr->diode->neg_node, curr->diode->model_name, curr->diode->area);
		}
		else if ( curr->type == 'M' || curr->type == 'm' ) {

			printf( "%c%s %s %s %s %s %s %lf %lf\n", curr->type, curr->mos->name, \
				curr->mos->drain, curr->mos->gate, curr->mos->source, curr->mos->body, \
				curr->mos->model_name, curr->mos->length, curr->mos->width );
		}
		else if ( curr->type == 'Q' || curr->type =='q' ) {

			printf( "%c%s %s %s %s %s %d\n", curr->type, curr->bjt->name, \
				curr->bjt->collector, curr->bjt->base, curr->bjt->emitter, curr->bjt->model_name, curr->bjt->area);
		}

		curr = curr->next;
	}
}