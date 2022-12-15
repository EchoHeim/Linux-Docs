#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/timer.h>
struct timer_list my_timer;//1.定义定时器结构体timer_list
void timer_func(unsigned long data)    //2.定义定时器处理函数
{
	printk("time out!%lu\n",data); //打印当前进程
}
static int __init time_init(void)
{
	init_timer(&my_timer); //初始化timer_list结构
	 /*设定定时器处理函数触发时间为5秒 */ 
	my_timer.expires  = jiffies + 5*HZ;     //设定定时器处理函数触发时间为5秒
	my_timer.function = timer_func;         //给结构体指定定时器处理函数
	my_timer.data     = (unsigned long)99;  //设定定时器处理函数的传参
	add_timer(&my_timer);                    //激活定时器
	return 0;
}
static void __exit time_exit(void)
{
	printk("bye bye!!!\n");
}
module_init(time_init);
module_exit(time_exit);
MODULE_LICENSE("GPL");
