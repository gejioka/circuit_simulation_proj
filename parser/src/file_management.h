#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_manipulation.h"
#include "unused_data_manipulation.h"

#define TYPE 	0
#define NAME 	1
#define POS 	2
#define NEG 	3
#define VALUE 	4
#define USED 	5
#define UNUSED 	6
#define GARBAGE 7
#define EXIT 	8
#define VALID 	9

/** All data structure **/
typedef struct all_data {
	int type_of_data;
	elementT *used_element;
	elemunT *unused_element;
}alldataT;

/** Convert value which read from file to SI **/
double convert_value_to_SI ( char *item, int characters_num ) {
	int count;					// A variable for count the size of item each time.
	char *substring=NULL; 		// A variable to store substrings of the item.
	double base; 				// A variable for the base of the value of item.
	double exp; 				// A variable for the exponent of the value of item.
	double value;  				// A variable for the value of the item.

	// Convert value to SI system.
	for ( count=0; count < characters_num+1; count++ ) {
		if ( item[count] == 'e' || item[count] == '\0' ) {
			
			// Bind memory for substring.
			substring = (char *)malloc((count + 1)*sizeof(char));
			
			// Copy item to substring.
			strncpy ( substring, item, count );
			substring[strlen(substring)] = '\0';
			
			// Convert substring to double.
			sscanf(substring, "%lf", &base);

			// Free memory for substring.
			free ( substring );
			substring = NULL;

			// Check if value has exponent.
			if ( item[count] == 'e' ) {

				// Bind memory for substring.
					substring = (char *)malloc((characters_num-count)*sizeof(char));
					
					// Find exponent of value.
					strcpy ( substring, item + count + 1 );
					substring[strlen(substring)-1] = '\0';

					// Convert exponent to double.
					sscanf ( substring,"%lf", &exp );
					
					// Free memory for substring.
					free ( substring );
					substring=NULL;
			}else {

				exp = 0.0;
			}
		}
	}
	
	// Calculate value.
	value = base*pow(10.0,exp);

	return value;
}

/** Check the type of specific data **/
int check_data_type ( char type ) {
	if ( type == 'V' || type == 'v' || type == 'I' || type == 'i' || type == 'R' || type == 'r' || \
			type == 'C' || type == 'c' || type == 'L' || type == 'l' ) {

		return USED;
	}else if ( type == 'D' || type == 'd' || type == 'M' || type == 'm' || type == 'Q' || type == 'q' ) {

		return UNUSED;
	}
	
	return -1;
}

/** Create a structure node with used data **/
elementT *create_structure_of_used_data ( FILE *file ) {
	int i; 						// A variable which using for counter.
	int size; 					// A variable for number of bytes that fread returns.
	int characters_num;			// A variable for count the size of item each time.
	int first_char; 			// A variable to check the first character of the line.
	double value;  				// A variable for the value of the item.
	char ch[2]; 				// A variable to store each character of the file.
	char *item=NULL; 			// A variable which store all items of a specific element.
	char type; 					// A variable for the type of the element.
	char *name; 				// A variable for the name of the element.
	char *pos_node; 			// A variable for the positive node of this element.
	char *neg_node; 			// A variable for the negative node of this element.
	elementT *node; 			// A variable type struct element.

	// Bind memory for the variable node.
	node = (elementT *)malloc(sizeof(elementT));
	
	// Initialize variables to enter in while.
	ch[0]='\0';
	ch[1]='\0';
	i=0;
	first_char=1;
	characters_num=1;
	item=(char *)calloc(sizeof(char),1);
	while ( ch[0] != '\n' ) {

		// Read file character by character.
		size = fread(ch, sizeof(char), 1, file);
		
		// Check if fread reaches EOF.
		if ( size == 0 ){
			
			break;
		}
		
		// Create a dynamic string which size is equal with it's length.
		item = (char *)realloc(item,(characters_num+1)* sizeof(char));

		// Add next character of file to item.
		if (ch[0] != ' ' && ch[0] != '\n' && ch[0]!= '\r' && ch[0] != '\t' ){
			
			strncat ( item, ch, 1);
			item[strlen(item)]='\0';
		}
	
		// Check if the item of element change.
		if ( ch[0] == ' ' || ch[0] == '\t' || first_char == 1 || ch[0] == '\n' ) {
			
			// Read item character by character.
			while ( first_char != 1 && ( ch[0] == ' ' || ch[0] == '\t' ) ) {
				
				size = fread(ch, sizeof(char), 1, file);
			}

			if ( first_char != 1 ) {

				fseek ( file, -1, SEEK_CUR );
			}

			// Add type of the specific element.
			if ( i == TYPE ) {
				first_char = 0;
				type = ch[0];
				free ( item );
				item = NULL;

			// Add name of the specific element.
			}else if ( i == NAME ) {
				name = (char *)malloc((strlen(item)+1)*sizeof(char));

				strcpy ( name, item );

				free ( item );
				item = NULL;

			// Add positive node for the specific element.
			}else if ( i == POS ) {
				pos_node = (char *)malloc((strlen(item)+1)*sizeof(char));

				strcpy ( pos_node, item );

				free ( item );
				item = NULL;

			// Add negative node for the specific element.
			}else if ( i == NEG ) {
				neg_node = (char *)malloc((strlen(item)+1)*sizeof(char));
				
				strcpy ( neg_node, item );

				free ( item );
				item = NULL;

			// Add value for the specific element.
			}else if ( i == VALUE ) {
				
				value = convert_value_to_SI ( item, characters_num );

				// Free memory for item
				free(item);
				item =NULL;
			}

			item=(char *)calloc(sizeof(char),1);
			i++;
			characters_num = 0;
		}

		characters_num++;
	}

	// Assign values to variables of node.
	node->type=type;
	node->name=name;
	node->pos_node=pos_node;
	node->neg_node=neg_node;
	node->value=value;
	
	// Deallocate item.
	free(item);
	item=NULL;
	
	return node;
}

