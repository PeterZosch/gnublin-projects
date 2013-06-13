#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main () 
{
	int a, b, c, D;
	float x1, x2;

	system( "clear" );

	printf("Programm zur Loesung einer quadratischen Gleichung\n");
	printf("\nAllgemein: ax^2+bx+c\n");
	printf("\nBitte eine Zahl fuer a eingeben: ");	

	scanf("%i", &a);
	printf("\nBitte eine Zahl fuer b eingeben: ");	
	scanf("%i", &b);
	printf("\nBitte eine Zahl fuer c eingeben: ");	
	scanf("%i", &c);

	D = ( b * b ) - ( 4 * a * c );

	x1 = ( -b + sqrt(D) ) / (2 * a );
	x2 = ( -b - sqrt(D) ) / (2 * a );
	
	if( D == 0 ) {
		printf("\nx1 = x2 = %.100f\n", x1 );
	} else if ( D < 0 ) {
		printf("\nLeere Menge\n");
	} else {
		printf("\nx1 = %.100f\nx2 = %.100f\n", x1, x2);
	}		
	
	return 0;
}
