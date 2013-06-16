#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"


//int parsing( char *, int tab);
int parsing( char * );

int parse ( struct ircstruct *ircode, char *argv[] )
{
	char buffer[32] = {0};

	char sb_pulse[32] = {0};
	char sb_space[32] = {0};
	char adress[32] = {0};
	char command[32] = {0};
	char stop[32] = {0};
	
	unsigned int isb_pulse = 0x0;
	unsigned int isb_space = 0x0;
	unsigned int hadress = 0x0;
	unsigned int hcommand = 0x0;
	unsigned int istop = 0x0;

	int i = 0;	
	int found = 0;

/* 	argv[1] Argument in locales Chararry speichern um danach 
	eine .conf anzuhängen
*/
	char argv_par[32] = {0};
	char confName[6]= ".conf";
	char pathName[13]= "/etc/ircube/";
	
	while ( argv[1][i] != '\0' ) {

		argv_par[i] = argv[1][i];
		i++;
	}
	argv_par[i] = '\0';

	strcat(argv_par, confName);
	strcat(pathName, argv_par);

/******************************************************************************/
	
	FILE *config;
	config = fopen( pathName, "r");

	if ( NULL == config ) {

    	printf("File '%s' not found\n", argv_par);
    	return -1;
	}

	while (fgets(buffer, 256, config)){


		if ( strstr( buffer, "sb_pulse") != NULL ) {

			strcpy ( sb_pulse, buffer );
		}

		if ( strstr( buffer, "sb_space") != NULL ) {
				
			strcpy ( sb_space, buffer );
		}
		
		if ( strstr( buffer, "adress") != NULL ) {
				
			strcpy ( adress, buffer );
		}

		if ( strstr( buffer, argv[2]) != NULL ) {
				
			strcpy ( command, buffer );
			found++ ;		
		}
		
		if ( strstr( buffer, "stop") != NULL ) {

			strcpy ( stop, buffer );
		}

	}

	if ( !found ) {
		printf("Command %s in file '%s' not found\n", argv[2], argv_par );
		return -1;
	}
	
	isb_pulse = parsing(sb_pulse);	
	isb_space = parsing(sb_space);	
	hadress = parsing(adress);	
	hcommand = parsing(command);	
	istop = parsing(stop);	

	(*ircode).sb_pulse = isb_pulse;
	(*ircode).sb_space = isb_space;
	(*ircode).adress = hadress;
	(*ircode).command = hcommand;
	(*ircode).stop = istop;

	fclose(config);

	return 0;
}

//int parsing( char *label, int x ) 
int parsing( char *label ) 
{
	int i = 0;
	int j = 0;
	int found = 0;

	char valueBuffer[10] = {0};
	int value = 0;
	
	while (label[i] != '\n')	{
		
		if (label[i] == '=') {
	
			found = 1;
			i = i + 2;
		}
			
		if ( found ) {

			valueBuffer[j] = label[i];	
			j++;
		}			
					
		i++;

	}

	value = (unsigned int)strtol(valueBuffer, NULL, 0);

	return value;
}
