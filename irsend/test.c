#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main ( int argc, char *argv[] )
{
    struct ircstruct{
        unsigned int sb_pulse;
        unsigned int sb_space;
		unsigned int adress;
        unsigned int command;
        unsigned int stop;
    };

	struct ircstruct ircode;

	parse( *argv[], &ircode );
	
	printf("\nsb_pulse = %i", ircode.sb_pulse );
    printf("\nsb_space = %i", ircode.sb_space );
    printf("\nadress = %i", ircode.adress );
    printf("\ncommand = %i", ircode.command );
    printf("\nstop = %i\n", ircode.stop );

	return 0;	
}
