#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>

static struct timer_list timer1;
static struct timer_list timer2;
void fun_timer1(unsigned long data)
{
	printk("time1 out!  data = %ld\n",data);
//	mod_timer(&timer,jiffies+HZ/2);		//加上此条语句可循环执行；
}
void fun_timer2(unsigned long data)
{
	printk("time2 out!  data = %ld\n",data);
//	mod_timer(&timer,jiffies+HZ/2);		//加上此条语句可循环执行；
}

static int __init hello_timer(void)
{
	printk("register success!\n");
	timer1.data = 100;
	timer1.expires = jiffies+2*HZ;		//2秒后进入超时函数(fun_timer)；
	timer1.function = fun_timer1;

	timer2.data = 200;
	timer2.expires = jiffies+4*HZ;		//4秒后进入超时函数(fun_timer)；
	timer2.function = fun_timer2;

	init_timer(&timer1);
	init_timer(&timer2);

	add_timer(&timer1);
	add_timer(&timer2);
	return 0;
}

static void __exit bye_timer(void)
{
	del_timer(&timer1);
	del_timer(&timer2);
	printk("bye,bye!\n");
}

module_init(hello_timer);
module_exit(bye_timer);
MODULE_LICENSE("GPL");

