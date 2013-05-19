#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define nano	500000 
#define micro	500

int main()
{
    struct timespec ts_res, ts_start, ts_end;
    clock_getres(CLOCK_MONOTONIC, &ts_res);

	struct timespec ts = { .tv_sec = 0, .tv_nsec = nano };

    printf("Resolution: %lus and %lins\n", ts_res.tv_sec, ts_res.tv_nsec);

	//usleep zeitmessung 
	printf("\nMessung mit usleep:\n");

	    clock_gettime(CLOCK_MONOTONIC, &ts_start);
	   	usleep(micro); 
	    clock_gettime(CLOCK_MONOTONIC, &ts_end);
   		printf("%luns\n", (ts_end.tv_sec - ts_start.tv_sec) * 1000000000 + ts_end.tv_nsec - ts_start.tv_nsec);
		
	
	//nanosleep zeitmessung
	printf("\nMessung mit nanosleep:\n");

		clock_gettime(CLOCK_MONOTONIC, &ts_start);
		nanosleep( &ts, (struct timespec *) NULL );
	    clock_gettime(CLOCK_MONOTONIC, &ts_end);
 
   		printf("%luns\n", (ts_end.tv_sec - ts_start.tv_sec) * 1000000000 + ts_end.tv_nsec - ts_start.tv_nsec);


	//clock_nanosleep zeitmessung
	printf("\nMessung mit clock_nanosleep:\n");

		clock_gettime(CLOCK_MONOTONIC, &ts_start);
		clock_nanosleep( CLOCK_MONOTONIC, 0, &ts, NULL );
	    clock_gettime(CLOCK_MONOTONIC, &ts_end);
 
   		printf("%luns\n", (ts_end.tv_sec - ts_start.tv_sec) * 1000000000 + ts_end.tv_nsec - ts_start.tv_nsec);

 	
    return 0;
}
