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
	int file_desc, ret_val;

	int hexcode = 0x00818E7;

	struct code {
		int start = 1;
		int adress = 2;
		int command = 3;
		int end = 4;
	};

	struct sched_param param;                                                   
                                                                                
    param.sched_priority = 99;                                                  
    if (sched_setscheduler(0, SCHED_FIFO, & param) != 0) {                      
        perror("sched_setscheduler");                                           
        exit(EXIT_FAILURE);                                                     
    }                                     
	
	struct code hexcode;

	file_desc = open(DEVICE_FILE_NAME, 0);

	if (file_desc < 0) {
		printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
		exit(-1);
	}

	ret_val = ioctl(file_desc, 42, &hexcode );

	if (ret_val < 0) {
		printf("ioctl_set_msg failed:%d\n", ret_val);
		exit(-1);
	}
		return 0;
}
