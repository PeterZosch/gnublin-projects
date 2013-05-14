#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
/* #include <asm/delay.h> */

/* LPC3131 UM chapter 15 */
#define IOCONFIG    0x13003000
#define FBLO_GPIO   0x1C0  /* GPIO functional block */

/* offset in GPIO functional block  */
#define PINS        0x00
#define MODE0       0x10  
#define MODE0_SET   0x14
#define MODE0_RESET 0x18
#define MODE1       0x20  
#define MODE1_SET   0x24
#define MODE1_RESET 0x28

void *mymem;
/*int getInput(void *mymem);*/
void byebye(void);

/*int getInput(void *mymem)
{
	unsigned int in;

	for(;;){
    
	if( (*(unsigned int *)(mymem + FBLO_GPIO) & ( 1 << 8 )) == 0 )
    
	}        
}*/

int main()
{
    int mem_fd;
    atexit(byebye);
    if ((mem_fd = open("/dev/mem", O_RDWR)) < 0) {
        printf("can't open /dev/mem \n");
        exit(-1);
    }
    printf("mem_fd = %d\n", mem_fd);
    printf("getpagesize() -> %d\n", getpagesize());
    mymem = mmap(0, 
                 getpagesize(), 
                 PROT_READ|PROT_WRITE, 
                 MAP_SHARED, 
                 mem_fd, 
                 IOCONFIG);
    if (mymem == MAP_FAILED) {
        printf("mmap error %d\n", errno);
        exit(-1);
    }
    else {
        printf("mymem = 0x%x\n", (unsigned int)mymem);
    }
		*(unsigned int *)(mymem + FBLO_GPIO + MODE0_RESET) = ( 1 << 8 );
        *(unsigned int *)(mymem + FBLO_GPIO + MODE1_RESET) = ( 1 << 8 );
		
		
		while( *(unsigned int *)(mymem + FBLO_GPIO) & ( 1 << 8 ));
/*		printf("%i\n", getInput(mymem)); */

    return 0;
}

void byebye()
{
    printf("cleaning up\n");
    /* when not explicitly given, munmap() will automatically
       be called on exit (see 'man munmap') */
    munmap(mymem, getpagesize()); 
}
