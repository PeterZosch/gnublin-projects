#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"

#define sek 250000

void LEDblinkmode()
{
	int valueButton = -1;
	int valueRed = -1;
	int valueBlue = -1;
	int i = 0;

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
		
			i = 0;

			valueRed = GetGpioValue( Gpio03 );
			valueBlue = GetGpioValue( Gpio11 );
			
			if ( (valueBlue || valueRed) == 1 ) {
				
				SetValueGpio( Gpio03, GpioClear );
				SetValueGpio( Gpio11, GpioClear );
			}

			if ( valueRed == 1 ) {
			
				valueButton = GetGpioValue( Gpio14 );

				if (valueButton == 1 ) {
				
					SetValueGpio( Gpio03, GpioClear );
					SetValueGpio( Gpio11, GpioSet );
					usleep(sek);

				}

				valueButton = GetGpioValue( Gpio14 );

				if (valueButton == 1 ) {
				
					SetValueGpio( Gpio03, GpioSet );
					SetValueGpio( Gpio11, GpioClear );
					usleep(sek);
	
				}

			} else {


				valueButton = GetGpioValue( Gpio14 );

				if (valueButton == 1 ) {
				
					SetValueGpio( Gpio03, GpioSet );
					SetValueGpio( Gpio11, GpioClear );
					usleep(sek);

				}

				valueButton = GetGpioValue( Gpio14 );

				if (valueButton == 1 ) {
				
					SetValueGpio( Gpio03, GpioClear );
					SetValueGpio( Gpio11, GpioSet );
					usleep(sek);

				}
				
			}
		
		} else if ( valueButton == 0 ) {
			
			valueRed = GetGpioValue ( Gpio03 );
			valueBlue = GetGpioValue ( Gpio11 );
					

			if ( i == 0 ) {

				SetValueGpio( Gpio03, GpioClear );
				SetValueGpio( Gpio11, GpioClear );

			}
	
			if ( valueBlue != valueRed ) {

				i = 1;

				if ( valueRed == 1) {

					SetValueGpio( Gpio03, GpioClear );
					SetValueGpio( Gpio11, GpioClear );

				} else {

					SetValueGpio( Gpio03, GpioSet );
					SetValueGpio( Gpio11, GpioSet );
		
				} 

			} else {
				
			
				valueRed = GetGpioValue ( Gpio03 );
				valueBlue = GetGpioValue ( Gpio11 );

				
				i = 1;

			}

			
		} else {
			
			printf( "Massiver Fehler" );
			break;
		}

	}

}

