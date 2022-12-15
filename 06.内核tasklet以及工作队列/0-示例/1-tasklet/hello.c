#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

void my_tasklet_function(unsigned long data);   //先声明函数

/*静态定义并初始化一个tasklet 内核微线程*/
DECLARE_TASKLET(my_tasklet,my_tasklet_function,1);

/*tasklet任务函数*/
void my_tasklet_function(unsigned long data)
{
	printk("my_tasklet_function is call\r\n");
	printk("data = %lu\n",data);
 
}
static int __init test_init(void)        //模块初始化函数
{
	printk("tasklet is call\r\n");	
	/*调度tasklet*/
	my_tasklet.data=100;
	tasklet_schedule(&my_tasklet);	
		
	return 0;
}
static void __exit test_exit(void)        //模块卸载函数
{ 
	printk("tasklet is end\r\n");
	tasklet_kill(&my_tasklet);	
}
module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
