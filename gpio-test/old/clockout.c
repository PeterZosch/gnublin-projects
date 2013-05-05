#include <stdio.h>
#include "gpio.h"

/** \file */

/**
 * \brief  Generate an Frequency
 *
 *			Generate an Frequency
 *
 * \author kubuntufan@googlemail.com
 * 
 * \version 1.0
 * 
 * \param		[char] gpio[3]		Number of GPIO
 * \param		[unsigned long int] Freq	Frequency in Herz
 * \param		[int] count		Number of Periods
 * 
 * \return		[int] 0			Making directory OK
 */

int FrequOut(char gpio[3], unsigned long int Freq, int count)
{
int i=0;
unsigned long int t1=0,t2=0;

if(Freq < 1000)
{ 
	t1=(((double)1/(double)Freq)*1000000)/2;
	t2=t1;
}

if(Freq >=1000)
{
	t1=((((double)1/(double)Freq))*1000000)/2;
	t2=t1;
}

if(Freq >= 1000000)
{ 
	t1=(((double)1/(double)Freq)*1)/2;
	t2=t1;
}

for (i=0;i<=count;i++)
{
	SetGpio(&gpio[0]);
	usleep(t1);
	ClearGpio(&gpio[0]);
	usleep(t2);
}

return 0;
}
