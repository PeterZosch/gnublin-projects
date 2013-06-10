#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/irq.h>
#include <linux/init.h>
#include <linux/interrupt.h>

#include <asm/io.h>
#include <mach/hardware.h>
#include <mach/gpio.h>
#include <mach/irqs.h>
#include <asm/uaccess.h>

#define PULSE 24

#define DEVICE_NAME "ir2gpio"
#define MAJOR_NUM 240

struct ircstruct{
		unsigned int header;
		unsigned int adress;
		unsigned int command;
		unsigned int end;
};

unsigned int h = 0;
unsigned int a = 0;
unsigned int c = 0;
unsigned int e = 0;

/*struct ircstruct ircode;*/

static void ircode_out( unsigned long hexcode );
static int pulse_send( unsigned long lenght );
static void space_send( unsigned long slenght );
static void ircode_in( void );
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

static irqreturn_t irq_handler( int irq, void *dev_id )
{

	struct timeval tv;
	
	do_gettimeofday(&tv);

	printk( KERN_INFO "%08u.%06u s\n", (int)(tv.tv_sec % 100000000),
			(int)(tv.tv_usec));
	
	return ( IRQ_HANDLED );

}

static void ircode_in( void )
{
/*	request_irq( IRQ_PIN14, irq_handler, IRQF_SHARED,
				"ir2gpio",(void *)EVT_GPIO14 );
*/}

static int device_ioctl( struct inode *inode, struct file *file,
					unsigned int cmd, unsigned long ioctl_param)
{
	int rc;
	struct ircstruct *ircode = kmalloc(sizeof(struct ircstruct), GFP_DMA);

	

	switch( cmd )
	{
		case 42:
			ircode_out( ioctl_param );
			break;
		case 69:
			ircode_in();
			break;
		case 77:
		
		rc = copy_from_user( ircode, (void *)ioctl_param, sizeof(struct ircstruct));
		h = ircode->header;
   	 	a = ircode->adress;
   		c = ircode->command;
	    e = ircode->end;

			break;
		default:
			printk( KERN_INFO " unknown ioctl commando.\n" );
			break;
	}

    printk(KERN_INFO "\nheader = %i", ircode->header);
    printk(KERN_INFO "\nadress = %i", ircode->adress);
    printk(KERN_INFO "\ncommand = %i", ircode->command);
    printk(KERN_INFO "\nend = %i", ircode->end);

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
	
	int register_value, reqerr;

	register_value = register_chrdev( MAJOR_NUM, DEVICE_NAME, &fops );

	if ( register_value < 0 )
	{
		printk( KERN_ALERT "failed with %d\n", register_value);
		return register_value;
	}

	printk(KERN_INFO "ir2gpio driver registered with major number %d.\n",
			MAJOR_NUM );
	
	reqerr =	request_irq( IRQ_PIN14, irq_handler, IRQF_SHARED,
                "ir2gpio",(void *)EVT_GPIO14 );

	printk(KERN_INFO "ir2gpio returnvalue from irq_request = %i\n", reqerr );

	return 0;


}

void cleanup_module(void)
{
	printk ( KERN_INFO "ir2gpio exit.\n" );
	
	free_irq( IRQ_PIN14, (void *)EVT_GPIO14 );

	unregister_chrdev( MAJOR_NUM, DEVICE_NAME );
}
