#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/io.h>
#include <asm/uaccess.h>


#include <mach/hardware.h>
#include <mach/gpio.h>

#define PULSE 24

#define DEVICE_NAME "ir2gpio"
#define MAJOR_NUM 240


struct ircstruct{
        unsigned int sb_pulse;
        unsigned int sb_space;
        unsigned int adress;
        unsigned int command;
        unsigned int stop;
};


static void ircode_out( struct ircstruct *ircode );
static int pulse_send( unsigned long lenght );
static void space_send( unsigned long slenght );
static int device_ioctl( struct inode *inode, struct file *file,
                         unsigned int cmd, unsigned long ioctl_param);

static int pulse_send( unsigned long lenght )
{
	int flag;
    unsigned long t, act;

	t = PULSE / 2;
    flag = 1;
	act = 0;

/* 	ca 1us zusaetzliche Zeit bedingt durch while schleife
	daher wird mit lenght/t die haeufigkeit der zu durchlaufenden
	while-schleife ermittelt und von der eigentlichen pulse zeit
	abgezogen 
*/

    while ( act <= ( lenght - (lenght / t) ) ) {

        gpio_set_value( GPIO_GPIO11, flag );

	    udelay( t );

		act += t;

        flag = !flag;
}

	return 0;

}


static void space_send( unsigned long slenght )
{

	gpio_set_value( GPIO_GPIO11, 0 );

	if ( slenght < 2000 ) {	

		udelay( slenght );

	} else {

		mdelay( (slenght / 1000) );

	}

}

static void ircode_out( struct ircstruct *ircode )
{
	int i = 0;
	int binary = 0;
    unsigned long cpuflags;
	unsigned int hexcode;

	hexcode = ircode->command + ( ircode->adress << 16 );

	spinlock_t spinl;

	spin_lock_irqsave( &spinl , cpuflags );

	pulse_send( ircode->sb_pulse );
	space_send( ircode->sb_space );

  	for ( i = 31 ; i >= 0 ; i-- ) {

        binary = ( hexcode >> i ) & 1;

		if ( binary ) {

		//binaere 1 modelieren

			pulse_send( 560 );
			space_send( 1690 );

		} else {

		//binaere 0 modelieren

			pulse_send( 560 );
			space_send( 560 );
		}

	}

	pulse_send( ircode->stop );

	spin_unlock_irqrestore( &spinl , cpuflags );

}


static int device_ioctl( struct inode *inode, struct file *file,
unsigned int cmd, unsigned long ioctl_param )
{

    struct ircstruct *ircode = kmalloc( sizeof(struct ircstruct), GFP_DMA );

	switch( cmd ) {

		case 42:
			if (copy_from_user( ircode, (void *)ioctl_param, 
								sizeof( struct ircstruct)) != 0 ) {

				printk( KERN_INFO "Copy from userpace failed.\n" );
				return -EFAULT;
			}
			ircode_out( ircode );
			break;

		default:
			printk( KERN_INFO " unknown ioctl commando.\n" );
			break;
}

	return 0;
}

static struct file_operations fops = {
	.owner	=	THIS_MODULE,
	.write	=	NULL,
	.ioctl	=	device_ioctl,	
	.read	=	NULL,
	.poll	=	NULL,
	.open	= NULL,
	.release	=	NULL,
	.llseek	=	NULL,
};

int init_module(void)
{

	printk ( KERN_INFO "ir2gpio init.\n" );

	int register_value;

	register_value = register_chrdev( MAJOR_NUM, DEVICE_NAME, &fops );

	if ( register_value < 0 ) {

		printk( KERN_ALERT "failed with %d\n", register_value);
		return register_value;
	}

	printk( KERN_INFO "ir2mode driver registered with major number %d.\n",
			MAJOR_NUM );

	return 0;

}

void cleanup_module(void)
{
	printk ( KERN_INFO "ir2gpio exit.\n" );

	unregister_chrdev( MAJOR_NUM, DEVICE_NAME );
}
