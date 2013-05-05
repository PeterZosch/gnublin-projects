#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "gpio.h"

#define HBL 250000 

void pulse();
void sendHigh();
void sendLow();
void setHigh();
void setLow();

int main() {
    
	unsigned int b = 0;
    
	int ircode[16] = {1,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1};

	int n = 0;
    
	MakeGpio( Gpio11 );
	DirectionGpio( Gpio11, GpioOut );
	SetValueGpio( Gpio11, GpioClear );

	for ( n = 0 ; n < 16 ; n++ ) {
        
		b = ircode[n];
        
		if (b == 1){
            
			sendHigh();
            
		} else if ( b == 0 ) {
            
			sendLow();
		}	
	}

	printf("Fertig !");

	return 0;    
}

void pulse()
{  
   	int i = 0;
 
	for( i=0 ; i < 32 ; i++) {

		setHigh();
		usleep(27.78);
    
		setLow();
		usleep(27.78);

	}
}

void sendHigh()
{    
	setLow();
	usleep( HBL );
   
	pulse();
    
}

void sendLow()
{
	pulse();
    
	setLow();
	usleep( HBL );    
}


void setHigh()
{
	SetValueGpio( Gpio11, GpioSet );
    
}

void setLow()
{
	SetValueGpio( Gpio11, GpioClear );    
}
