#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"

void LEDkippstufe()
{
	int valueButton = -1;
	int valueRed = -1;
	int valueBlue = -1;

	MakeGpio( Gpio03 );
	MakeGpio( Gpio11 );
	MakeGpio( Gpio14 );

	DirectionGpio( Gpio03, GpioOut );
	DirectionGpio( Gpio11, GpioOut );
	DirectionGpio( Gpio14, GpioIn );

	SetValueGpio( Gpio03, GpioClear );
	SetValueGpio( Gpio11, GpioClear );
		
	for ( ; ; ) {	

		valueButton = GetGpioValue( Gpio14 );
	
		if ( valueButton == 1 ) {
		
			valueRed = GetGpioValue( Gpio03 );
			
			if ( valueRed == 1 ) {

				valueBlue = GetGpioValue( Gpio11 );
			
				if ( valueBlue == 1 ) {

					SetValueGpio( Gpio11, GpioClear );
				}
		
			} else {

				SetValueGpio( Gpio03, GpioSet );

			}

		} else if ( valueButton == 0 ) {
			

			valueBlue = GetGpioValue ( Gpio11 );
		
			if ( valueBlue == 1) {

				valueRed = GetGpioValue( Gpio03 );
			
				if ( valueRed == 1 ) {

					SetValueGpio( Gpio03, GpioClear );
				}

			} else {

				SetValueGpio( Gpio11, GpioSet );
			}

		} else {
			
			printf( "Massiver Fehler" );
			break;
		}

	}

}

