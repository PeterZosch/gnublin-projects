#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

struct ircstruct{
    unsigned int sb_pulse;
    unsigned int sb_space;
	unsigned int adress;
    unsigned int command;
    unsigned int stop;
    };

struct ircstruct *ircode;


int main ( int argc, char *argv[] )
{

	ircode = malloc(sizeof(struct ircstruct));
	ircode = parse(ircode, argv);
//	parse( &ircode );
	
	printf("\nsb_pulse = %i", ircode->sb_pulse );
    printf("\nsb_space = %i", ircode->sb_space );
    printf("\nadress = %i", ircode->adress );
    printf("\ncommand = %i", ircode->command );
    printf("\nstop = %i\n", ircode->stop );

	return 0;	
}
/*
struct ircstruct *parse( struct ircstruct *ircode )
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

		if ( strstr( buffer, "MUTE") != NULL ) {
				
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

	ircode->sb_pulse = isb_pulse;
	ircode->sb_space = isb_space;
	ircode->adress = hadress;
	ircode->command = hcommand;
	ircode->stop = istop;

	printf("\nsb_pulse = %i", isb_pulse );
	printf("\nsb_space = %i", isb_space );
	printf("\nadress = %i", hadress );
	printf("\ncommand = %i", hcommand );
	printf("\nstop = %i\n", istop );

	
	fclose(conf);
	return ircode;
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
	value = (unsigned int)strtol(valueBuffer, NULL, 0);
	
	return value;
}
*/