/** Create structure of unused data **/
elemunT *create_structure_of_unused_data(FILE *file){
	int element_variable; 	// A variable that decide in which variable will the value be stored.
	int size; 				// A variable that fread use to return how many bytes read from file.
	int characters_num; 	// A variable for count the size of item each time.
	int first_char;			// A variable to check the first character of the line.
	char ch[2];				// A variable to store each character of the file.
	char *item=NULL;		// A variable which store all items of a specific element.
	elemunT *node; 			// A variable type struct elemun.

	// Bind memory for node.
	node = (elemunT *)malloc(sizeof(elemunT));

	// Initialize variables.
	ch[0]='\0';
	ch[1]='\0';
	element_variable = 0;
	first_char=1;
	characters_num=1;
	item = (char *)calloc(sizeof(char),1);
	while (ch[0] != '\n') {
		// Read caharacter from file.
		size = fread(ch, sizeof(char), 1, file);

		// Check if fread reaches the EOF.
		if (size == 0){
			
			break;
		}

		// Bind memory for item.
		item=(char *)realloc(item, (characters_num + 1)*sizeof(char));

		// Append item with ch value.
		if (ch[0] != ' ' && ch[0] != '\n' && ch[0] != '\r' && ch[0]!='\t'){
			
			strcat(item,ch);
			item[strlen(item)]='\0';
		}

		// Check if the item of element change.
		if ( ch[0] == ' ' || ch[0] == '\t' || first_char == 1 || ch[0] == '\n' ) {
			
			// Skip all spaces and tabs.
			while ( first_char != 1 && ( ch[0] == ' ' || ch[0] == '\t' ) ){
			
				size = fread(ch, sizeof(char), 1, file);
			}

			if (first_char != 1){
			
				fseek( file, -1, SEEK_CUR);
			}

			// Find the type of element.
			if (first_char == 1){
				first_char = 0;
				
				node->type = ch[0];

				if (node->type == 'D' || node->type == 'd'){
					
					// Bind memory for diode.
					node->diode = (diodeT *)malloc(sizeof(diodeT));
					node->mos=NULL;
					node->bjt=NULL;
				}else if(node->type == 'M' || node->type == 'm'){
					
					// Bind memory for mos.
					node->diode=NULL;
					node->mos = (mosT *)malloc(sizeof(mosT));
					node->bjt=NULL;
				}else if( node->type == 'Q' || node->type == 'q'){
					
					// Bind memory for bjt.
					node->diode = NULL;
					node->mos = NULL;
					node->bjt = (bjtT *)malloc(sizeof(bjtT));
				}
				
				// Deallocate item.
				free(item);
				item = NULL;
			}else if(node->type == 'D' || node->type == 'd'){

				// Add name of the specific element.
				if (element_variable == 1){
					node->diode->name=(char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->diode->name,item);

					free(item);
					item = NULL;
				
				// Add positive node of specific element.
				}else if (element_variable == 2){
					node->diode->pos_node = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->diode->pos_node,item);


					free(item);
					item = NULL;

				// Add negatie node of specific element.
				}else if (element_variable == 3){
					node->diode->neg_node = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->diode->neg_node, item);

					free(item);
					item=NULL;

				// Add model name of specific element.
				}else if (element_variable == 4){
					node->diode->model_name = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->diode->model_name,item);

					free(item);
					item=NULL;

				// Add area of specific element.
				}else if ( element_variable == 5){
					node->diode->area = atoi(item);

					free(item);
					item = NULL;
				}
				
			}else if (node->type == 'M' || node->type == 'm'){

				// Add name of specific element.
				if (element_variable == 1){
					node->mos->name = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->mos->name,item);

					free(item);
					item = NULL;

				// Add drain of specific element.
				}else if (element_variable == 2){
					node->mos->drain = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->mos->drain,item);

					free(item);
					item = NULL;

				// Add gate of specific element.
				}else if (element_variable == 3){
					node->mos->gate = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->mos->gate,item);

					free(item);
					item = NULL;

				// Add source of specific element.
				}else if (element_variable == 4){
					node->mos->source = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->mos->source,item);

					free(item);
					item = NULL;

				// Add body of specific element.
				}else if (element_variable == 5){
					node->mos->body = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->mos->body,item);

					free(item);
					item = NULL;

				}else if (element_variable == 6){
					node->mos->model_name = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->mos->model_name,item);

					free(item);
					item = NULL;

				// Add length of specific element.
				}else if (element_variable == 7){

					node->mos->length = convert_value_to_SI ( item, characters_num );

					free(item);
					item =NULL;

				// Add width of specific element.
				}else if (element_variable == 8){
				
					node->mos->width = convert_value_to_SI ( item, characters_num );

					free(item);
					item =NULL;
				}


			}else if (node->type == 'Q' || node->type == 'q'){

				// Add name of specific element.
				if (element_variable == 1){
					node->bjt->name = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->bjt->name,item);

					free(item);
					item = NULL;

				// Add collector of specific element.
				}else if (element_variable == 2){
					node->bjt->collector=(char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->bjt->collector,item);

					free(item);
					item = NULL;

				// Add base of specific element.
				}else if (element_variable == 3){
					node->bjt->base = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->bjt->base,item);

					free(item);
					item = NULL;

				// Add emitter of specific element.
				}else if (element_variable == 4){
					node->bjt->emitter = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->bjt->emitter,item);

					free(item);
					item = NULL;

				// Add model name of specific element.
				}else if (element_variable == 5){
					node->bjt->model_name = (char *)malloc((strlen(item)+1)*sizeof(char));
					strcpy(node->bjt->model_name,item);

					free(item);
					item = NULL;

				// Add area of specific element.
				}else if (element_variable == 6){
					node->bjt->area = atoi(item);

					free(item);
					item = NULL;
				}
			}

			element_variable++;
			characters_num=0;
			
			// Bind memory for item.
			item = (char *)calloc(sizeof(char),1);
		}

		characters_num++;
	}

	// Deallocate item.
	free(item);
	item=NULL;

	// Check if diode has area value and if don't set it to default ( 1 ).
	if ( element_variable == 5 ) {

		node->diode->area = 1;
	}else if (element_variable == 6 && node->bjt != NULL ) {
		
		node->bjt->area = 1;
	}

	return node;
}

