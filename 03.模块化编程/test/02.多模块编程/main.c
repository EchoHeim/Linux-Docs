#include <linux/kernel.h>
#include <linux/module.h>

extern void display_1(void);
extern void display_2(void);

static int __init hello(void)
{
	printk("hello!\n");
	display_1();
	return 0;
}

static void __exit bye(void)
{
	printk("thinks,bye!\n");
	display_2();
}

module_init(hello);
module_exit(bye);
MODULE_LICENSE("GPL");


