#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ircstruct{
    unsigned int sb_pulse;
    unsigned int sb_space;
    unsigned int adress;
    unsigned int command;
    unsigned int stop;
    };

int parse( struct ircstruct *ircode, char *argv[] );
