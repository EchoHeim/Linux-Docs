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
static struct resource	key_resource[]=
{
	{
		.start = 0x11000C60,       //资源起始
		.end   = 0x11000C60 + 12,    //资源终止
		.flags = IORESOURCE_MEM,    //资源类型  这里是内存资源
	},
};

/* 5、编写release函数 释放资源 一定要有 */
static void	key_release(struct device *dev)
{

}

/* 3、定义平台设备platform_device结构体 */
static struct platform_device key_dev = 
{
	.name = "key_drv",  //平台设备的名字要与驱动端一致
	.id = -1,
	.num_resources = ARRAY_SIZE(key_resource), //计算资源个数
	.resource = key_resource,                   //资源名称                 
	.dev =
	{
		.release = key_release,
	},
};

static __init int keydev_init(void)
{
	platform_device_register(&key_dev);
	printk("hello keydev!\n");
	return 0;
}
static __exit void keydev_exit(void)
{   
	platform_device_unregister(&key_dev);
	printk("keydev, bye!\n");
}

module_init(keydev_init);
module_exit(keydev_exit);
MODULE_LICENSE("GPL");




