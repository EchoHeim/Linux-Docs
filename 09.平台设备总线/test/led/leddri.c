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

static struct cdev *led_cdev=NULL;
static unsigned int *GPM4_CON=NULL;
static unsigned int *GPM4_DAT=NULL;
static struct class *led_class;
static char *leds_name[]={"led1","led2","led3","led4"};

static dev_t devnum;
//static unsigned int led_major = 0;		//�������豸�ţ�
static unsigned int led_minor = 0;		//������豸�ţ�

static int led_open(struct inode *node, struct file *file)
{
	led_minor=iminor(node);
	return 0;
}

static int led_close(struct inode *node, struct file *file)
{
	led_minor=iminor(node);
	return 0;
}

/* д�������� */
static ssize_t led_write(struct file *filp, const char __user *buf, size_t count,loff_t *ops)
{
	unsigned char led_num;
	unsigned long return_val=0;
	return_val = copy_from_user(&led_num,buf,1);
	if(led_num)
		*GPM4_DAT &= ~(1<<led_minor);
	else
		*GPM4_DAT |= (1<<led_minor);
	return 0;
}

/* ����file_operations������ */
static struct file_operations led_fops =
{
	.owner = THIS_MODULE,
	.open = led_open,
	.release = led_close,
	.write = led_write,
};

static int led_probe(struct platform_device *dev)
{
	static struct resource *led_tep = NULL;
	int i,iosize;
	
	/* cdev�豸ע�� */
	alloc_chrdev_region(&devnum,0,4,"led");
	led_cdev = cdev_alloc();
	led_cdev->owner = THIS_MODULE;
	led_cdev->count = 4;
	if(led_cdev == NULL)
		printk("alloc error!!\n");
	cdev_init(led_cdev,&led_fops);
	cdev_add(led_cdev,devnum,4);

	/* �Զ������豸�ڵ� */
	led_class = class_create(THIS_MODULE,"led");
	for(i=0;i<4;i++)
		device_create(led_class,NULL,devnum+i,NULL,leds_name[i]);
	
	/* ��ƽ̨�豸��ȡ��Դ */
	led_tep = platform_get_resource(dev,IORESOURCE_MEM,0);
	iosize = led_tep->end - led_tep->start;  

	/* ������Դӳ�� */
	GPM4_CON = ioremap(led_tep->start,iosize);
	GPM4_DAT =  GPM4_CON +1;

	/*led��ʼ��*/
	*GPM4_CON &= ~(0xffff<<0);
	*GPM4_CON |= (0x1111<<0);
	*GPM4_DAT |= (0xf<<0);
	
	return 0;
}

/* ����ж�� */
static int led_remove(struct platform_device *dev)
{
	int i=0;
	for(i=0;i<4;i++)
		device_destroy(led_class, devnum+i);
	class_destroy(led_class);
	cdev_del(led_cdev);
	unregister_chrdev_region(devnum,1);
	iounmap(GPM4_CON);
	printk("led_remove is ok!!!\n");
	return 0;
}

static struct platform_driver led_driv =
{
	.probe = led_probe,
	.remove = led_remove,
	.driver = 
	{
		.name = "led_drv",
	},
};

static int __init led_dri_hello(void)
{
	platform_driver_register(&led_driv);
	printk("led_dri is OK!\n");
	return 0;
}

static void __exit led_dri_bye(void)
{
	platform_driver_unregister(&led_driv);
	printk("led_dri is Bye!\n");
}

module_init(led_dri_hello);
module_exit(led_dri_bye);
MODULE_LICENSE("GPL");


