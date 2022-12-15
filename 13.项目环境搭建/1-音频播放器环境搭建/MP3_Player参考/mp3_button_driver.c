#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <mach/regs-gpio.h>
#include <mach/hardware.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/sched.h>
#include <linux/gpio.h>
#include <linux/timer.h>
#include <linux/poll.h>




/*�����������򣬴���ȫ���İ���*/
/*����һ:�жϺ�  ������: ע���жϵĵ��������*/
static struct class * dev_class;
static struct device * dev_device;
static int major;
static struct timer_list my_timer;


static char key_value; 
static volatile int btn_con;

struct pin_info{
	int  irq;
	int  pin;
	int  value;
	char *name;
};
static struct pin_info pins[6] = {
	{IRQ_EINT8, S3C2410_GPG(0), 1,"K1"},
	{IRQ_EINT11,S3C2410_GPG(3), 2,"K2"},
	{IRQ_EINT13,S3C2410_GPG(5), 3,"K3"},
	{IRQ_EINT14,S3C2410_GPG(6), 4,"K4"},
	{IRQ_EINT15,S3C2410_GPG(7), 5,"K5"},
	{IRQ_EINT19,S3C2410_GPG(11),6,"K6"},
};

static struct pin_info * pin_p;

static DECLARE_WAIT_QUEUE_HEAD(btn_wq);


static irqreturn_t irq_handler(int irq, void * dev)
{
	pin_p = (struct pin_info *)dev;
	mod_timer(&my_timer,jiffies + HZ/100);
	return 	IRQ_RETVAL(IRQ_HANDLED);	
}

//����ʱ�䵽����øú���
static void my_function(unsigned long num)
{
	/*��ȡ����ֵ*/
	if(s3c2410_gpio_getpin(pin_p->pin)){
		key_value = pin_p->value;  /*̧��*/	
		btn_con = 1;
	}
	else{
		key_value = 10 + pin_p->value;/*����״̬*/
		btn_con = 0;//����Ӧ�ò�Ͳ����ȡ����ʱ�ļ�ֵ��
	}
	
	wake_up_interruptible(&btn_wq); 
	
}

static int btn_open(struct inode *inode, struct file *filp)
{
	/*
	irq ���жϱ��
	handler ���жϷ�����
	flags : �жϴ�����ʽ
	name  ���ж��� 
	dev   : ���Ƕ�Ӧ���ݸ��жϷ������Ĳ���
	*/	
	int i;
	for(i=0;i<6;i++)
	{
		request_irq(pins[i].irq,irq_handler,IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING
					  ,pins[i].name,&pins[i]);
	}

	btn_con = 0;
	return 0;
}
static int btn_close(struct inode *inode, struct file *filp)
{
	int i;
	for(i=0;i<6;i++)
	{
		free_irq(pins[i].irq,&pins[i]);
	}
	return 0;
}

//	char key_value;
//	read(fd,&key_value,1);

static ssize_t btn_read(struct file *filp, char __user *usr_buf, size_t count, loff_t * loff)
{
	int ret;
	/*���м�����ʱ����Ӧ�ò㷵�����ݣ�û�м����£��ȴ�ֱ���а�������*/
	//�ȴ�����wati queue
	wait_event_interruptible(btn_wq,btn_con);
	btn_con = 0;
	
	ret = copy_to_user(usr_buf,&key_value,count);
	if(ret != 0){
		return -EINVAL;
	}
	return 0;	
}

static unsigned int btn_poll(struct file *filp, struct poll_table_struct *wait)
{
	unsigned int mask = 0;
	poll_wait(filp, &btn_wq, wait);
    //���һ���ȴ����е�poll_table�ṹ��
	//����������˳��������жϴ����л��Ѷ��У�����poll��ѯʱ�䵽
	//�ú�����һϵ�е�poll�������ú���timer�����ý�������

	 //�ж����ַ�ʽ�˳���˯��
	if (btn_con)	//�а�������
	{
		printk("which key is down ?\n");
		mask |= POLLIN | POLLRDNORM;
	}
	else			//��ʱʱ�䵽
		mask = 0;
	
	return mask;	
}


static struct file_operations btn_fops = {
	.open 	 = btn_open,
	.release = btn_close,
	.read    = btn_read,
	.poll    = btn_poll,
};

static int button_init(void)
{
	int ret;

	init_timer(&my_timer);
	my_timer.expires = jiffies + 5*HZ;
	my_timer.function = my_function;
	my_timer.data = 0; 
	
	printk("my_timer_init\n");
	printk("ARM HZ is %d\n",HZ);
	
	/*ע���豸*/
	major = register_chrdev(0,"buttons",&btn_fops);
	if(major < 0){
		printk("register error\n");
		return -EINVAL;		
	}
	printk("major is %d\n",major);
	dev_class = class_create(THIS_MODULE, "dev_btn");//����һ���࣬
	if (IS_ERR(dev_class))
	{	ret = PTR_ERR(dev_class);
		goto free_unregister;
	}
	dev_device = device_create(dev_class,NULL,MKDEV(major,0),NULL,"my_buttons");
	if (IS_ERR(dev_device))
	{	ret = PTR_ERR(dev_device);
		goto free_class_create;
	}	
	return 0;
free_class_create:
	class_destroy(dev_class);	
free_unregister:
	unregister_chrdev(major,"buttons");
	return ret;
}

static void button_exit(void)
{
	del_timer(&my_timer);
	device_destroy(dev_class,MKDEV(major,0));
	class_destroy(dev_class);
	unregister_chrdev(major,"buttons");	
}

module_init(button_init);
module_exit(button_exit);
MODULE_LICENSE("GPL");