/** Read line by line the file **/
alldataT read_line ( FILE *file ) {
	int data_type; 				// A variable that tell us node is valid or garbage.
	int type; 					// A variable for the type of node.
	int first_char; 			// A variable to check the first character of the line.
	int flag_first; 			// A variable to check for empty lines.
	int size; 					// A variable that fread use to return how many bytes read from file.
	char ch[2]; 				// A variable to store each character of the file.
	alldataT node;	 			// A variable type struct alldata.			
	elementT *used_element; 	// A variable type struct elemun.
	elemunT *unused_element; 	// A variable type struct elemun.

	// Initialize variables.
	ch[0] = '\0';
	ch[1] = '\0';
	if ( file != NULL ) {

		// Initialize variables i, first_char, characters_num and type.
		first_char=1;
		flag_first=1;
		type=EXIT;
		while ( 1 ) {

			// Read file character by character.
			size = fread(ch, sizeof(char), 1, file);

			// Check if reach EOF.
			if ( size == 0 ){
				
				break;
			}

			// Check if fread finds an empty line.
			if ( ch[0] == '\n' && flag_first == 1 ) {
				
				node.type_of_data = GARBAGE;
				node.used_element = NULL;
				node.unused_element = NULL;

				break;
			}else {
				// Check if the first character of a useless line is \r.
				if ( ch[0] != '\r' ) {
					
					flag_first = 0;
				}
			}

			// Check if line has comments and skip it.
			if ( ch[0] == '*' ) {
				size = fread(ch, sizeof(char), 1, file);

				while ( ch[0] != '\n' && size != 0 ) {
					
					size = fread(ch, sizeof(char), 1, file);
				}

				node.type_of_data = GARBAGE;
				node.used_element = NULL;
				node.unused_element = NULL;

				break;
			}

			if ( first_char == 1 && ch[0] != '\r' ) {
				type = ch[0];
				
				fseek ( file, -1, SEEK_CUR );
				data_type = check_data_type ( type );
				if ( data_type != -1 ) {
					// Add node to list with used nodes.
					if ( data_type == USED ) {
						used_element = create_structure_of_used_data ( file );

						node.type_of_data = VALID;
						node.used_element = used_element;
						node.unused_element = NULL;

					// Add node to list with unused nodes.
					}else {
						unused_element = create_structure_of_unused_data ( file );

						node.type_of_data = VALID;
						node.unused_element = unused_element;
						node.used_element = NULL;
					}

					break;
				}
			}
		}

		// Create node with the above information.
		if ( ( size != 0 ) || (size == 0 && type != EXIT)){
			if ( node.type_of_data == GARBAGE ) {

				return node;
			}

			return node;
		}
	}

	// Create exit node.
	node.type_of_data = EXIT;
	node.used_element = NULL;
	node.unused_element = NULL;

	return node;
}

