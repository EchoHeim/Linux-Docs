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

static unsigned int *beep_base=NULL;

#define GPD0_CON (*(volatile unsigned int*)(beep_base+0))
#define GPD0_DAT (*(volatile unsigned int*)(beep_base+1))

static int beep_open(struct inode *num, struct file *file)
{
	return 0;
}

static int beep_close(struct inode *num, struct file *file)
{
	return 0;
}
ssize_t beep_write(struct file *fd, const char __user *name, size_t size, loff_t *lofset)
{
	unsigned char beep_val=0;
	unsigned long return_val=0;
	return_val = copy_from_user(&beep_val,name,1);
	if(beep_val)
		GPD0_DAT |= (0x1<<0);
	else
		GPD0_DAT &= ~(0x1<<0);
	return 0;
}

static struct file_operations beep_fop=
{
	.owner = THIS_MODULE,
	.open = beep_open,
	.release = beep_close,
	.write = beep_write,
};

static struct miscdevice misc=
{
	.name="hello_beep",
	.minor = 255,
	.fops = &beep_fop,
};

static int __init hello_beep(void)
{
	beep_base=(unsigned int *)ioremap(0x114000A0,0x18);
	GPD0_CON &= ~(0xf<<0);
	GPD0_CON |= (0x1<<0);
	GPD0_DAT &= ~(0x1<<0);
	
	misc_register(&misc);		//ÔÓÏîÉè±¸×¢²á·äÃùÆ÷£»
	return 0;
}
static void __exit bye_beep(void)
{
	misc_deregister(&misc);	
	iounmap(beep_base);
	printk("bye,bye!\n");
}

module_init(hello_beep);
module_exit(bye_beep);
MODULE_LICENSE("GPL");



