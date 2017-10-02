#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_management.h"

int main ( int argc, char *argv[] ) {
	char *file_name=NULL;

	if ( argc > 1 ) {

		file_name = (char *)malloc(strlen(argv[1])*sizeof(char));
		strcpy ( file_name, argv[1] );
	}else {

		printf("Give path of file: ");
		scanf("%ms",&file_name);
	}

	create_structure_by_file ( file_name );

	free ( file_name );
	file_name=NULL;
		
	return 0;
}
