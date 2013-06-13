#include <stdio.h>

struct test {

		int a;
		int b;
};

void foo ( struct test *tobi );

int main()
{

	struct test tobi = {42, 69};

	printf("\nVor foo aufruf:\n" );
	printf("\na = %i", tobi.a );
	printf("\nb = %i", tobi.b );

	foo( &tobi );
	
	printf("\nNach foo aufruf:\n" );
	printf("\na = %i", tobi.a );
	printf("\nb = %i\n", tobi.b );

	return 0;
}

void foo ( struct test *tobi )
{
	int x = 1;
	int y = 3;

	printf("\nIn foo aufruf:\n" );
	printf("\na = %i", (*tobi).a );
	printf("\nb = %i", (*tobi).b );

	(*tobi).a = x;
	(*tobi).b = y;

}

	
