#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "gpio.h"

#define HBL 250000 

void pulse();
void sendHigh();
void sendLow();
void setHigh();
void setLow();

int main() {
    
	unsigned int b = 0;
    
	int ircode[14] = {1,1,0,1,0,1,0,0,1,0,1,0,0,1};

	int n = 0;
    
	MakeGpio( Gpio11 );
	DirectionGpio( Gpio11, GpioOut );
	SetValueGpio( Gpio11, GpioClear );

	clock_t t;

	t = clock();

	for ( n = 0 ; n < 14 ; n++ ) {
        
		b = ircode[n];
        
		if (b == 1){
            
			sendHigh();
            
		} else if ( b == 0 ) {
            
			sendLow();
		}	
	}

	t = clock() - t ;


	printf("Fertig in %f sec" , ((float)t)/CLOCKS_PER_SEC );

	return 0;    
}

void pulse()
{  
   	int i = 0;
 
	for( i=0 ; i < 32 ; i++) {

		setHigh();
		usleep(7);
    
		setLow();
		usleep(21);

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
