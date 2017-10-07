#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_management.h"

int main ( int argc, char *argv[] ) {
	char *file_name=NULL; 	// Path for the file.
	alldataT new; 			// A node with all data.

	// Check if user give path from command line as argument.
	if ( argc > 1 ) {

		file_name = (char *)malloc((strlen(argv[1])+1)*sizeof(char));
		strcpy ( file_name, argv[1] );
	// Ask user to give a path from keyboard.
	}else {

		printf("Give path of file: ");
		scanf("%ms",&file_name);
	}

	// Create structure with all data and print this data.
	new=create_structure_by_file ( file_name );
	print_used_list(new.used_element);
	
	// Delete lists with used and unused data.
	delete_list(new.used_element);
	delete_nodes(new.unused_element);
	
	// Deallocate file_name.
	free ( file_name );
	file_name=NULL;
		
	return 0;
}