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

	struct ircstruct{
					unsigned int sb_pulse;
					unsigned int sb_space;
					unsigned int adress;
					unsigned int command;
					unsigned int stop;
	};

//	struct ircstruct ircode;
	struct ircstruct ircode = { 9000, 4500, 0x0008, 0x18E7, 560 };
/*	ircode = malloc( sizeof( struct ircstruct ));*/

/*	ircode.header = 42;
	ircode.adress = 69;
	ircode.command = 3;
	ircode.end = 4;	

	printf( "sb_pulse: %i @ %p\n", ircode.sb_pulse, &ircode.sb_pulse );
	printf( "sb_space: %i @ %p\n", ircode.sb_space, &ircode.sb_space );
	printf( "adress %i @ %p\n", ircode.adress, &ircode.adress );
	printf( "command: %i\n", ircode.command );
	printf( "stop: %i\n", ircode.stop );
	printf( "sizeof struct %i\n", sizeof( struct ircstruct ));
*/	
	file_desc = open(DEVICE_FILE_NAME, 0);

	if (file_desc < 0) {
		printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
		exit(-1);
	}

	ret_val = ioctl(file_desc, 42, &ircode);

	printf( "sended ircode struct @%p\n", &ircode);

	if (ret_val < 0) {
		printf("ioctl_set_msg failed:%d\n", ret_val);
		exit(-1);
	}
		return 0;
}