/** Create structure for all elements which exists in file **/
alldataT create_structure_by_file ( char *file_name ) {
	int first_used_node; 				// A variable to check for the first used node.
	int first_unused_node; 				// A variable to check for the first unused node. 
	FILE *file; 						// A variable for the file.
	elementT *u_head; 					// A variable for the head of used nodes.
	elementT *u_tail; 					// A variable for the tail of used nodes.
	elemunT *un_head=NULL; 				// A variable for the head of unused nodes.
	elemunT *un_tail;  					// A variable for the tail of unused nodes.
	alldataT node; 						// A variable for the node.
	//elementT *element,*head,*tail;

	// Open file for read and read it line by line.
	file = fopen(file_name,"r");
	node=read_line(file);
	
	// Initialize the list of elements.
	while ( node.type_of_data == GARBAGE ) {
		
		node=read_line(file);
	}

	// Read all file and create the structure with elements.
	first_used_node=1;
	first_unused_node=1;
	while ( node.type_of_data != EXIT ) {
		if ( node.type_of_data == VALID ) {
			// Check if is the first time of an used or an unused node and init the corresponding list. 
			if ( first_used_node == 1 && first_unused_node == 1 ) {
				if ( node.unused_element == NULL ) {
					
					u_head = init_list ( node.used_element );
					u_tail = u_head;
					first_used_node=0;
				}else {

					un_head = init_node ( node.unused_element );
					un_tail = un_head;
					first_unused_node=0;
				}
			}else if ( first_used_node == 1 && node.unused_element == NULL ) {

				u_head = init_list ( node.used_element );
				u_tail = u_head;
				first_used_node=0;
			}else if ( first_unused_node == 1 && node.used_element == NULL ) {

				un_head = init_node ( node.unused_element );
				un_tail = un_head;
				first_unused_node=0;
			}
		}

		// Create new node.
		node=read_line(file);

		// Add new node to list.
		if ( node.type_of_data != EXIT && node.type_of_data != GARBAGE ) {
			if ( node.unused_element == NULL ) {
				if (first_used_node != 1){
					u_tail = add_element ( u_tail, node.used_element );
				}
			}else if (first_unused_node != 1) {

				un_tail = add_node ( un_tail, node.unused_element );
			}
		}
	}
	
	// Print list with unused nodes.
	if (un_head != NULL){
		print_unused_list(un_head);
	}

	// Assign used and unused head to node.
	node.used_element = u_head;
	node.unused_element = un_head;
	
	// Close file.
	fclose(file);
	
	return node;
}