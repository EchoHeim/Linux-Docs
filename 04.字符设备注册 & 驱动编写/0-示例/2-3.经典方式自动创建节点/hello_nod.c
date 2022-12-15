
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/mm.h>

static int hello_open(struct inode *pinode, struct file *pfile)
{
	printk ("hello_open is call\r\n",);
	return 0;
}

static struct file_operations dev_ops =
{		
    .owner = THIS_MODULE,      
    .open  = hello_open,
};


#define MY_MAJOR 0                 //���豸��д0��ϵͳ�Զ�����һ�����豸��
#define DEVICE_NAME "hello_world"  //�豸��
static int major;
static struct class * dev_class;
static struct device * device_p;

static int __init hello_init(void)
{   
    int err = 0;
    printk("����ע���豸\n");
    major = register_chrdev(MY_MAJOR,DEVICE_NAME,&dev_ops);  //���豸��   �豸��    �ṹ�弯
    //>��majorΪ0ʱ�򣬱�ʾ�ò���ϵͳ��̬�ķ���һ�����豸�ţ����ҳɹ�ʱ����������豸��
    //>��major��Ϊ0ʱ����ʹ��major��Ϊ���豸���ɹ�����0��ʧ�ܷ��ظ���
    //>�����豸���Ѿ���ʹ������������ֵΪ����
    // �����Զ������豸�ڵ��ļ�����Ҫ�Լ��ֶ����
    if(major < 0)
   	{
		printk("register_chrdev fail\n");
		return -1;
   	}   
    dev_class = class_create(THIS_MODULE,"ZSK");     //����class��
    if (IS_ERR(dev_class))                   
    {
		printk("class_create fail\n");
		goto out;
    } 
    device_p = device_create(dev_class, NULL, MKDEV(major, 0), NULL, "ZSK_1");//�����豸�ڵ�	
    if (IS_ERR(device_p)) 
    {
    	printk("device_create fail\n");
		goto out;
    }    
    printk("register_chrdev success, major = %d\n",major);
    return 0;
out:                                               //ע��ʧ��Ҫ���ͷ�֮ǰ������豸��
    unregister_chrdev(major,DEVICE_NAME);	       //ж�ص����豸��      �豸��
    return 0;     
}
static void __exit hello_exit(void)
{    
    printk("exiting");                          //ע��˳��
	device_destroy(dev_class,MKDEV(major,0));    //��ɾ���豸�ڵ�
	class_destroy(dev_class);                    //��ɾ���豸��
	unregister_chrdev(major,DEVICE_NAME);        //ע���豸
	iounmap(gpbbase);                            //�ͷ������ڴ�
	printk("end\n");
}

module_init(hello_init);
module_exit(hello_exit);


MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("KKKKKKKK"); 
