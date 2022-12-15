#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>  
#include <linux/device.h>
#include <asm/io.h>
#include <linux/mm.h>
unsigned int *bass_addr=NULL;
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
static struct class * dev_class;
static struct device * device_p;
static dev_t dev;
static struct cdev led_cedv;
static int __init leds_init(void)
{		
	//1、映射地址
	bass_addr = (unsigned int *)ioremap(0x110002E0,0x18);
	GPM4CON &= ~(0xffff<<0);
	GPM4CON |= (1<<0)|(1<<4)|(1<<8)|(1<<12);
	GPM4DATA |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
	dev = MKDEV(250,0);
	led_cedv.owner = THIS_MODULE;
	led_cedv.dev =  dev;
	led_cedv.count = 1;
	cdev_init(&led_cedv,&led_fops);
	//申请设备号
	register_chrdev_region(dev,1,"LED");
	//注册设备
	cdev_add(&led_cedv,dev,1);
	//创建设备类指针	
	dev_class = class_create(THIS_MODULE,"ZSK");
	//创建节点
	device_p = device_create(dev_class, NULL,dev, NULL, "LED");
	return 0;
}
static void __exit leds_exit(void)
{
	//取消映射地址	摧毁节点	删除类		分离设备	删除设备号
	iounmap(bass_addr);
	device_destroy(dev_class,dev); 
	class_destroy(dev_class);                    
	cdev_del(&led_cedv);	
	unregister_chrdev_region(dev,1);
}
module_init(leds_init);
module_exit(leds_exit);
MODULE_LICENSE("GPL");







