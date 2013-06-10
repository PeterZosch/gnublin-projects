#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

int parsing( char *, int tab);

void pars( char *argv[], struct ircode *ircode )
{
	char buffer[32] = {0};
	char sb_pulse[32] = {0};
	char sb_space[32] = {0};
	char adress[32] = {0};
	char command[32] = {0};
	char stop[32] = {0};

	int isb_pulse = 0x0;
	int isb_space = 0x0;
	int hadress = 0x0;
	int hcommand = 0x0;
	int istop = 0x0;
	
	FILE *conf;
	conf = fopen( "sat.conf", "r");

	while (fgets(buffer, 256, conf)){


		if ( strstr( buffer, "sb_pulse") != NULL ) {

			strcpy ( sb_pulse, buffer );
		}

		if ( strstr( buffer, "sb_space") != NULL ) {
				
			strcpy ( sb_space, buffer );
		}
		
		if ( strstr( buffer, "adress") != NULL ) {
				
			strcpy ( adress, buffer );
		}

		if ( strstr( buffer, argv[1]) != NULL ) {
				
			strcpy ( command, buffer );
		}
		
		if ( strstr( buffer, "stop") != NULL ) {

			strcpy ( stop, buffer );
		}

	}

	isb_pulse = parsing(sb_pulse, 2);	
	isb_space = parsing(sb_space, 2);	
	hadress = parsing(adress, 3);	
	hcommand = parsing(command, 3);	
	istop = parsing(stop, 3);	

	(*ircode).sb_pulse = isb_pulse
	(*ircode).sb_space = isb_space
	(*ircode).adress = hadress
	(*ircode).command = hcommand
	(*ircode).stop = istop

/*	printf("\nsb_pulse = %i", isb_pulse );
	printf("\nsb_space = %i", isb_space );
	printf("\nadress = %i", hadress );
	printf("\ncommand = %i", hcommand );
	printf("\nstop = %i\n", istop );
*/
	fclose(conf);
	return 0;
}

int parsing( char *label, int x ) 
{
	int i = 0;
	int j = 0;
	int tab = 0;

	char valueBuffer[10] = {0};
	int value = 0;
	
	while (label[i] != '\n')	{
		
			if (label[i] == '\t') {
			
				tab++;
			}
			
			if (tab == x) {

				valueBuffer[j] = label[i];	
				j++;
			}			
					
		i++;
	}
	value = (int)strtol(valueBuffer, NULL, 0);
	
	return value;
}
