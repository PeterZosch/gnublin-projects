#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */
#include <sched.h>

#define DEVICE_FILE_NAME "/dev/ir2gpio"
#define N 32

#define KEY_MUTE 		0x5EA138C7
#define KEY_PROGUP 		0x000808F7
#define KEY_PROGDOWN 	0x0008F00F
#define KEY_SIX		 	0x000810EF
#define KEY_EIGHT	 	0x000850AF
#define KEY_BACK	 	0x0008827D

int main( int argc, char *argv[] )
{
	int file_desc, ret_val;

	int hexcode = 0x00;

	struct sched_param param;                                                   
                                                                                
    param.sched_priority = 99;                                                  
    if (sched_setscheduler(0, SCHED_FIFO, & param) != 0) {                      
        perror("sched_setscheduler");                                           
        return EXIT_FAILURE;                                                     
    }                                     
	
   	if ( argc < 2 ) {
      printf("Benötige mindesten 1 Argument!\n");
      printf("Aufruf: %s <KEY_BUTTON>...\n", *argv);
      return EXIT_FAILURE;
   	}
	

	if ( (strcmp( argv[1], "KEY_MUTE" )) == 0 ) {
	
		hexcode = KEY_MUTE;
	
	} else if ( (strcmp( argv[1], "KEY_PROGUP" )) == 0 ) {

		hexcode = KEY_PROGUP;

	} else if ( (strcmp( argv[1], "KEY_PROGDOWN" )) == 0 ) {
	
		hexcode = KEY_PROGDOWN;
	
	} else if ( (strcmp( argv[1], "KEY_SIX" )) == 0 ) {
	
		hexcode = KEY_SIX;
	
	} else if ( (strcmp( argv[1], "KEY_EIGHT" )) == 0 ) {
	
		hexcode = KEY_EIGHT;
	
	} else if ( (strcmp( argv[1], "KEY_BACK" )) == 0 ) {
	
		hexcode = KEY_BACK;
	
	} else {
	
      printf("%s: Command not found\n", argv[1]);
      return EXIT_FAILURE;
	}

	file_desc = open(DEVICE_FILE_NAME, 0);

	if (file_desc < 0) {
		printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
		exit(-1);
	}

	ret_val = ioctl(file_desc, 42, hexcode );

	if (ret_val < 0) {
		printf("ioctl_set_msg failed:%d\n", ret_val);
		exit(-1);
	}
		return 0;
}
