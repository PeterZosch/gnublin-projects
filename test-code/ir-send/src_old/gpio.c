#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "gpio.h"

/** \file */

/**
 * \brief  Making an GPIO
 *
 *			Making an GPIO directory
 *
 * \author kubuntufan@googlemail.com
 * 
 * \version 1.0
 * 
 * \param		[char] gpio[3]		Number of GPIO
 *
 * \return		[int] 0			Making directory OK
 * \return		[int] 1			Making directory not OK
 */

int MakeGpio(char gpio[3])
{
	FILE *datei;
	datei = fopen("/sys/class/gpio/export", "ab");
	if(datei==NULL)
	{
		return 1;
	}
	fwrite(&gpio[0],1,2,datei);
	fclose (datei);
	return 0;
}

/**
 * \brief  Destroy an GPIO
 *
 *			Destory an GPIO directory
 *
 * \author kubuntufan@googlemail.com
 * 
 * \version 1.0
 * 
 * \param		[char] gpio[3]		Number of GPIO
 *
 * \return		[int] 0			Destroying directory OK
 * \return		[int] 1			Destroying directory not OK
 */

int DestroyGpio(char gpio[3])
{
	FILE *datei;
	datei = fopen("/sys/class/gpio/unexport", "ab");
	if(datei==NULL)
	{
		return 1;
	}
	fwrite(&gpio[0],1,2,datei);
	fclose (datei);
	return 0;
}

/**
 * \brief  Direction of GPIO
 *
 * 
 *			Set Direction of GPIO
 *
 * \author kubuntufan@googlemail.com
 * 
 * \version 1.0
 * 
 * \param		[char] gpio[3]			Number of GPIO
 * \param		[char] dir[3]		Direction of GPIO
 * 
 * \return		[int] 0			Set direction OK
 * \return		[int] 1			Set direction not OK
 * 
 */

int DirectionGpio(char gpio[3], char dir[3])
{
	FILE *datei;
	char path[30];
	
	sprintf(path,"/sys/class/gpio/gpio%s/direction",&gpio[0]);
	datei = fopen(path, "ab");
	if(datei==NULL)
	{
		return 1;
	}
	fwrite(&dir[0],1,3,datei);
	fclose (datei);
	return 0;
}

/**
 * \brief  Set Value of GPIO
 *
 *			Set Value of GPIO
 *
 * \author kubuntufan@googlemail.com
 * 
 * \version 1.0
 * 
 * \param		[char] gpio[3]			Number of GPIO
 * \param		[char] val[1]		Value of GPIO
 * 
 * \return		[int] 0			Set value OK
 * \return		[int] 1			Set value not OK
 */

int SetValueGpio(char gpio[3], char val[1])
{
	FILE *datei;
	char path[30];
	
	sprintf(path,"/sys/class/gpio/gpio%s/value",&gpio[0]);
	
	datei = fopen(path, "ab");
	if(datei==NULL)
	{
		return 1;
	}
	fwrite(&val[0],1,1,datei);
	fclose (datei);
	return 0;
}

/**
 * \brief  Get Value of GPIO
 *
 *			Get Value of GPIO
 *
 * \author kubuntufan@googlemail.com
 * 
 * \version 1.0
 * 
 * \param		[char] gpio[3]			Number of GPIO
 * 
 * \return		[int] 0			Value of GPIO
 * \return		[int] 1			Value of GPIO
 * \return		[int] 2			Error
 */

int GetGpioValue(char gpio[3])
{
	FILE *datei;
	char path[30];
	char daten[2];
	
	sprintf(path,"/sys/class/gpio/gpio%s/value",&gpio[0]);
	
	datei = fopen(path, "rb");
	if(datei==NULL)
	{
		return 2;
	}
	fread(&daten,sizeof(char),2,datei);
	fclose (datei);
	
	if (daten[0] == '1')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * \brief  Set GPIO
 *
 *			Set GPIO
 *
 * \author kubuntufan@googlemail.com
 * 
 * \version 1.0
 * 
 * \param		[char] gpio[3]			Number of GPIO
 * 
 * \return		[int] 0			no Errors
 * \return		[int] 1			Errors
 */

int SetGpio(char gpio[3])
{
	MakeGpio(&gpio[0]);
	DirectionGpio(&gpio[0],GpioOut);
	SetValueGpio(&gpio[0],GpioSet);
	
	return 0;
}

/**
 * \brief  Clear Value of GPIO
 *
 *			Clear Value of GPIO
 *
 * \author kubuntufan@googlemail.com
 * 
 * \version 1.0
 * 
 * \param		[char] gpio[3]			Number of GPIO
 * 
 * \return		[int] 0			no Errors
 * \return		[int] 1			Errors
 */

int ClearGpio(char gpio[3])
{
	MakeGpio(&gpio[0]);
	DirectionGpio(&gpio[0],GpioOut);
	SetValueGpio(&gpio[0],GpioClear);
	
	return 0;
}
