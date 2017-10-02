#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_manipulation.h"

#define TYPE 	0
#define NAME 	1
#define POS 	2
#define NEG 	3
#define VALUE 	4

elementT *read_line ( FILE *file );
elementT *create_structure_by_file ( char *file_name );

/** Read line by line the file **/
elementT *read_line ( FILE *file ) {
	int i; 						// A variable which using for counter.
	int size; 					// A variable for number of bytes that fread returns.
	int count,characters_num;	// A variable for count the size of item each time.
	int first_char; 			// A variable to check the first character of the line.
	double exp; 				// A variable for the exponent of the value of item.
	double value;  				// A variable for the value of the item.
	double base; 				// A variable for the base of the value of item.
	char ch[2]; 				// A variable to store each character of the file.
	char *item=NULL; 			// A variable which store all items of a specific element.
	char type; 					// A variable for the type of the element.
	char *name; 				// A variable for the name of the element.
	char *pos_node; 			// A variable for the positive node of this element.
	char *neg_node; 			// A variable for the negative node of this element.
	char *substring; 			// A variable to store substrings of the item.
	elementT *node; 			// A variable type struct element.

	// Bind memory for the variable node.
	node = (elementT *)malloc(sizeof(elementT));

	ch[0] = '\0';
	ch[1] = '\0';
	if ( file != NULL ) {
		// Initialize variables i, first_char, characters_num.
		i=0;
		first_char=1;
		characters_num=1;

		while (ch[0] != '\n') {
			// Read file character by character.
			size = fread(ch, sizeof(char), 1, file);
			
			// Check if read reaches EOF and exit from while.
			if ( size==0 ){
				break;
			}

			// Create a dynamic string which size is equal with it's length.
			item = (char *)realloc(item,characters_num * sizeof(char));

			// Add next character of file to item.
			strcat ( item, ch );

			// Check if the item of element change.
			if ( ch[0] == ' ' || first_char == 1 || ch[0] == '\n' ) {
				// Add type of the specific element.
				if ( i == TYPE ){
					first_char = 0;
					type = ch[0];

					free ( item );
					item = NULL;

				// Add name of the specific element.
				}else if ( i == NAME ) {
					name = (char *)malloc(characters_num*sizeof(char));

					item[strlen(item)-1] = '\0';
					strcpy ( name, item );

					free ( item );
					item = NULL;

				// Add positive node for the specific element.
				}else if ( i == POS ) {
					pos_node = (char *)malloc(characters_num*sizeof(char));
					item[strlen(item)-1] = '\0';

					strcpy ( pos_node, item );

					free ( item );
					item = NULL;

				// Add negative node for the specific element.
				}else if ( i == NEG ) {
					neg_node = (char *)malloc(characters_num*sizeof(char));
					item[strlen(item)-1] = '\0';

					strcpy ( neg_node, item );

					free ( item );
					item = NULL;

				// Add value for the specific element.
				}else if ( i == VALUE ) {
					item[strlen(item)-1] = '\0';

					for ( count=0; count < characters_num; count++ ) {
						if ( item[count] == 'e' || item[count] == '\0' ) {
							substring = (char *)malloc((count + 1)*sizeof(char));
							strncpy ( substring, item, count );
							substring[strlen(substring)-1] = '\0';
							sscanf(substring, "%lf", &base);

							free ( substring );
							substring = NULL;
							if ( item[count] == 'e' ) {
 								substring = (char *)malloc((characters_num-count)*sizeof(char));
 								strcpy ( substring, item + count + 1 );
 								substring[strlen(substring)-1] = '\0';

 								sscanf ( substring,"%lf", &exp );
 								free ( substring );
 								substring=NULL;
							}else {

								exp = 0.0;
							}
						}
					}
					free(item);
					item =NULL;

					value = base*pow(10.0,exp);
				}
				
				i++;
				characters_num = 0;
			}
			characters_num++;
		}

		// Create node with the above information.
		if (size != 0){
			node->type=type;
			node->name=name;
			node->pos_node=pos_node;
			node->neg_node=neg_node;
			node->value=value;
			
			return node;
		}
		
	}

	return NULL;
}

/** Create structure for all elements which exists in file **/
elementT *create_structure_by_file ( char *file_name ) {
	FILE *file;
	elementT *element,*head,*tail;

	// Open file for read and read it line by line.
	file = fopen(file_name,"r");
	element=read_line(file);
	// Initialize the list of elements.
	head = init_list(element);
	tail = head;

	// Read all file and 
	while ( element != NULL){
		element=read_line(file);
		if (element != NULL){
			tail = add_element(tail,element);
		}
	}
	print_list(head);

	return 0;
}