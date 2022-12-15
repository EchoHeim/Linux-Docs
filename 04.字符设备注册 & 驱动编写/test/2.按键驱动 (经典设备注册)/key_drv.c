#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/mm.h>
#include <asm/io.h>
#include <asm/uaccess.h>

static unsigned int *key_base=NULL;
#define GPX3_CON (*(volatile unsigned int *)(key_base+0))
#define GPX3_DAT (*(volatile unsigned int *)(key_base+1))
#define GPX3_PUD (*(volatile unsigned int *)(key_base+2))

static int major=0;
static struct class *key_class=NULL;
int key_open(struct inode *node, struct file *fp)
{
	return 0;
}
int key_close(struct inode *node, struct file *fp)
{
	return 0;
}

static unsigned char key_val=0;	//¶¨Òå¼üÖµ£»
ssize_t key_read(struct file *fp, char __user *name, size_t size, loff_t * p)
{
	unsigned long return_val;
	if(!(GPX3_DAT&(1<<2)))
	{
		while(!(GPX3_DAT&(1<<2)));
		key_val=1;
	}
	else if(!(GPX3_DAT&(1<<3)))
	{
		while(!(GPX3_DAT&(1<<3)));
		key_val=2;
	}
	else if(!(GPX3_DAT&(1<<4)))
	{
		while(!(GPX3_DAT&(1<<4)));
		key_val=3;
	}
	else if(!(GPX3_DAT&(1<<5)))
	{
		while(!(GPX3_DAT&(1<<5)));
		key_val=4;
	}
	if(key_val)
		return_val=copy_to_user(name,&key_val,1);
	key_val=0;
	return 0;
}

static struct file_operations key_fops=
{
	.owner=THIS_MODULE,
	.open = key_open,
	.release = key_close,
	.read = key_read,
};
static int __init hello_key(void)
{
	key_base=(unsigned int *)ioremap(0x11000C60,0x18);
	GPX3_CON &= ~(0xffff<<8);
	GPX3_PUD &= ~(0xff<<4);
	GPX3_PUD |= (0xff<<4);
	major=register_chrdev(0,"HSL",&key_fops);
	key_class=class_create(THIS_MODULE,"hsl_key");
	device_create(key_class,NULL,MKDEV(major,0),NULL,"key_drv");
	return 0;
}

static void __exit bye_key(void)
{
	device_destroy(key_class,MKDEV(major,0));
	class_destroy(key_class);
	unregister_chrdev(major,"HSL");
	iounmap(key_base);
}

module_init(hello_key);
module_exit(bye_key);
MODULE_LICENSE("GPL");






