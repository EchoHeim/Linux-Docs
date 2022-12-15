#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <linux/platform_device.h>

static int major=0;
static struct class *key_class=NULL;
static DECLARE_WAIT_QUEUE_HEAD(key_wait);		//创建阻塞等待队列头；
static unsigned int key_ev;		//定义标志位；
struct KEY_tag
{
	unsigned int gpio;
	char name[20];
};
struct KEY_tag key[4]={{EXYNOS4_GPX3(2),"key1"},
						{EXYNOS4_GPX3(3),"key2"},
						{EXYNOS4_GPX3(4),"key3"},
						{EXYNOS4_GPX3(5),"key4"}};

static int key_dev=0;
static unsigned int key_val=0;	//定义返回键值；
irqreturn_t key_handler(int irq,void *dev)
{
	switch(irq)
	{
		case 442:key_val=1;break;		//中断号内核已定义.可打印显示；
		case 443:key_val=2;break;
		case 444:key_val=3;break;
		case 445:key_val=4;break;
	}
	key_ev=1;
	wake_up_interruptible(&key_wait);		//进入中断后，唤醒读操作的阻塞等待；
	return 0;
}

int key_open(struct inode *node, struct file *fp)
{
	unsigned int return_val,irq = 0,i;
	for(i=0;i<4;i++)
	{
		irq = gpio_to_irq(key[i].gpio);
		return_val = request_irq(irq,key_handler,IRQF_TRIGGER_RISING,key[i].name,(void *)&key_dev);
	}
	return 0;
}

int key_close(struct inode *node, struct file *fp)
{
	unsigned int irq = 0,i;
	for(i=0;i<4;i++)
	{
		irq = gpio_to_irq(key[i].gpio);
		free_irq(irq,(void *)&key_dev);
	}
	return 0;
}

ssize_t key_read(struct file *fp, char __user *name, size_t size, loff_t * p)
{
	unsigned long return_val;
	wait_event_interruptible(key_wait,key_ev);		//读操作阻塞，等待kev_ev变高；
	return_val=copy_to_user(name,&key_val,1);
	key_ev=0;			//读取后置0；
	return 0;
}

static struct file_operations key_fops=
{
	.owner=THIS_MODULE,
	.open = key_open,
	.release = key_close,
	.read = key_read,
};
static int __init hello_key(void)
{
	major=register_chrdev(0,"HSL",&key_fops);
	key_class=class_create(THIS_MODULE,"hsl_key");
	device_create(key_class,NULL,MKDEV(major,0),NULL,"hello_key");
	return 0;
}

static void __exit bye_key(void)
{
	device_destroy(key_class,MKDEV(major,0));
	class_destroy(key_class);
	unregister_chrdev(major,"HSL");
	printk("bye,bye!\n");
}

module_init(hello_key);
module_exit(bye_key);
MODULE_LICENSE("GPL");

