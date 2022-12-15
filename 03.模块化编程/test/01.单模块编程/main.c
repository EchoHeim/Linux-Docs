#include <linux/kernel.h>
#include <linux/module.h>
static int __init hello(void)
{
	printk("hello world!\n");
	return 0;
}
static void __exit bye(void)
{
	printk("thinks, bye!\n");
}
module_init(hello);
module_exit(bye);
MODULE_LICENSE("GPL");
