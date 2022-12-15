//linux2.6�汾��ע�᷽ʽ
//cdev��ʽ

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>  //ע��˴���ͷ�ļ�

//#define MY_MAJOR 150
#define DEV_NAME "dev_26"

static int hello_open(struct inode *pinode, struct file *pfile)
{
	printk ("linux26 is call\r\n");
	return 0;
}

static int hello_release(struct inode *pinode, struct file *pfile)
{
    printk ("linux26  is call\r\n");
    return 0;
}

static struct file_operations dev_ops =
{
    .owner = THIS_MODULE,     
    .open  = hello_open,
    .release= hello_release,
};

static int major = 0;    //����������豸��
static struct cdev xyd_cdev;

//���
static int __init hello_init(void)
{
    int ret;
    dev_t dev;
    cdev_init(&xyd_cdev,&dev_ops); //�Խṹ����г�ʼ������fops���뵽�ṹ���� 
    xyd_cdev.owner = THIS_MODULE;  
    dev = MKDEV(major, 0);
    if( major ){
		// ��̬�豸��ע��
		ret = register_chrdev_region(MKDEV(major,0), 1, DEV_NAME);
    }
    else{
		// ��̬�����豸��
		ret = alloc_chrdev_region(&dev, 0, 1, DEV_NAME);
		major = MAJOR(dev);  //��ȡ���豸��
    }    
    ret = cdev_add(&xyd_cdev,dev,1);  //���������ں�ע������豸   
    if(ret < 0)
    {
        printk (KERN_EMERG "cdev_add  err\r\n");
        goto out;
    }
    
    printk(KERN_EMERG "linux2.6 init ! major is %d\n",major);
    return 0;
    
 out:   //ע��ʧ��Ҫ���ͷ�֮ǰ������豸��
    unregister_chrdev_region(dev, 1);	
    return ret;      
}

static void __exit hello_exit(void)
{
     cdev_del(&xyd_cdev);     //���ں�ж������
     unregister_chrdev_region(MKDEV(major, 0),1);   //�ͷ��豸��
     printk(KERN_EMERG "linux2.6 exit !\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");


