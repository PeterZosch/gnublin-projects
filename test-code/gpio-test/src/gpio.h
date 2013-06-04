/** \file */

/** @mainpage Use the Framework
 *  
 *  @section sec1 Howto Include 
 *	#include "GPIO API/gpio.h"
 * 
 * #include "GPIO API/clockout.h"
 * 
 * int main (void)
 * 
 * {
 * 
 * SetGpio(Gpio03);
 * 
 * FrequOut(Gpio03, 2, 10);
 * 
 * return 0;
 * 
 * }
 * 
 */

//Define GPIO Numbers
/** Macro GPIO3 */
#define Gpio03 "3"
/** Macro GPI011 */
#define Gpio11 "11"
/** Macro GPI014 */
#define Gpio14 "14"
/** Macro GPI015 */
#define Gpio15 "15"

//Define GPIO Direction
/** Macro GPIO Direction out */
#define GpioOut "out"
/** Macro GPIO Direction in */
#define GpioIn "in"

//Define GPIO State
/** Macro GPIO State 1 */
#define GpioSet "1"
/** Macro GPIO State 0 */
#define GpioClear "0"

extern int MakeGpio(char gpio[3]);
extern int DestroyGpio(char gpio[3]);
extern int DirectionGpio(char gpio[3], char dir[3]);
extern int SetValueGpio(char gpio[3], char val[1]);
extern int GetGpioValue(char gpio[3]);
extern int SetGpio(char gpio[3]);
extern int ClearGpio(char gpio[3]);
