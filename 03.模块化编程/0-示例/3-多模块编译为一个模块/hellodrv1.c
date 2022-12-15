#include <linux/kernel.h>
#include <linux/module.h>
extern void hello_text0(void);
extern void hello_text1(void);
static int __init hello_drv1_init(void)
{
	hello_text0();
	printk(KERN_INFO"this is hellodrv1_init\n");
	return 0;
}
static void __exit hello_drv1_exit(void)
{
	hello_text1();
	printk(KERN_INFO"this is hellodrv1_exit\n");
}
module_init(hello_drv1_init);
module_exit(hello_drv1_exit);
MODULE_LICENSE("GPL");
