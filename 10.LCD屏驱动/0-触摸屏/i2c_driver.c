#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#include <plat/ctouch.h>
#include <plat/ft5x0x_touch.h>

typedef struct TouchDes {
    int point;
    u16 x;
    u16 y;
    u16 pressure;
} T_Event, *PT_Event;

/* ������нṹ�� */
static struct workqueue_struct *queue = NULL;
static struct work_struct work;
static PT_Event ts = NULL;
static struct i2c_client *tsclient = NULL;
/* ����һ���ṹ����������x��y���� */
static struct input_dev *myinput = NULL;
static DEFINE_SEMAPHORE(sem);

static const struct i2c_device_id ft5x0x_id_table[] = 
{
    { "ft5x0x", 0 },
    {}
};

void Test_and_Set(struct i2c_client *client)
{
    s32 val;
	
    printk("slaaddr : 0x%x\n", client->addr);
	
    /* ��ȡ�̼�id */
    val = i2c_smbus_read_byte_data(client, 0xa6);
	
    /* ��ȡ����id */
    printk("Firmware ID : 0x%x\n", val);

	
    val = i2c_smbus_read_byte_data(client, 0xa8);
    printk("vendor's chip id : 0x%x\n", val);
	
    /* ���õ�ԴģʽΪ����ģʽ */
    i2c_smbus_write_byte_data(client, 0xa5, 0);
	
    /* ��ȡ�Ƿ�������ȷ */
    val = i2c_smbus_read_byte_data(client, 0xa5);
	
    printk("PMODE is : 0x%x\n", val);
}

static void ts_wrok_handler(struct work_struct *data)
{
    static int count = 0;
	
    u8 buf[1024];
	//��ȡ�ź����������ȡ���ɹ���������������ɹ�ֱ�ӷ���
    down_interruptible(&sem); 
    
    /* ��ȡ���ݲ����ϴ�:�ڴ˴�������ȡ7���Ĵ�����ַ */
    i2c_smbus_read_i2c_block_data(tsclient, 0, 7, buf);
	
    /* ��ȡ�������� */
    ts->point = buf[2] & 0x07;
    if(!ts->point ) {
        printk("-----------------\n");
        input_report_abs(myinput, ABS_PRESSURE, 0);
        input_report_key(myinput, BTN_TOUCH, 0);
        input_sync(myinput);
    }

    if(ts->point == 1) {
        ts->x = (s16)(buf[3] & 0x0f) << 8 | buf[4];
        ts->y = (s16)(buf[5] & 0x0f) << 8 | buf[6];

        ts->pressure = 1;
		
        printk("x = %d\n", ts->x);
        printk("y = %d\n", ts->y);
		
        input_report_abs(myinput, ABS_X, ts->x);
        input_report_abs(myinput, ABS_Y, ts->y);
        input_report_abs(myinput, ABS_PRESSURE, ts->pressure);
        input_report_key(myinput, BTN_TOUCH, 1);
        input_sync(myinput);
    }
    up(&sem);
}

static irqreturn_t ft5x0x_ts_interrupt(int irq, void *dev_id)
{
    schedule_work(&work);
    return IRQ_HANDLED;
}

/* ��Ե���� */
static int __devinit ft5x0x_probe(struct i2c_client *client,const struct i2c_device_id *id)
{
    s32 val;
	
    tsclient = client;
	
    ts = (PT_Event)kmalloc(sizeof(T_Event), GFP_KERNEL);
    if(NULL == ts) {
        printk("malloc error!!\n");
        return -1;
    }
	
    printk("ts = %p\n", ts);
	
    /* 1������input_dev�ṹ�� */
    myinput = input_allocate_device();
    if(NULL == myinput) {
        printk("input alloc error!!\n");
        return -1;
    }
	
    /* 2������ */
    /* 2.1�������¼� */
    /* ����Ϊͬ���¼� */
    set_bit(EV_SYN, myinput->evbit);
	
    /* ����Ϊ���������¼� */
    set_bit(EV_ABS, myinput->evbit);
    set_bit(EV_KEY, myinput->evbit);

    /* 2.2��������һ���¼��������¼� */
    set_bit(ABS_X, myinput->absbit);
    set_bit(ABS_Y, myinput->absbit);
    set_bit(ABS_PRESSURE, myinput->absbit);
    set_bit(BTN_TOUCH, myinput->keybit);
	
    /* ����С */
    input_set_abs_params(myinput, ABS_X, 0, 799, 0, 0);
    input_set_abs_params(myinput, ABS_Y, 0, 479, 0, 0);
    input_set_abs_params(myinput, ABS_PRESSURE, 0, 1, 0 , 0);
	
    /* 3��ע�� */
    input_register_device(myinput);
	
    msleep(15);
	
    Test_and_Set(client);
	
    /* ����һ�����̹߳������� */
    queue = create_singlethread_workqueue("myqueue"); 
    if (!queue) {
        printk("create workqueue is error!!!\n");
        return -1;
    }
	
    /* ��ʼ��һ������ */
    INIT_WORK(&work, ts_wrok_handler);
	
    /* 4��Ӳ�� */
    request_irq(IRQ_EINT(14), ft5x0x_ts_interrupt, IRQ_TYPE_EDGE_FALLING, "ft5x0x", (void *)ts);
	
    return 0;
}

static int __devexit ft5x0x_remove(struct i2c_client *client)
{
    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    free_irq(IRQ_EINT(14), (void *)ts);
    input_unregister_device(myinput);
    kfree(ts);
    return 0;
}

static struct i2c_driver ft5x0x_driver = {
    .driver = {
        .name   = "xyd",            //������ sys/bus/i2c/drivers�鿴��
        .owner  = THIS_MODULE,
    },
    .probe      = ft5x0x_probe,
    .remove     = __devexit_p(ft5x0x_remove),
    .id_table   = ft5x0x_id_table,
};

static __init int ft5x0x_drv_init(void)
{
    /* ע��һ��IIC���� */
    i2c_add_driver(&ft5x0x_driver);
    return 0;
}

static __exit void ft5x0x_drv_exit(void)
{
    i2c_del_driver(&ft5x0x_driver);
}

module_init(ft5x0x_drv_init);
module_exit(ft5x0x_drv_exit);
MODULE_LICENSE("GPL");
