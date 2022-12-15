#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/slab.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/gpio_keys.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/spinlock.h>

/* ������������
 * �����¼� 
 * key1 : l
 * key2 : s
 * key3 : �س�
 */
typedef struct PinDesc 
{
	unsigned int irq; // �жϺ�
	char * name;      // �ж�����
	int pin;          // �ܽ�
	unsigned char val;// ��ֵ
	
}T_PinDesc,*PT_PinDesc;


static T_PinDesc keyDesc[3]=
{
	{IRQ_EINT(26),"key1",EXYNOS4_GPX3(2),KEY_L},
	{IRQ_EINT(27),"key2",EXYNOS4_GPX3(3),KEY_S},
	{IRQ_EINT(28),"key3",EXYNOS4_GPX3(4),KEY_ENTER},
};

static struct input_dev *myinput = NULL;
static struct timer_list key_timer;
static PT_PinDesc pin;

static irq_handler_t myfun(int irq,void *dev)
{
	pin = (PT_PinDesc)dev;

	mod_timer(&key_timer,jiffies + HZ/100);
	return IRQ_HANDLED;
}

static void key_function(unsigned long data)
{
	unsigned int pinval;
	PT_PinDesc pin_desc = pin;
	if(!pin_desc)
	{
		printk("the first time to enter\n");
		return ;
	}
	pinval = gpio_get_value(pin_desc->pin);
	if(pinval)
	{
		/* �ɿ� : ���һ������: 0-�ɿ�, 1-���� */
		input_event(myinput, EV_KEY, pin_desc->val, 0);
		/* ����ȷ���ϱ����¼������ղŻ���õ�handler��event */
		input_sync(myinput);

	}
	else
	{
		input_event(myinput, EV_KEY, pin_desc->val, 1);
		input_sync(myinput);
	}
}


static __init int input_key_init(void)
{
	int i;
	/* 1������input_dev�ṹ�� */
	myinput = input_allocate_device();
	if(NULL == myinput)
	{
		printk("input alloc error!!\n");
		return -1;
	}
	/* 2������ */
	myinput->name = "mykey";
	
	/* 2.1�������¼� */
	__set_bit(EV_KEY, myinput->evbit);
	/* ���ظ��¼� */
	__set_bit(EV_REP, myinput->evbit);
	/* 2.2��������һ���¼��������¼� */
	__set_bit(KEY_L, myinput->keybit);
	__set_bit(KEY_S, myinput->keybit);
	__set_bit(KEY_ENTER, myinput->keybit);
	/* 3��ע�� */
	input_register_device(myinput);
	/* 4��Ӳ�� */
	for(i=0;i<ARRAY_SIZE(keyDesc);i++)
	{
		request_irq(keyDesc[i].irq,myfun,IRQ_TYPE_EDGE_BOTH,keyDesc[i].name, (void *)&keyDesc[i]);
	}

	init_timer(&key_timer);
	key_timer.function = key_function;
	add_timer(&key_timer);
	
	return 0;
}
static __exit void input_key_exit(void)
{
	int i;
	for(i=0;i<ARRAY_SIZE(keyDesc);i++)
	{
		free_irq(keyDesc[i].irq,(void *)&keyDesc[i]);
	}
	input_unregister_device(myinput);
}

module_init(input_key_init);
module_exit(input_key_exit);
MODULE_LICENSE("GPL");
