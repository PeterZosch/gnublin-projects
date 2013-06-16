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
		unsigned int sb_pulse;
		unsigned int sb_space;
		unsigned int adress;
		unsigned int command;
		unsigned int stop;
};

/*struct ircstruct ircode;*/

static void ircode_out( struct ircstruct *ircode);
static int pulse_send( unsigned long lenght );
static void space_send( unsigned long slenght );
//static void ircode_in( void );
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
	abgezogen */

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
	spinlock_t spinl;
	
	unsigned int isb_pulse;
	unsigned int isb_space;
	unsigned int hadress;
	unsigned int hcommand;
	unsigned int istop;
	
	isb_pulse = ircode->sb_pulse;
	isb_space = ircode->sb_space;
	hadress = ircode->adress;
	hcommand = ircode->command;
	istop = ircode->stop;
/*
	printk( KERN_INFO "sturcht:\n" );
	printk( KERN_INFO "%i\n", ircode->sb_pulse );
	printk( KERN_INFO "%i\n", ircode->sb_space );
	printk( KERN_INFO "%i\n", ircode->adress);
	printk( KERN_INFO "%i\n", ircode->command );
	printk( KERN_INFO "%i\n", ircode->stop );

	printk( KERN_INFO "integer:\n" );
	printk( KERN_INFO "%i\n", isb_pulse );
	printk( KERN_INFO "%i\n", isb_space );
	printk( KERN_INFO "%i\n", hadress);
	printk( KERN_INFO "%i\n", hcommand );
	printk( KERN_INFO "%i\n", istop );
*/
	spin_lock_irqsave( &spinl , cpuflags );

	pulse_send( isb_pulse );
	space_send( isb_space );

 	for ( i = 15 ; i >= 0 ; i-- ) {

        binary = ( hadress >> i ) & 1;

		if ( binary ) {
			
			pulse_send( 560 );
			space_send( 1690 );

		} else {

			pulse_send( 560 );
			space_send( 560 );
		}
	

	}

    for ( i = 15 ; i >= 0 ; i-- ) {

        binary = ( hcommand >> i ) & 1;

        if ( binary ) {

            pulse_send( 560 );
            space_send( 1690 );

        } else {

            pulse_send( 560 );
            space_send( 560 );
        }
    

    }

	pulse_send( istop );

	spin_unlock_irqrestore( &spinl , cpuflags );

	gpio_set_value( GPIO_GPIO11, 0 );
}
/*
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
	request_irq( IRQ_PIN14, irq_handler, IRQF_SHARED,
				"ir2gpio",(void *)EVT_GPIO14 );
}
*/

static int device_ioctl( struct inode *inode, struct file *file,
					unsigned int cmd, unsigned long ioctl_param)
{

	struct ircstruct *ircode = kmalloc( sizeof(struct ircstruct), GFP_DMA );

	switch( cmd )
	{
//		case 69:
//			ircode_in();
//			break;

		case 42:
			if (copy_from_user( ircode, (void *)ioctl_param,
								sizeof(struct ircstruct)) != 0 ) {

				printk( KERN_INFO " Copy from userspace failed.\n" );
				return -EFAULT;
			}

		ircode_out( ircode );
			break;

		default:
			printk( KERN_INFO " unknown ioctl commando.\n" );
			break;
	}
/*
	printk( KERN_INFO "%i\n", ircode->sb_pulse );
	printk( KERN_INFO "%i\n", ircode->sb_space );
	printk( KERN_INFO "%i\n", ircode->command );
	printk( KERN_INFO "%i\n", ircode->adress);
	printk( KERN_INFO "%i\n", ircode->stop );
*/	
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
	
	//int register_value, reqerr;
	int register_value;

	register_value = register_chrdev( MAJOR_NUM, DEVICE_NAME, &fops );

	if ( register_value < 0 )
	{
		printk( KERN_ALERT "failed with %d\n", register_value);
		return register_value;
	}

	printk(KERN_INFO "ir2gpio driver registered with major number %d.\n",
			MAJOR_NUM );
/*	
	reqerr =	request_irq( IRQ_PIN14, irq_handler, IRQF_SHARED,
                "ir2gpio",(void *)EVT_GPIO14 );

	printk(KERN_INFO "ir2gpio returnvalue from irq_request = %i\n", reqerr );
*/
	return 0;


}

void cleanup_module(void)
{
	printk ( KERN_INFO "ir2gpio exit.\n" );
	
//	free_irq( IRQ_PIN14, (void *)EVT_GPIO14 );

	unregister_chrdev( MAJOR_NUM, DEVICE_NAME );
}
