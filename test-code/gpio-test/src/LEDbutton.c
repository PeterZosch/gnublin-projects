#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"

void LEDbutton()
{
    int valueButton = -1; //GPIO14

	MakeGpio( Gpio11 );
	MakeGpio( Gpio14 );

    DirectionGpio( Gpio11, GpioOut );
    DirectionGpio( Gpio14, GpioIn );

    SetValueGpio( Gpio11, GpioClear );
	
	for ( ; ; ) {

		valueButton = GetGpioValue( Gpio14 );

		if ( valueButton == 1 ) {
		
			SetValueGpio( Gpio11, GpioSet );

		} else {

			SetValueGpio( Gpio11, GpioClear );

		}	

	}

}
