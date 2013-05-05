#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define HBL 888.888

void pulse();
void sendHigh();
void sendLow();
void setHigh();
void setLow();

int main(){
    
unsigned int b = 0;
    
int ircode[16] = {1,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1};
    
	for( int n = 0 ; n < 16 ; n++ ){
        
		b = ircode[n];
        
		if (b == 1){
            
			sendHigh();
            
		}else if(b == 0){
            
			sendLow();
	}	
}

	printf("Fertig !");
    
}

void pulse(){
  
    
	for( int i=0 ; i < 32 ; i++){

		setHigh();
		usleep(27.78);
    
		setLow();
		usleep(27.78);

	}

}

void sendHigh(){
    
	setLow();
	usleep(HBL);
   
	pulse();
    
}

void sendLow(){
	pulse();
    
	setLow();
	usleep(HBL);
    
}


void setHigh(){
    
}

void setLow(){
    
}
