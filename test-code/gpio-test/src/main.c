#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "LEDbutton.h"
#include "LEDkippstufe.h"
#include "LEDblinkmode.h"
#include "IRfreqGen.h"
#include "IRioCheck.h"


int main()
{
  	char key;
 
    do{
        system("clear");

        printf("GPIO-Test Menue\n");
        printf("***************\n\n");
        printf("(1) LED mit Schalter bedienen\n");
        printf("(2) LED Kippstufe mit Schalter\n");
        printf("(3) LED blkinmodus mit Logik\n");
        printf("(4) IR-LED Test mit einstellbarer Frequenz\n");
        printf("(5) IR Messung der Set and Clear Zeit\n");
        printf("> ");

//        fpurge(stdin);
        do { scanf( "%c", &key ); } while ( getchar () != '\n' );
        
        switch ( key ) {
          
			case'1':	LEDbutton();
            			break;
			
			case'2':	LEDkippstufe();
            			break;

			case'3':	LEDblinkmode();
            			break;
	
			case'4':	IRfreqGen();
            			break;

			case'5':	IRioCheck();
            			break;
        }
        
    }while(key != 'q');
    return 0;
}
