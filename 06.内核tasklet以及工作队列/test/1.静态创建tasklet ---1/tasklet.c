#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

void fun(unsigned long data)
{
	printk("hello world!    data = %lu\n",data);
}

DECLARE_TASKLET(my_tasklet,fun,100);

static int __init hello_tasklet(void)
{
	tasklet_schedule(&my_tasklet);
	return 0;
}

static void __exit bye_tasklet(void)
{
	printk("bye,bye!\n");
}

module_init(hello_tasklet);
module_exit(bye_tasklet);
MODULE_LICENSE("GPL");

