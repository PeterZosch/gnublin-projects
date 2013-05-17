#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
 
int main()
{
	int microsec = 500;
    struct timespec ts_res, ts_start, ts_end, req;
    clock_getres(CLOCK_MONOTONIC, &ts_res);

	req.tv_sec = 0;
	req.tv_nsec = microsec * 1000L;

    printf("Resolution: %lus and %lins\n", ts_res.tv_sec, ts_res.tv_nsec);
 
//	while (1) {

	    clock_gettime(CLOCK_MONOTONIC, &ts_start);
 
//		usleep(500);
		nanosleep( &req, (struct timespec *)NULL);
 
	    clock_gettime(CLOCK_MONOTONIC, &ts_end);
 
   		 printf("Elapsed time: %luns\n", (ts_end.tv_sec - ts_start.tv_sec) * 1000000000 + ts_end.tv_nsec - ts_start.tv_nsec);

//	}
 	
    return 0;
}
