#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <asm/io.h>

static unsigned long *GPX3CON=NULL;
static unsigned long *GPX3DAT=NULL;
static unsigned long *GPX3PUD=NULL;

static int mykey_open(struct inode *inod, struct file *fil)
{
	return 0;
}

static ssize_t mykey_read(struct file *fil, char __user *buf, size_t count, loff_t *ops)
{
	unsigned long return_val;
	int key_val;
	if(!(*GPX3DAT & (1<<2)))
	{
		key_val = 1;
	}
	else if(!(*GPX3DAT & (1<<3)))
	{
		key_val = 2;
	}
	else if(!(*GPX3DAT & (1<<4)))
	{
		key_val = 3;
	}
	else if(!(*GPX3DAT & (1<<5)))
	{
		key_val = 4;
	}
	else
		key_val = 0;
	if(key_val)
		return_val=copy_to_user(buf,&key_val,1);
	key_val=0;
	return 0;
}
	
static int mykey_close(struct inode *inod, struct file *fil)
{
	return 0;
}

static struct file_operations mykey_fops =
{
	.owner   = THIS_MODULE,
	.open    = mykey_open,
	.release = mykey_close,
	.read    = mykey_read,
};

static struct miscdevice mykey_misc =
{
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "mykey",
	.fops  = &mykey_fops,
};

static int key_probe(struct platform_device *dev)
{
	static struct resource *myres = NULL;
	int iosize;
	int i;

	misc_register(&mykey_misc);
	
	/* ��ƽ̨�豸��ȡ��Դ */
	myres = platform_get_resource(dev,IORESOURCE_MEM,0);
	iosize = myres->end - myres->start;  

	/* ������Դӳ�� */
	GPX3CON = ioremap(myres->start,iosize);
	GPX3DAT =  GPX3CON +1;
	GPX3PUD =  GPX3CON +2;

	/*��ʼ��*/
	*GPX3CON &=~(0xFFFF<<8);
	*GPX3PUD &=~(0xFF<<4);
	*GPX3PUD |= 0xFF<<4;
	
	return 0;
}

/* ����ж�� */
static int key_remove(struct platform_device *dev)
{
	iounmap(GPX3CON);
	misc_deregister(&mykey_misc);
	printk("key_remove is ok!!!\n");
	return 0;
}

/* ����ƽ̨�豸platform_driver�ṹ�� */
static struct platform_driver key_drv = 
{
	.probe  = key_probe,    //���豸�˺�����������ƥ����ִ���������
	.remove = key_remove,  
	.driver =
	{
		.name = "key_drv",    //���豸������Ҫ��ͬ����������ƥ��
	},
};

static __init int keydrv_init(void)
{
    /* ƽ̨�豸ע�� */
	platform_driver_register(&key_drv);	
	printk("hello keydrv!\n");
	return 0;
}
static __exit void keydrv_exit(void)
{
	platform_driver_unregister(&key_drv);
	printk("keydrv, bye!\n");
}

module_init(keydrv_init);
module_exit(keydrv_exit);
MODULE_LICENSE("GPL");


