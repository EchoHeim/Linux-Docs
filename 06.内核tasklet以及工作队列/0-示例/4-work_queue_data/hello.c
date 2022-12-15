#include <linux/module.h>
#include <linux/init.h>
#include <linux/workqueue.h>

typedef struct data
{	
	struct work_struct work;  
	int x;
	int y;	
	int z;
} my_data;

my_data my_work;

static void work_handler(struct work_struct *data)
{
	my_data *p;
	
	printk(KERN_EMERG "work handler function is call!!!\n");

	p = (my_data *)data;
	
	printk(KERN_EMERG "data:%p\n",data);
	printk(KERN_EMERG "p:%p\n", p);
	printk(KERN_EMERG "x:%d,\n", p->x);
	printk(KERN_EMERG "y:%d,\n", p->y);   	
	printk(KERN_EMERG "z:%d,\n", p->z);  
}

static int __init test_init(void)
{
	my_work.x = 123;
	my_work.y = 456;
	my_work.z = 789;

	printk(KERN_EMERG "my_work:%p\n", &my_work);
	printk(KERN_EMERG "my_work.work:%p\n", &my_work.work);
	
	/* 把work放置内核工作队列中*/
	INIT_WORK(&my_work.work, work_handler);

	/* 调用工作 */
	schedule_work(&my_work.work);

	return 0;
}
static void __exit test_exit(void)
{
	printk("%s is call\r\n", __FUNCTION__);
}

MODULE_LICENSE("GPL");
module_init(test_init);
module_exit(test_exit);
