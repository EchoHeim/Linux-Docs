#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/mm.h>
#include <asm/io.h>
static unsigned int *base=NULL;
#define GPX3CON (*(volatile unsigned int *)(base+0))
#define GPX3DAT (*(volatile unsigned int *)(base+1))
#define GPX3PUD (*(volatile unsigned int *)(base+2))
int mykeyopen(struct inode *node, struct file *fp)
{
	return 0;
}
int mykeyclose(struct inode *node, struct file *fp)
{
	return 0;
}
ssize_t mykeyread(struct file *node, char __user *buff, size_t size, loff_t * offset)
{
	if(!(GPX3DAT & (1<<2)))
	{
		while(!(GPX3DAT & (1<<2)));
		printk("key0 is press!!!\n");
	}
	if(!(GPX3DAT & (1<<3)))
	{
		while(!(GPX3DAT & (1<<3))); //while(0);
		printk("key1 is press!!!\n");
	}
	if(!(GPX3DAT & (1<<4)))
	{
		while(!(GPX3DAT & (1<<4)));
		printk("key2 is press!!!\n");
	}
	if(!(GPX3DAT & (1<<5)))
	{
		while(!(GPX3DAT & (1<<5)));
		printk("key3 is press!!!\n");
	}
	return 0;
}

static struct file_operations key_fops =
{
	.owner=THIS_MODULE,
	.open = mykeyopen,
	.release=mykeyclose,
	.read=mykeyread,
};
static int major=0;
static struct class *keyclass=NULL;
static int __init mykey_init(void)
{
	base = (unsigned int *)ioremap(0x11000C60,0x16);
	GPX3CON &= ~(0xffff<<8);
	GPX3PUD &= ~(0xff<<4);
	GPX3PUD |= (0xff<<4);
	major = register_chrdev(0,"hello",&key_fops);
	keyclass=class_create(THIS_MODULE,"xyd");
	device_create(keyclass,NULL,MKDEV(major,0),NULL,"mykey");
	return 0;
}
static void __exit mykey_exit(void)
{
	device_destroy(keyclass,MKDEV(major,0));
	class_destroy(keyclass);
	unregister_chrdev(major,"hello");
	iounmap(base);
}
module_init(mykey_init);
module_exit(mykey_exit);
MODULE_LICENSE("GPL");

