#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define GPX3REG_BASEADDR 0x11000C60

#define rGPX3CON (*(volatile unsigned long *)(gpx3reg_viraddr+0))
#define rGPX3DAT (*(volatile unsigned long *)(gpx3reg_viraddr+1))
#define rGPX3PUD (*(volatile unsigned long *)(gpx3reg_viraddr+2))

static unsigned long *gpx3reg_viraddr = NULL;

static int mykey_open(struct inode *inod, struct file *fil)
{
	return 0;
}


static ssize_t mykey_read(struct file *fil, char __user *buf, size_t count, loff_t *ops)
{
	int key_val;
	if(!(rGPX3DAT & (1<<2)))
		key_val = 1;
	else if(!(rGPX3DAT & (1<<3)))
		key_val = 2;
	else if(!(rGPX3DAT & (1<<4)))
		key_val = 3;
	else if(!(rGPX3DAT & (1<<5)))
		key_val = 4;
	else
		key_val = 0;
	printk("key_val = %d\n",key_val);
	return 0;
}
	
static int mykey_close(struct inode *inod, struct file *fil)
{

	return 0;
}


static struct file_operations mykey_fops =
{
	.owner   = THIS_MODULE,
	.open    = mykey_open,
	.release = mykey_close,
	.read    = mykey_read,
};

static struct miscdevice mykey_misc =
{
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "mykey",
	.fops  = &mykey_fops,
};

static int mykey_init(void)
{
	misc_register(&mykey_misc);

	gpx3reg_viraddr = (unsigned long *)ioremap(GPX3REG_BASEADDR,12);

	rGPX3CON &=~(0xFFFF<<8);
	rGPX3PUD &=~(0xFF<<4);
	rGPX3PUD |= 0xFF<<4;
	
	return 0;
}

static void mykey_exit(void)
{
	iounmap(gpx3reg_viraddr);
	misc_deregister(&mykey_misc);
}

module_init(mykey_init);
module_exit(mykey_exit);
MODULE_LICENSE("GPL");
