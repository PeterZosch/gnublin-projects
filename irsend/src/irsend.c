#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */
#include <sched.h>
#include "parser.h"

#define DEVICE_FILE_NAME "/dev/ir2gpio"
#define N 32

struct ircstruct{
    unsigned int sb_pulse;
    unsigned int sb_space;
    unsigned int adress;
    unsigned int command;
    unsigned int stop;
    };

struct ircstruct *ircode;


int main( int argc, char *argv[] )
{
	int file_desc, ret_val;

	struct sched_param param;                                                   
                                                                                
    param.sched_priority = 99;                                                  
    if (sched_setscheduler(0, SCHED_FIFO, & param) != 0) {                      
        perror("sched_setscheduler");                                           
        return EXIT_FAILURE;                                                     
    }                                     
	
   	if ( argc < 3 ) {
      printf("Benötige mindesten 2 Argumente!\n");
      printf("Aufruf: %s <Config> <KEY_BUTTON>...\n", *argv);
      return EXIT_FAILURE;
   	}
	
    ircode = malloc(sizeof(struct ircstruct));

	ircode = parse( ircode, argv );

    printf("\nsb_pulse = %i", ircode->sb_pulse );
    printf("\nsb_space = %i", ircode->sb_space );
    printf("\nadress = %i", ircode->adress );
    printf("\ncommand = %i", ircode->command );
    printf("\nstop = %i\n", ircode->stop );

	file_desc = open(DEVICE_FILE_NAME, 0);

	if (file_desc < 0) {
		printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
		exit(-1);
	}

	ret_val = ioctl(file_desc, 77, &ircode );

	if (ret_val < 0) {
		printf("ioctl_set_msg failed:%d\n", ret_val);
		exit(-1);
	}
		return 0;
}
