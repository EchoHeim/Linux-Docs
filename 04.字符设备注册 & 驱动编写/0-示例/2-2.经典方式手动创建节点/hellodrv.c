#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
static int hello_open(struct inode *num, struct file *file)
{
	printk("hello_open is call!!!\n");
	return 0;
}
static int hello_close(struct inode *num, struct file *file)
{
	printk("hello_close is call!!!\n");
	return 0;
}
static int major;
static struct file_operations hello_fops = 
{
	.owner = THIS_MODULE,
	.open = hello_open,
	.release = hello_close,
};
static int __init hello_init(void)
{
	major = register_chrdev(0,"my_hello",&hello_fops);
	printk("major = %d\n",major);
	return 0;
}
static void __exit hello_exit(void)
{
	unregister_chrdev(major,"my_hello");
	printk("bye bye!!!");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
