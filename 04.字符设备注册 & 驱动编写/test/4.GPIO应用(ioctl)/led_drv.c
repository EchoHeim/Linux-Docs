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

static int led_open(struct inode *num, struct file *file)
{
	return 0;
}

static int led_close(struct inode *num, struct file *file)
{
	return 0;
}

	//ioctl函数有bug，第二个参数不能是 2 (被系统占用！)。
long led_ioctl(struct file *fd, unsigned int cmds, unsigned long datas)
{
	if(datas==1)
	{
		switch(cmds)
		{
			case 11:GPM4_DAT &= ~(0x1<<0);break;
			case 12:GPM4_DAT &= ~(0x1<<1);break;
			case 13:GPM4_DAT &= ~(0x1<<2);break;
			case 14:GPM4_DAT &= ~(0x1<<3);break;
		}
	}
	else
	{
		switch(cmds)
		{
			case 11:GPM4_DAT |= (0x1<<0);break;
			case 12:GPM4_DAT |= (0x1<<1);break;
			case 13:GPM4_DAT |= (0x1<<2);break;
			case 14:GPM4_DAT |= (0x1<<3);break;
		}
	}
	return 0;
}

static struct file_operations led_fop=
{
	.owner = THIS_MODULE,
	.open = led_open,
	.release = led_close,
	.unlocked_ioctl = led_ioctl,
};

static struct miscdevice misc=
{
	.name="hello_led",
	.minor = 255,
	.fops = &led_fop,
};

static int __init hello_led(void)
{
	led_base=(unsigned int *)ioremap(0x110002E0,0x18);
	GPM4_CON &= ~(0xffff<<0);
	GPM4_CON |= (0x1111<<0);
	GPM4_DAT |= (0xf<<0);
	
	misc_register(&misc);		//ÔÓÏîÉè±¸×¢²áledµÆ
	return 0;
}
static void __exit bye_led(void)
{
	misc_deregister(&misc);	
	iounmap(led_base);
	printk("bye,bye!\n");
}

module_init(hello_led);
module_exit(bye_led);
MODULE_LICENSE("GPL");



