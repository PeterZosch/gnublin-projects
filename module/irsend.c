#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */
#include <sched.h>

#define DEVICE_FILE_NAME "/dev/ir2gpio"
#define N 32

int main()
{
	int file_desc, ret_val, i;

//int code[32] = {0,1,0,1,1,1,1,0,1,0,1,0,0,0,0,1,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,1};

	int hexcode = 0x5EA138C7;

	struct sched_param param;                                                   
                                                                                
    param.sched_priority = 99;                                                  
    if (sched_setscheduler(0, SCHED_FIFO, & param) != 0) {                      
        perror("sched_setscheduler");                                           
        exit(EXIT_FAILURE);                                                     
    }                                     
	
	i = 1;	

	file_desc = open(DEVICE_FILE_NAME, 0);

	if (file_desc < 0) {
		printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
		exit(-1);
	}

	ret_val = ioctl(file_desc, 42, hexcode );

/*	ret_val = ioctl(file_desc, 69, 4500);
	
	for( i = 0 ; i <= 31 ; i++) {
	
		if ( code[i] == 0 ) { 
			
			ret_val = ioctl(file_desc, 42, 510);

			ret_val = ioctl(file_desc, 69, 560);

		} else { 

			ret_val = ioctl(file_desc, 42, 510);

			ret_val = ioctl(file_desc, 69, 1690);
		}

	}
*/
	if (ret_val < 0) {
		printf("ioctl_set_msg failed:%d\n", ret_val);
		exit(-1);
	}
		return 0;
}
