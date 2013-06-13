#include <stdio.h>
#include "foo.h"
/*
struct test {

	int a;
	int b;
};
*/
void foo ( struct test *tobi )
//void foo ( )
{
    int x = 1;
    int y = 3;

    printf("\nIn foo aufruf:\n" );
    printf("\na = %i", (*tobi).a );
    printf("\nb = %i", (*tobi).b );

    (*tobi).a = x;
    (*tobi).b = y;

}

