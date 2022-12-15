#include <linux/kernel.h>
#include <linux/module.h>
void hello_text0(void)
{
	printk("hello_text0\n");
}
void hello_text1(void)
{
	printk("hello_text1\n");
}
static __init int hello_drv0_init(void)
{
	printk("this is hellodrv0_init\n");
	return 0;
}
static __exit void hello_drv0_exit(void)
{
	printk("this is hellodrv0_exit\n");
}
module_init(hello_drv0_init);
module_exit(hello_drv0_exit);
EXPORT_SYMBOL(hello_text0);
EXPORT_SYMBOL(hello_text1);
MODULE_LICENSE("GPL");
