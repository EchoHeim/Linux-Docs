#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

struct work_tag
{
	int a;
	int b;
	struct work_struct work;
};
struct work_tag my_work;

void fun(struct work_struct *data)
{
	struct work_tag *p = container_of(data,struct work_tag,work);
	printk("hello world!\n");
	printk("a = %d, b = %d\n",p->a,p->b);
}


static int __init hello_work(void)
{
	my_work.a = 100;
	my_work.b = 200;
	INIT_WORK(&my_work.work, fun);
	schedule_work(&my_work.work);
	return 0;
}

static void __exit bye_work(void)
{
	printk("bye,bye!\n");
}

module_init(hello_work);
module_exit(bye_work);
MODULE_LICENSE("GPL");

