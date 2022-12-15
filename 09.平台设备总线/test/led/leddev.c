#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <linux/uaccess.h>

static struct resource	led_source[]=
{
	{
		.start = 0x110002e0,       //��Դ��ʼ  GPM4CON��GPM4DAT
		.end   = 0x110002e0 + 8,    //��Դ��ֹ��ַ
		.flags = IORESOURCE_MEM,    //��Դ����  �������ڴ���Դ
	},
	{
		.start = 0,    //  ����IO�Ķ���
		.end   = 4,
		.flags = IORESOURCE_MEM,
	},
};

static void	led__release(struct device *dev)
{

}

struct platform_device led_dev=
{
	.name = "led_drv",
	.id = -1,
	.num_resources = ARRAY_SIZE(led_source),
	.resource = led_source,
	.dev = 
	{
		.release = led__release,
	},
};

static int __init led_dev_hello(void)
{
	platform_device_register(&led_dev);
	printk("led_dev is OK!\n");
	return 0;
}

static void __exit led_dev_bye(void)
{
	printk("led_dev is Bye!\n");
}

module_init(led_dev_hello);
module_exit(led_dev_bye);
MODULE_LICENSE("GPL");



