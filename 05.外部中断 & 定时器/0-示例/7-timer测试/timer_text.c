#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <mach/hardware.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <mach/map.h>
#include <mach/gpio.h>
#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>
static struct timer_list timer;
static DECLARE_WAIT_QUEUE_HEAD(key_wait);
int condition=0;
static struct tag
{
	unsigned int gpio;
	unsigned int irq;
	char name[20];
};
static struct tag key[]={{EXYNOS4_GPX3(2),0,"key1"},{EXYNOS4_GPX3(3),0,"key2"},{EXYNOS4_GPX3(4),0,"key3"},{EXYNOS4_GPX3(5),0,"key4"}};
unsigned char keyvalue=0;
irqreturn_t fun(int irq, void *data)
{
	switch(irq)
	{
		case 442:keyvalue=1;break;
		case 443:keyvalue=2;break;
		case 444:keyvalue=3;break;
		case 445:keyvalue=4;break;
		default:break;
	}
	mod_timer(&timer,jiffies+HZ/25);
	return 0;
}
void timer_fun(unsigned long data)
{
	condition=1;
	wake_up_interruptible(&key_wait);
}
int myopen(struct inode *node, struct file *fp)
{
	unsigned int ret=0;
	int i;
	for(i=0;i<4;i++)
	{
		key[i].irq=gpio_to_irq(key[i].gpio);
		ret = request_irq(key[i].irq,fun,IRQF_TRIGGER_FALLING,key[i].name,NULL);
	}
	return 0;
}
ssize_t myread(struct file *fp, char __user *buff, size_t size, loff_t *offset)
{
	unsigned long r_ret;
	wait_event_interruptible(key_wait,condition);
  	condition = 0;
	r_ret=copy_to_user(buff,&keyvalue,1);
	return 0;
}

int myclose(struct inode *node, struct file *fp)
{
	int i;
	for(i=0;i<4;i++)
		free_irq(key[i].irq,NULL);
	return 0;
}
static unsigned int mypoll( struct file *file,struct poll_table_struct *wait)
{
	unsigned int mask = 0;
	poll_wait(file,&key_wait, wait);
	if(condition)
		mask |= POLLIN;
	return mask;
}
static struct file_operations myfops=
{
	.owner = THIS_MODULE,
	.open = myopen,
	.release=myclose,
	.read = myread,
	.poll = mypoll,
};
static struct miscdevice misc=
{
	.minor=255,
	.name="mykey",
	.fops=&myfops,
};
static int __init mykey_init(void)
{
	timer.data=0;
	timer.expires = jiffies+HZ/25; 
	timer.function = timer_fun;
	init_timer(&timer);
	misc_register(&misc);
	return 0;
}
static void __exit mykey_exit(void)
{
	del_timer(&timer);	
	misc_deregister(&misc);
}

module_init(mykey_init);
module_exit(mykey_exit);
MODULE_LICENSE("GPL");
