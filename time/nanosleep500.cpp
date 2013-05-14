#include <iostream>
#include <unistd.h>
#include <sys/time.h>                // for gettimeofday()
#include <time.h>
using namespace std;

int main()
{
	int microsec = 50; // length of time to sleep, in miliseconds
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = microsec * 1000L;

    timeval t1, t2;
    double elapsedTime;

    // start timer
    gettimeofday(&t1, NULL);

    // do something
	nanosleep(&req, (struct timespec *)NULL);

    // stop timer
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) ;   // us to ms
    cout << elapsedTime << " us.\n";

    return 0;
}
