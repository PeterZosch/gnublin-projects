#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/io.h>
/*#include <asm/uaccess.h>
*/
#include <mach/hardware.h>
#include <mach/gpio.h>

#define PULSE 24

#define DEVICE_NAME "ir2gpio"
#define MAJOR_NUM 240


static void ircode_out( unsigned long hexcode );
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

   	while ( act <= lenght ) {

        gpio_set_value( GPIO_GPIO11, flag );
	
   	  	udelay( t );
		
		act += t;

       	flag = !flag;
	}
	
    gpio_set_value( GPIO_GPIO11, 0 );
	return 0;

}


static void space_send( unsigned long slenght )
{

	gpio_set_value( GPIO_GPIO11, 0 );
	
		udelay( slenght );

}

static void ircode_out( unsigned long hexcode )
{
	int i = 0;
	int binary = 0;
    unsigned long cpuflags;
	spinlock_t spinl;
	
	spin_lock_irqsave( &spinl , cpuflags );

	pulse_send( 9000 );
	space_send( 4500 );

 	for ( i = 31 ; i >= 0 ; i-- ) {

        binary = ( hexcode >> i ) & 1;

		if ( binary ) {
			
			pulse_send( 510 );
			space_send( 1690 );

		} else {

			pulse_send( 510 );
			space_send( 560 );
		}

	}

	spin_unlock_irqrestore( &spinl , cpuflags );
}


static int device_ioctl( struct inode *inode, struct file *file,
					unsigned int cmd, unsigned long ioctl_param)
{

	switch( cmd )
	{
		case 42:
			ircode_out( ioctl_param );
			break;
		default:
			printk( KERN_INFO " unknown ioctl commando.\n" );
			break;
	}

	return 0;
}

static struct file_operations fops = {
	.owner		=	THIS_MODULE,
	.write		=	NULL,
	.ioctl		=	device_ioctl,	
	.read		=	NULL,
	.poll		=	NULL,
	.open		= 	NULL,
	.release	=	NULL,
	.llseek		=	NULL,
};

int init_module(void)
{

	printk ( KERN_INFO "ir2gpio init.\n" );
	
	int register_value;

	register_value = register_chrdev( MAJOR_NUM, DEVICE_NAME, &fops );

	if ( register_value < 0 )
	{
		printk( KERN_ALERT "failed with %d\n", register_value);
		return register_value;
	}

	printk(KERN_INFO "ir2mode driver registered with major number %d.\n",
			MAJOR_NUM );

	return 0;


}

void cleanup_module(void)
{
	printk ( KERN_INFO "ir2gpio exit.\n" );

	unregister_chrdev( MAJOR_NUM, DEVICE_NAME );
}
