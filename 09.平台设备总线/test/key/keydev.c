#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <linux/uaccess.h>

/* 4��������Դ */
static struct resource	key_resource[]=
{
	{
		.start = 0x11000C60,       //��Դ��ʼ
		.end   = 0x11000C60 + 12,    //��Դ��ֹ
		.flags = IORESOURCE_MEM,    //��Դ����  �������ڴ���Դ
	},
};

/* 5����дrelease���� �ͷ���Դ һ��Ҫ�� */
static void	key_release(struct device *dev)
{

}

/* 3������ƽ̨�豸platform_device�ṹ�� */
static struct platform_device key_dev = 
{
	.name = "key_drv",  //ƽ̨�豸������Ҫ��������һ��
	.id = -1,
	.num_resources = ARRAY_SIZE(key_resource), //������Դ����
	.resource = key_resource,                   //��Դ����                 
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




