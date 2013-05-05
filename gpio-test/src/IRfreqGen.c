#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"

void IRfreqGen()
{

		
	double sek = 0;
	double sec = 0; 
	double frq = 0.0;
	int long msek = 0;
	
	system( "clear" );

	MakeGpio( Gpio11 );

	DirectionGpio( Gpio11, GpioOut );

	SetValueGpio( Gpio11, GpioClear );

	printf( "Bitte geben sie die Frequenz in Hz ein:\n" );
	printf( ">" );
	scanf( "%lf", &frq );

	printf( "Die IR-LED (Gpio11) blinkt mit einer Frequenz von %.2lf Hz\n\n", frq);
	printf( "zum Beenden Ctrl + C drücken\n" );

	sek = ( 1 / frq );
 	sec = ( sek * 1000000 );
	msek = ( int long )sec;

	for ( ; ; ) {	

		SetValueGpio( Gpio11, GpioSet );
		usleep(msek);

		SetValueGpio( Gpio11, GpioClear );
		usleep(msek);

	}

}

