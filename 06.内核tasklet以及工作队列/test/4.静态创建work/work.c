#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

void fun(struct work_struct *data)
{
	printk("hello world!\n");
}

DECLARE_WORK(my_work,fun);

static int __init hello_work(void)
{
	schedule_work(&my_work);
	return 0;
}

static void __exit bye_work(void)
{
	printk("bye,bye!\n");
}

module_init(hello_work);
module_exit(bye_work);
MODULE_LICENSE("GPL");

