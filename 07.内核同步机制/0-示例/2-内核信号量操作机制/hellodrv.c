#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/list.h>
#include <linux/spinlock.h>
DEFINE_SEMAPHORE(sem);
static int hello_open(struct inode *num, struct file *file)
{
	down(&sem);
	printk("hello_open is call!!!\n");	
	return 0;
}
static int hello_close(struct inode *num, struct file *file)
{
	printk("hello_close is call!!!\n");
	up(&sem);
	return 0;
}
static struct file_operations hello_fops = 
{
	.owner = THIS_MODULE,
	.open  = hello_open,
	.release = hello_close,
};
static struct miscdevice misc = 
{
	.name = "hello",
	.minor = 255,
	.fops = &hello_fops,
};


static int __init hello_init(void)
{
	int ret = misc_register(&misc);
	if(ret<0)
	{
		printk("register fail!!!\n");
		return -1;
	}
	printk("hello register success!!!\n");
	return 0;
}
static void __exit hello_exit(void)
{
	misc_deregister(&misc);
	printk("bye bye!!!");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
