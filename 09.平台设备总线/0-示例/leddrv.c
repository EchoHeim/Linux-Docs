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

/* 写操作函数 */
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

/* 定义file_operations操作集 */
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

	/* cdev设备注册 */
	alloc_chrdev_region(&devnum,0,1,"led");
	mycdev = cdev_alloc();
	if(mycdev == NULL)
		printk("alloc error!!\n");
	cdev_init(mycdev,&fops);
	cdev_add(mycdev,devnum,1);

	/* 自动创建设备节点 */
	led_class = class_create(THIS_MODULE,"led");
	device_create(led_class,NULL,devnum,NULL,"led");
	
	/* 从平台设备获取资源 */
	myres = platform_get_resource(dev,IORESOURCE_MEM,0);
	iosize = myres->end - myres->start;  

	/* 进行资源映射 */
	gpm4con = ioremap(myres->start,iosize);
	gpm4dat =  gpm4con +1;

	/* 获取引脚资源 */
	myres = platform_get_resource(dev,IORESOURCE_MEM,1);
	pin = myres->start;
	tmp = myres->end;
	
	/* 进行LED初始化 */
	for(i=pin;i<tmp;i++)
	{	
		*gpm4con &= ~(0xf<<i*4);
		*gpm4con |= (1<<i*4);
		*gpm4dat |=(1<<i);
	}
	return 0;
}

/* 驱动卸载 */
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

/* 定义平台设备platform_driver结构体 */
static struct platform_driver led_drv = 
{
	.probe  = led_probe,    //当设备端和驱动端名称匹配后会执行这个函数
	.remove = led_remove,  
	.driver =
	{
		.name = "myled",    //和设备端名称要相同，根据名字匹配
	},
};

/* 2、编写驱动入口出口函数 */
static __init int leddrv_init(void)
{
    /* 平台设备注册 */
	platform_driver_register(&led_drv);	
	printk("leddrv_init...!!\n");
	return 0;
}
static __exit void leddrv_exit(void)
{
	platform_driver_unregister(&led_drv);
}


/* 1、指定驱动入口出口函数 */
module_init(leddrv_init);
module_exit(leddrv_exit);
MODULE_LICENSE("GPL");

