#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
static unsigned char led_statu=0;
unsigned int *base_addr = 0;
#define GPM4BASE   0x110002E0  //GPM4CON物理地址
#define GPM4SIZE   0x18        //GPM4占用空间大小
#define rGPM4CON      (*(volatile unsigned int*)(base_addr + 0))	
#define rGPM4DAT      (*(volatile unsigned int*)(base_addr + 1))
#define rGPM4PUD		  (*(volatile unsigned int*)(base_addr + 2))
static int leds_open(struct inode * inode,struct file *filp)
{
	rGPM4DAT &= ~(1<<0);
	led_statu = 1;	
	 return 0;
}
static int leds_close(struct inode *inode,struct file *filp)
{
	rGPM4DAT |= (1<<0);
	led_statu = 0;	
	return 0;
} 
static int led_read(struct file *filp,char __user *buff,size_t count,loff_t *offset)
{
	unsigned long r_ret;
	unsigned char c_bu=1;
	copy_to_user(buff,&led_statu,1);
	return 0;
}
static int led_write(struct file *fp,const char __user *user_buf,size_t count,loff_t *offset)
{
	static unsigned char c_buf;
	static unsigned long ret;
	ret=copy_from_user(&c_buf,user_buf,1);
	if(ret==0)
	{
		if(c_buf == 1)
		{
				rGPM4DAT &= ~(1<<0);
				led_statu = 1;	
		}
		else
		{
			 	rGPM4DAT |= (1<<0);
				led_statu = 0;	
		}	
	}
	return 0;
}
static struct file_operations led_fops = {
	.owner   = THIS_MODULE,
	.open    = leds_open,
	.release = leds_close,
	.read = led_read,
	.write = led_write,
};

 struct miscdevice misc = {
	.name  = "LED",
	.minor = 255,	
	.fops  = &led_fops,
};
static int __init leds_init(void)
{
	int ret;
	base_addr  = (unsigned int *)ioremap(GPM4BASE,GPM4SIZE);
	rGPM4CON &= ~((0xf<<3*4)|(0xf<<2*4)|(0xf<<1*4)|(0xf<<0*4));
	rGPM4CON |=  ((1  <<3*4)|(1  <<2*4)|(1  <<1*4)|(1  <<0*4));	
	rGPM4DAT |= ((1<<0)|(1<<1)|(1<<2)|(1<<3));
	led_statu = 0;	
	ret = misc_register(&misc);
	if(ret<0)
	{
		printk("register fail!!!\n");
		return -1;
	}
	printk("ok!!!\n");
	return 0;
}
static void __exit leds_exit(void)
{
	iounmap(base_addr);//取消映射
	misc_deregister(&misc);
	printk("bye bye!!!\n");
}
module_init(leds_init);
module_exit(leds_exit);
MODULE_LICENSE("GPL");







