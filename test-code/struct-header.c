#include <stdio.h>
#include "foo.h"
/*
struct test {

		int a;
		int b;
};
struct test tobi;
*/
int main()
{

	struct test tobi = {42, 69};
	tobi.a = 42;
	tobi.b = 69;


	printf("\nVor foo aufruf:\n" );
	printf("\na = %i", tobi.a );
	printf("\nb = %i", tobi.b );

	foo( &tobi );
	
	printf("\nNach foo aufruf:\n" );
	printf("\na = %i", tobi.a );
	printf("\nb = %i\n", tobi.b );

	return 0;
}
