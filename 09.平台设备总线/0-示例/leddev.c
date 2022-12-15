#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <linux/uaccess.h>

/* 4、定义资源 */
static struct resource	ledresource[]=
{
	[0] = 
	{
		.start = 0x110002e0,       //资源起始  GPM4CON、GPM4DAT
		.end   = 0x110002e0 + 8,    //资源终止
		.flags = IORESOURCE_MEM,    //资源类型  这里是内存资源
	},
	[1] = 
	{
		.start = 0,    //  具体IO的定义
		.end   = 4,
		.flags = IORESOURCE_MEM,
	},
};

/* 5、编写release函数 释放资源 一定要有 */
static void	led_release(struct device *dev)
{

}

/* 3、定义平台设备platform_device结构体 */
static struct platform_device led_dev = 
{
	.name = "myled",  //平台设备的名字要与驱动端一致
	.id = -1,
	.num_resources = ARRAY_SIZE(ledresource), //计算资源个数
	.resource = ledresource,                   //资源名称                 
	.dev =
	{
		.release = led_release,
	},
};

/* 2、编写入口出口函数 */
static __init int leddev_init(void)
{
    /* 6、平台设备注册 */
	platform_device_register(&led_dev);
	printk("leddev_init...!!\n");
	return 0;
}
static __exit void leddev_exit(void)
{   
    /* 7、驱动卸载 */
	platform_device_unregister(&led_dev);
}

/* 1、指定驱动入口出口 */
module_init(leddev_init);
module_exit(leddev_exit);
MODULE_LICENSE("GPL");

