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


int main( int argc, char *argv[] )
{
	int file_desc, ret_val;

	struct ircstruct ircode;
/*
	struct sched_param param;                                                   
	    
    param.sched_priority = 99;                                                  
    if (sched_setscheduler(0, SCHED_FIFO, & param) != 0) {                      
        perror("sched_setscheduler");                                           
        return EXIT_FAILURE;                                                     
    }                                     
*/
	
   	if ( argc < 3 ) {
      printf("Benötige mindesten 2 Argumente!\n");
      printf("Aufruf: %s <Config> <KEY_BUTTON>...\n", *argv);
      return EXIT_FAILURE;
   	}
	
	ret_val = parse( &ircode, argv );

	if (ret_val < 0) {
		
		return EXIT_FAILURE;
	}

	file_desc = open(DEVICE_FILE_NAME, 0);

	if (file_desc < 0) {
		printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
		exit(-1);
	}

	ret_val = ioctl(file_desc, 42, &ircode );

	if (ret_val < 0) {
		printf("ioctl_set_msg failed:%d\n", ret_val);
		exit(-1);
	}

		return 0;
}
