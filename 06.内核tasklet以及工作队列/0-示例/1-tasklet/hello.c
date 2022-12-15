#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

void my_tasklet_function(unsigned long data);   //����������

/*��̬���岢��ʼ��һ��tasklet �ں�΢�߳�*/
DECLARE_TASKLET(my_tasklet,my_tasklet_function,1);

/*tasklet������*/
void my_tasklet_function(unsigned long data)
{
	printk("my_tasklet_function is call\r\n");
	printk("data = %lu\n",data);
 
}
static int __init test_init(void)        //ģ���ʼ������
{
	printk("tasklet is call\r\n");	
	/*����tasklet*/
	my_tasklet.data=100;
	tasklet_schedule(&my_tasklet);	
		
	return 0;
}
static void __exit test_exit(void)        //ģ��ж�غ���
{ 
	printk("tasklet is end\r\n");
	tasklet_kill(&my_tasklet);	
}
module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
