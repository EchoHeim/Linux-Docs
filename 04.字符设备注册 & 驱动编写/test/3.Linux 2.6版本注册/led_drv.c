#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/cdev.h>  
#include <linux/device.h> 
static unsigned int *led_base=NULL;
#define GPM4_CON (*(volatile unsigned int*)(led_base+0))
#define GPM4_DAT (*(volatile unsigned int*)(led_base+1))

static struct class *led_class=NULL;
static char *leds_name[]={"led1","led2","led3","led4"};

static dev_t leds_dev;			//定义设备号；
static int led_major = 0;		//定义主设备号；
static int led_minor = 0;		//定义次设备号；

static int led_open(struct inode *node, struct file *file)
{
	led_minor=iminor(node);
	return 0;
}

static int led_close(struct inode *node, struct file *file)
{
	led_minor=iminor(node);
	return 0;
}
ssize_t led_write(struct file *fd, const char __user *name, size_t size, loff_t * lofset)
{
	unsigned char led_num;
	unsigned long return_val=0;
	return_val = copy_from_user(&led_num,name,1);
	if(led_num)
		GPM4_DAT &= ~(1<<led_minor);
	else
		GPM4_DAT |= (1<<led_minor);
	return 0;
}

static struct file_operations led_fop=
{
	.owner = THIS_MODULE,
	.open = led_open,
	.release = led_close,
	.write = led_write,
};

static struct cdev leds_cdev=
{
	.owner = THIS_MODULE,
	.count = 4,
};

static int __init hello_led(void)
{
	int i=0;
	led_base=(unsigned int *)ioremap(0x110002E0,0x16);
	GPM4_CON &= ~(0xffff<<0);
	GPM4_CON |= (0x1111<<0);
	GPM4_DAT |= (0xf<<0);	
	cdev_init(&leds_cdev,&led_fop);
	if(led_major)
	{
		leds_dev=MKDEV(led_major,0);
		register_chrdev_region(leds_dev,4,"leds");
	}
	else
		alloc_chrdev_region(&leds_dev,0,4,"leds");
	cdev_add(&leds_cdev,leds_dev,4);

	led_class=class_create(THIS_MODULE,"hsl");
	for(i=0;i<4;i++)
		device_create(led_class,NULL,leds_dev+i,NULL,leds_name[i]);
	return 0;
}

static void __exit bye_led(void)
{
	int i=0;
	for(i=0;i<4;i++)
		device_destroy(led_class,leds_dev+i);
	class_destroy(led_class);
	cdev_del(&leds_cdev);
	unregister_chrdev_region(leds_dev,4);
	iounmap(led_base);
	printk("bye,bye!\n");
}

module_init(hello_led);
module_exit(bye_led);
MODULE_LICENSE("GPL");



