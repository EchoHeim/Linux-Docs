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
static struct resource	ledresource[]=
{
	[0] = 
	{
		.start = 0x110002e0,       //��Դ��ʼ  GPM4CON��GPM4DAT
		.end   = 0x110002e0 + 8,    //��Դ��ֹ
		.flags = IORESOURCE_MEM,    //��Դ����  �������ڴ���Դ
	},
	[1] = 
	{
		.start = 0,    //  ����IO�Ķ���
		.end   = 4,
		.flags = IORESOURCE_MEM,
	},
};

/* 5����дrelease���� �ͷ���Դ һ��Ҫ�� */
static void	led_release(struct device *dev)
{

}

/* 3������ƽ̨�豸platform_device�ṹ�� */
static struct platform_device led_dev = 
{
	.name = "myled",  //ƽ̨�豸������Ҫ��������һ��
	.id = -1,
	.num_resources = ARRAY_SIZE(ledresource), //������Դ����
	.resource = ledresource,                   //��Դ����                 
	.dev =
	{
		.release = led_release,
	},
};

/* 2����д��ڳ��ں��� */
static __init int leddev_init(void)
{
    /* 6��ƽ̨�豸ע�� */
	platform_device_register(&led_dev);
	printk("leddev_init...!!\n");
	return 0;
}
static __exit void leddev_exit(void)
{   
    /* 7������ж�� */
	platform_device_unregister(&led_dev);
}

/* 1��ָ��������ڳ��� */
module_init(leddev_init);
module_exit(leddev_exit);
MODULE_LICENSE("GPL");

