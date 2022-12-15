#include <linux/module.h>
#include <linux/kernel.h> 
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/irqreturn.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/sched.h> 
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm-generic/poll.h>
#include <linux/poll.h>
struct timer_list my_timer;
static DECLARE_WAIT_QUEUE_HEAD(key_wait);
static int condition = 0;
static struct class *key_class = NULL;
static dev_t key_major;
static dev_t key_num;
static unsigned char key_vale=0;
void time_funtion(unsigned long data)
{
	condition = 1; 
	wake_up_interruptible(&key_wait);
}
static irqreturn_t key_irq(int irq, void *data)
{ 
	switch(irq)
	{
		case 442:key_vale=1;break;
		case 443:key_vale=2;break;
		case 444:key_vale=3;break;
		case 445:key_vale=4;break;
	}
	init_timer(&my_timer);
	my_timer.expires = jiffies + HZ/100;
	my_timer.function = time_funtion;
	my_timer.data = 99;
	add_timer(&my_timer); 
	
	return IRQ_RETVAL(IRQ_HANDLED);
}
static int key_read(struct file *filp,char __user *buff,size_t count,loff_t *offset)
{
	unsigned long r_ret;
	wait_event_interruptible(key_wait,condition);
  	condition = 0;
	r_ret=copy_to_user(buff,&key_vale,1);
	key_vale=0;
	return 0;
}
static int i;
static int key_open(struct inode *inode, struct file *filp)
{  
	
	int irq;	
	int irq_rec;
	irq = gpio_to_irq(EXYNOS4_GPX3(2));
	irq_rec = request_irq(irq,key_irq,IRQ_TYPE_EDGE_FALLING,"key0",(void *)&i);
	irq = gpio_to_irq(EXYNOS4_GPX3(3));
	irq_rec = request_irq(irq,key_irq,IRQ_TYPE_EDGE_FALLING,"key1",(void *)&i);
	irq = gpio_to_irq(EXYNOS4_GPX3(4));
	irq_rec = request_irq(irq,key_irq,IRQ_TYPE_EDGE_FALLING,"key2",(void *)&i);
	irq = gpio_to_irq(EXYNOS4_GPX3(5));
	irq_rec = request_irq(irq,key_irq,IRQ_TYPE_EDGE_FALLING,"key3",(void *)&i);
  	return 0;
}
static int key_close(struct inode *inode, struct file *filp)
{
	int irq;
	irq = gpio_to_irq(EXYNOS4_GPX3(2));
	free_irq(irq,(void *)&i);
	irq = gpio_to_irq(EXYNOS4_GPX3(3));
	free_irq(irq,(void *)&i);
	irq = gpio_to_irq(EXYNOS4_GPX3(4));
	free_irq(irq,(void *)&i);
	irq = gpio_to_irq(EXYNOS4_GPX3(5));
	free_irq(irq,(void *)&i);
	return 0;
}
static unsigned int key_poll(struct file *filp, struct poll_table_struct *wait)
{
	int res = 0;
	poll_wait(filp,&key_wait,wait);
	if(condition)
		res = POLLIN;
	return res;
}

static struct file_operations key_fops =
{
  .owner   = THIS_MODULE,
  .open    = key_open,
  .release = key_close,
  .read = key_read,
  .poll = key_poll,
};

static int mykey_init(void)
{

  key_major = register_chrdev(0,"keydrv",&key_fops);
  key_num   = MKDEV(key_major,0);	
  key_class = class_create(THIS_MODULE,"key_class");
  device_create(key_class,NULL,key_num,NULL,"key");
  printk("this is keydrv init......\n");
  return 0;
}

static void mykey_exit(void)
{

  device_destroy(key_class,key_num);
  class_destroy(key_class);
  unregister_chrdev(key_major,"keydrv");
  printk("this is keydrv exit......\n");
}


module_init(mykey_init);
module_exit(mykey_exit);
MODULE_LICENSE("GPL");


