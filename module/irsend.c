#include <stdio.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */

#define DEVICE_FILE_NAME "/dev/ir2gpio"

main()
{
	int file_desc, ret_val, i;

	int code[34] = {0,1,0,1,0,1,1,1,1,0,1,0,1,0,0,0,0,1,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,1,};
	
	i = 1;	

	file_desc = open(DEVICE_FILE_NAME, 0);

	if (file_desc < 0) {
		printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
		exit(-1);
	}

	ret_val = ioctl(file_desc, 42, 9000);

	ret_val = ioctl(file_desc, 69, 4500);
	
	for( i = 0 ; i <= 33 ; i++) {
	
		if ( code[i] == 0 ) {
			
			ret_val = ioctl(file_desc, 42, 560);

			ret_val = ioctl(file_desc, 69, 560);

		} else {

			ret_val = ioctl(file_desc, 42, 560);

			ret_val = ioctl(file_desc, 69, 1690);
		}

	}
		

	if (ret_val < 0) {
		printf("ioctl_set_msg failed:%d\n", ret_val);
		exit(-1);
	}
		return 0;
}
