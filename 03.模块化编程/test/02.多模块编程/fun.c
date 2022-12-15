#include <linux/kernel.h>
#include <linux/module.h>

void display_1(void)
{
	printk("hello!\n");
}

void display_2(void)
{
	printk("world!\n");
}

static int __init fun_hello(void)
{
	printk("fun_hello world!\n");
	return 0;
}

static void __exit fun_bye(void)
{
	printk("thinks,fun_bye!\n");
}

module_init(fun_hello);
module_exit(fun_bye);
EXPORT_SYMBOL(display_1);
EXPORT_SYMBOL(display_2);
MODULE_LICENSE("GPL");


