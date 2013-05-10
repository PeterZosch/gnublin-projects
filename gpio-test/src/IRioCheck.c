#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "gpio.h"

void IRioCheck()
{

		
	double sek = 0;
	double sec = 0; 
	double frq = 0.0;
	int long msek = 0;
	char key;
	clock_t t0, t1, t2, t_ges;	

	system( "clear" );

	MakeGpio( Gpio11 );

	DirectionGpio( Gpio11, GpioOut );

	SetValueGpio( Gpio11, GpioClear );

	do {

		printf( "Bitte geben sie die Frequenz in Hz ein:\n" );
		printf( ">" );
		do { scanf( "%lf", &frq ); } while ( getchar () != '\n' );		

		printf( "Frequenz der IR-LED (Gpio11): %.2lf Hz\n\n", frq);

		sek = ( 1 / frq );
 		sec = ( sek * 1000000 );
		msek = ( int long )sec;

		t0 = clock();

		SetValueGpio( Gpio11, GpioSet );
		usleep(msek);
		t1 = ( clock() - t0 );
	
		SetValueGpio( Gpio11, GpioClear );
		usleep(msek);
		t2 = ( clock() - t1 );
		
		t_ges = ( clock() - t0 );

		printf(" SetGpio = %f\n" , ((float)t1)/CLOCKS_PER_SEC );
		printf(" ClearGpio = %f\n" , ((float)t2)/CLOCKS_PER_SEC );
		printf(" Gesamtzeit = %f\n\n" , ((float)t_ges)/CLOCKS_PER_SEC );

		printf("Eine neue Freuquenz eingeben? (j/n)\n" );
		printf(">");
		do { scanf( "%c", &key ); } while ( getchar () != '\n' );
	
	} while ( key != 'n'); 	
}

