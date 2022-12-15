#include <linux/module.h>
#include <linux/init.h>
#include <linux/workqueue.h>

static struct work_struct work;

static void work_handler(struct work_struct *data)
{
	 
    printk(KERN_EMERG "data:%p\n", data);
    
    printk(KERN_EMERG "work handler function is call!!!\n");    
}
static int __init test_init(void)
{
   
    printk(KERN_EMERG "&work:%p,\n", &work);

    /* ��work�����ں˹���������*/
    INIT_WORK(&work, work_handler);

    /* ���ù��� */
    schedule_work(&work);

    return 0;
}


static void __exit test_exit(void)
{   
    printk("%s is call\r\n", __FUNCTION__);
}

module_init(test_init);
module_exit(test_exit);



MODULE_LICENSE("GPL");


