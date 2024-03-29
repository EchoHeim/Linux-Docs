//linux2.6版本的注册方式
//cdev方式

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>  //注意此处的头文件
#include <linux/device.h>  


//#define MY_MAJOR 150
#define DEV_NAME "dev_26"

static int hello_open(struct inode *pinode, struct file *pfile)
{
	printk ("linux26  is call\r\n");
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

static struct class * dev_class;
static struct device * device_p;

static int major = 0;
static struct cdev xyd_cdev;

static int __init hello_init(void)
{
    int ret;
    int err = 0;
    dev_t dev;
    cdev_init(&xyd_cdev,&dev_ops); //对结构体进行初始化，把fops加入到结构体中   
    xyd_cdev.owner = THIS_MODULE;//指定结构所属模块。
    if( major ){
	    // 给定设备号注册
        dev = MKDEV(major, 0);
    	ret = register_chrdev_region(dev, 1, DEV_NAME);
    }
    else{
    	// 动态分配设备号
    	ret = alloc_chrdev_region(&dev, 0, 1, DEV_NAME);
    	major = MAJOR(dev);  //提取主设备号
    } 
    if(ret < 0)
    {
    	printk(KERN_EMERG "chrdev_region err\r\n");   
    	return ret;
    }
    
    ret = cdev_add(&xyd_cdev,dev,1);  //真正的向内核注册这个设备   
    if(ret < 0)
    {
         printk (KERN_EMERG "cdev_add  err\r\n");
	 goto out;
    }
	// 创建/dev设备结点
    dev_class = class_create(THIS_MODULE,"dev_class_26"); //创建class类
    if (IS_ERR(dev_class))
    {
    	printk("Err: failed in creating class.\n");
    	goto out;
    } 
    device_p = device_create(dev_class, NULL, MKDEV(major, 0), NULL, "linux_26");//创建设备节点	
    if (IS_ERR(device_p)) {
		err = PTR_ERR(device_p);
		goto out;
    } 
       
    printk(KERN_EMERG "linux2.6 init ! major is %d\n",major);
    return 0;
    
 out:   //注册失败要掉释放之前申请的设备号
    unregister_chrdev_region(dev, 1);	
    return ret;      
}

static void __exit hello_exit(void)
{
     device_destroy(dev_class,MKDEV(major,0)); //注意顺序
     class_destroy(dev_class);	
     cdev_del(&led_cdev);     //从内核卸载设备
     unregister_chrdev_region(MKDEV(major, 0),1);   //释放设备号
     printk(KERN_EMERG "linux2.6 exit !\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");


