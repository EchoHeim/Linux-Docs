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
#include <asm/io.h>

static struct cdev *mycdev=NULL;
static dev_t devnum;
static unsigned long *gpm4con=NULL;
static unsigned long *gpm4dat=NULL;
static int pin,tmp;
static struct class *led_class;

/* д�������� */
static ssize_t led_write(struct file *filp, const char __user *buf, size_t count,loff_t *ops)
{
	unsigned char val;
	unsigned long cfu;
	int i;
	cfu = copy_from_user(&val,buf,1);
	if(val)
	{
		for(i=pin;i<tmp;i++)
		{	
			*gpm4dat |=(1<<i);
		}
	}
	else
		for(i=pin;i<tmp;i++)
		{	
			*gpm4dat &= ~(1<<i);
		}
	return 0;
}

/* ����file_operations������ */
static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.write = led_write,
};

static int led_probe(struct platform_device *dev)
{
	static struct resource *myres = NULL;
	int iosize;
	int i;

	/* cdev�豸ע�� */
	alloc_chrdev_region(&devnum,0,1,"led");
	mycdev = cdev_alloc();
	if(mycdev == NULL)
		printk("alloc error!!\n");
	cdev_init(mycdev,&fops);
	cdev_add(mycdev,devnum,1);

	/* �Զ������豸�ڵ� */
	led_class = class_create(THIS_MODULE,"led");
	device_create(led_class,NULL,devnum,NULL,"led");
	
	/* ��ƽ̨�豸��ȡ��Դ */
	myres = platform_get_resource(dev,IORESOURCE_MEM,0);
	iosize = myres->end - myres->start;  

	/* ������Դӳ�� */
	gpm4con = ioremap(myres->start,iosize);
	gpm4dat =  gpm4con +1;

	/* ��ȡ������Դ */
	myres = platform_get_resource(dev,IORESOURCE_MEM,1);
	pin = myres->start;
	tmp = myres->end;
	
	/* ����LED��ʼ�� */
	for(i=pin;i<tmp;i++)
	{	
		*gpm4con &= ~(0xf<<i*4);
		*gpm4con |= (1<<i*4);
		*gpm4dat |=(1<<i);
	}
	return 0;
}

/* ����ж�� */
static int led_remove(struct platform_device *dev)
{
	device_destroy(led_class, devnum);
	class_destroy(led_class);
	cdev_del(mycdev);
	unregister_chrdev_region(devnum,1);
	iounmap(gpm4con);
	printk("led_remove is ok!!!\n");
	return 0;
}

/* ����ƽ̨�豸platform_driver�ṹ�� */
static struct platform_driver led_drv = 
{
	.probe  = led_probe,    //���豸�˺�����������ƥ����ִ���������
	.remove = led_remove,  
	.driver =
	{
		.name = "myled",    //���豸������Ҫ��ͬ����������ƥ��
	},
};

/* 2����д������ڳ��ں��� */
static __init int leddrv_init(void)
{
    /* ƽ̨�豸ע�� */
	platform_driver_register(&led_drv);	
	printk("leddrv_init...!!\n");
	return 0;
}
static __exit void leddrv_exit(void)
{
	platform_driver_unregister(&led_drv);
}


/* 1��ָ��������ڳ��ں��� */
module_init(leddrv_init);
module_exit(leddrv_exit);
MODULE_LICENSE("GPL");

