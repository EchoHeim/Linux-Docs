#include <linux/kernel.h>
#include <linux/module.h>

extern void hello(void);
extern void bye(void);

static int __init fun1(void)
{
	hello();
	printk("hello!\n");
	return 0;
}

static void __exit fun2(void)
{
	bye();
	printk("bye!\n");
}

module_init(fun1);
module_exit(fun2);
MODULE_LICENSE("GPL");
