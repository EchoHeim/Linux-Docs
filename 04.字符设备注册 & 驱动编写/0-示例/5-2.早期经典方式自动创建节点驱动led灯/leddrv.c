#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/mm.h>
#include <asm/io.h>
#include <linux/mm.h>
unsigned int *bass_addr=NULL;
#define MAJOR 0
#define GPM4CON (*(volatile unsigned *)bass_addr)
#define GPM4DATA	(*(volatile unsigned *)(bass_addr+1))
static int leds_open(struct inode * inode, struct file *filp)
{
	GPM4DATA &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3));  
	 return 0;
}
static int leds_close(struct inode *inode, struct file *filp)
{
	GPM4DATA |= (1<<0)|(1<<1)|(1<<2)|(1<<3); 
	return 0;
} 
static struct file_operations led_fops = {
	.owner   = THIS_MODULE,
	.open = leds_open,
	.release = leds_close,
};
static int major;
static struct class * dev_class;
static struct device * device_p;
static int __init leds_init(void)
{	
	bass_addr = (unsigned int *)ioremap(0x110002E0,0x18);
	GPM4CON &= ~(0xffff<<0);
	GPM4CON |= (1<<0)|(1<<4)|(1<<8)|(1<<12);
	GPM4DATA |= (1<<0)|(1<<1)|(1<<2)|(1<<3); 
	major = register_chrdev(MAJOR,"LED",&led_fops);
	if(major)
	{
		printk("register_chrdev success!!! %d\n",major);
		dev_class = class_create(THIS_MODULE,"ZSK");
		device_p = device_create(dev_class, NULL, MKDEV(major,0), NULL, "LED");
	}
	if(major==0)
	{
		printk("register_chrdev success!!! %d\n",MAJOR);
		dev_class = class_create(THIS_MODULE,"ZSK");
		device_p = device_create(dev_class, NULL, MKDEV(MAJOR,0), NULL, "LED");
	}
	if(major<0)
	{
		printk("register_chrdev fail!!! \n");
		iounmap(bass_addr);
	}
	
	return 0;
}
static void __exit leds_exit(void)
{
	iounmap(bass_addr);
	if(major==0)
	{
		device_destroy(dev_class,MKDEV(MAJOR,0));
		class_destroy(dev_class);
		unregister_chrdev(MAJOR,"LED");
	}	
 	if(major)  
	{  
		device_destroy(dev_class,MKDEV(major,0)); 
		class_destroy(dev_class);                    
		unregister_chrdev(major,"LED");
	}
}
module_init(leds_init);
module_exit(leds_exit);
MODULE_LICENSE("GPL");







