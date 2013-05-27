#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <asm/io.h>

#include <mach/hardware.h>
#include <mach/gpio.h>

#define PULSE 24


int pulse_send( unsigned int lenght )
{
	int flag;
    unsigned long t, act;

    t = PULSE / 2;
    flag = 1;
	act = 0;

    while ( act <= lenght )
    {
        gpio_set_value( GPIO_GPIO11, flag );
        udelay(t);

		act += t;

        flag = !flag;
    }
	
	return 0;

}


void space_send( unsigned int slenght )
{

	gpio_set_value( GPIO_GPIO11, 0 );

	udelay(slenght);

} 

int init_module(void)
{

	printk ( KERN_INFO "IRmod init.\n" );
	
	unsigned int i=1000;
	
	while( i-- )
	{
		pulse_send( 560 );

		space_send( 560 );
	}

	return 0;

}

void cleanup_module(void)
{

	printk ( KERN_INFO "IRmode exit.\n" );
}
