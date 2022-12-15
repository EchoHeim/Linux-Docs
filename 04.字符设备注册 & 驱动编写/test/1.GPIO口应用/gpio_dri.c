#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>

static unsigned int *led_base=NULL;
static unsigned int *beep_base=NULL;
static unsigned int *key_base=NULL;

#define GPM4_CON (*(volatile unsigned int*)(led_base+0))
#define GPM4_DAT (*(volatile unsigned int*)(led_base+1))
#define GPD0_CON (*(volatile unsigned int*)(beep_base+0))
#define GPD0_DAT (*(volatile unsigned int*)(beep_base+1))

#define GPX3_CON (*(volatile unsigned int*)(key_base+0))
#define GPX3_DAT (*(volatile unsigned int*)(key_base+1))
#define GPX3_PUD (*(volatile unsigned int*)(key_base+2))

static int dri_open(struct inode *num, struct file *file)
{
	return 0;
}

static int dri_close(struct inode *num, struct file *file)
{
	return 0;
}
ssize_t dri_read(struct file *a, char __user *b, size_t c, loff_t *d)
{
	if(!((GPX3_DAT>>2)&1))		//第一个按键按下；
	{
		while(!((GPX3_DAT>>2)&1));
		printk("key1 is pressing!\n");
		GPM4_DAT |= (0xf<<0);
		GPM4_DAT &=~(1<<0);
		GPD0_DAT |=(1<<0);		//蜂鸣器响；
	}
	else if(!((GPX3_DAT>>3)&1))
	{
		while(!((GPX3_DAT>>3)&1));
		printk("key2 is pressing!\n");
		GPM4_DAT |= (0xf<<0);
		GPM4_DAT &=~(1<<1);
		GPD0_DAT &=~(1<<0);
	}
	else if(!((GPX3_DAT>>4)&1))
	{
		while(!((GPX3_DAT>>4)&1));
		printk("key3 is pressing!\n");
		GPM4_DAT |= (0xf<<0);
		GPM4_DAT &=~(1<<2);
		GPD0_DAT &=~(1<<0);
	}
	else if(!((GPX3_DAT>>5)&1))
	{
		while(!((GPX3_DAT>>5)&1));
		printk("key4 is pressing!\n");
		GPM4_DAT |= (0xf<<0);
		GPM4_DAT &=~(1<<3);
		GPD0_DAT |=(1<<0);
	}	
}

static struct file_operations dri_fop=
{
	.owner = THIS_MODULE,
	.open = dri_open,
	.release = dri_close,
	.read = dri_read,
};

static struct miscdevice misc=
{
	.name="hello_dri",
	.minor = 255,
	.fops = &dri_fop,
};

static int __init hello_dri(void)
{
	led_base=(unsigned int *)ioremap(0x110002E0,0x18);
	GPM4_CON &= ~(0xffff<<0);
	GPM4_CON |= (0x1111<<0);
	GPM4_DAT |= (0xf<<0);
	beep_base=(unsigned int *)ioremap(0x114000A0,0x18);
	GPD0_CON &= ~(0xf<<0);
	GPD0_CON |= (0x1<<0);
	GPD0_DAT &= ~(0x1<<0);
	key_base=(unsigned int *)ioremap(0x11000C60,0x18);
	GPX3_CON &= ~(0xffff<<8);
	GPX3_CON |= (0x1111<<8);	//配置为输入模式；
	GPX3_PUD |= (0xff<<4);		//上拉输入；
	
	misc_register(&misc);		//杂项设备注册led灯、蜂鸣器、按键；
	return 0;
}
static void __exit bye_dri(void)
{
	misc_deregister(&misc);	
	iounmap(beep_base);
	iounmap(led_base);
	iounmap(key_base);
	printk("bye,bye!\n");
}

module_init(hello_dri);
module_exit(bye_dri);
MODULE_LICENSE("GPL");


