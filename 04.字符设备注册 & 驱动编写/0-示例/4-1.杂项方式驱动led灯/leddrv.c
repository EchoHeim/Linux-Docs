#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
unsigned int *base_addr = 0;

#define GPM4BASE   0x110002E0  //GPM4CON物理地址
#define GPM4SIZE   0x18        //GPM4占用空间大小
#define rGPM4CON      (*(volatile unsigned int*)(base_addr + 0))	
#define rGPM4DAT      (*(volatile unsigned int*)(base_addr + 1))	

static int leds_open(struct inode * inode, struct file *filp)
{
	 rGPM4DAT &= ~(1<<0);  
  	 rGPM4DAT &= ~(1<<1);  
  	 rGPM4DAT &= ~(1<<2);  
  	 rGPM4DAT &= ~(1<<3);  
	 printk("open leds is calling\n");	
	 return 0;
}
static int leds_close(struct inode *inode, struct file *filp)
{
	rGPM4DAT |=  (1 << 0 | 1 << 1 | 1 << 2 | 1 << 3); 	
	printk("close leds is calling\n");	
	return 0;
} 
static struct file_operations led_fops = {
	.owner   = THIS_MODULE,
	.open    = leds_open,
	.release = leds_close,
};

 struct miscdevice misc = {
	.name  = "LED",
	.minor = 255,	
	.fops  = &led_fops,
};
static int __init leds_init(void)
{
	int ret;
	printk("LED is call\n");
	base_addr    = (unsigned int *)ioremap (GPM4BASE, GPM4SIZE);
	/* 1、设置GPM4CON为输出模式 */
	rGPM4CON &= ~((0xf<<3*4)|(0xf<<2*4)|(0xf<<1*4)|(0xf<<0*4));
	rGPM4CON |=  ((1  <<3*4)|(1  <<2*4)|(1  <<1*4)|(1  <<0*4));	
	//
	rGPM4DAT |=  (1 << 0 | 1 << 1 | 1 << 2 | 1 << 3); 	
	ret = misc_register(&misc);         //注册杂项设备	
	if(ret < 0)
	{
		printk("err\n");
		return -1;
	}
	printk("LED is success\n");
	return 0;
}
static void __exit leds_exit(void)
{
	printk("LED is end\n");
	iounmap(base_addr);//取消映射
	misc_deregister(&misc);                                
	printk("LED end success\n");
}
module_init(leds_init);
module_exit(leds_exit);


MODULE_LICENSE("GPL");







