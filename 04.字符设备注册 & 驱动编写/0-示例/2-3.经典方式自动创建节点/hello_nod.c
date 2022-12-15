
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


#define MY_MAJOR 0                 //主设备号写0则系统自动分配一个主设备号
#define DEVICE_NAME "hello_world"  //设备名
static int major;
static struct class * dev_class;
static struct device * device_p;

static int __init hello_init(void)
{   
    int err = 0;
    printk("正在注册设备\n");
    major = register_chrdev(MY_MAJOR,DEVICE_NAME,&dev_ops);  //主设备号   设备名    结构体集
    //>当major为0时候，表示让操作系统动态的分配一个主设备号，并且成功时返回这个主设备号
    //>当major不为0时，则使用major作为主设备，成功返回0，失败返回负数
    //>若主设备号已经被使用则会出错，返回值为负数
    // 不能自动创建设备节点文件，需要自己手动添加
    if(major < 0)
   	{
		printk("register_chrdev fail\n");
		return -1;
   	}   
    dev_class = class_create(THIS_MODULE,"ZSK");     //创建class类
    if (IS_ERR(dev_class))                   
    {
		printk("class_create fail\n");
		goto out;
    } 
    device_p = device_create(dev_class, NULL, MKDEV(major, 0), NULL, "ZSK_1");//创建设备节点	
    if (IS_ERR(device_p)) 
    {
    	printk("device_create fail\n");
		goto out;
    }    
    printk("register_chrdev success, major = %d\n",major);
    return 0;
out:                                               //注册失败要掉释放之前申请的设备号
    unregister_chrdev(major,DEVICE_NAME);	       //卸载的主设备号      设备名
    return 0;     
}
static void __exit hello_exit(void)
{    
    printk("exiting");                          //注意顺序
	device_destroy(dev_class,MKDEV(major,0));    //先删除设备节点
	class_destroy(dev_class);                    //再删除设备类
	unregister_chrdev(major,DEVICE_NAME);        //注销设备
	iounmap(gpbbase);                            //释放虚拟内存
	printk("end\n");
}

module_init(hello_init);
module_exit(hello_exit);


MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("KKKKKKKK"); 
