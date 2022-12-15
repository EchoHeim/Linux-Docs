
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>  
#define DEV_NAME "hello"
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

static int major = 0;    //用来存放主设备号
static struct cdev xyd_cdev;

static int __init hello_init(void)
{
    int ret;
    dev_t dev;
    cdev_init(&xyd_cdev,&dev_ops); //对结构体进行初始化，把fops加入到结构体中   
    dev = MKDEV(major, 0);
    if( major){
		// 静态设备号注册
		ret = register_chrdev_region(MKDEV(major,0), 1, DEV_NAME);
    }
    else{
		// 动态分配设备号
		ret = alloc_chrdev_region(&dev, 0, 1, DEV_NAME);
		major = MAJOR(dev);  //提取主设备号
    }    
    ret = cdev_add(&xyd_cdev,dev,1);  //真正的向内核注册这个设备   
    if(ret < 0)
    {
        printk (KERN_EMERG "cdev_add  err\r\n");
        goto out;
    }
    
    printk("linux2.6 init ! major is %d\n",major);
    return 0;
    
 out:   //注册失败要掉释放之前申请的设备号
    unregister_chrdev_region(dev, 1);	
    return ret;      
}

static void __exit hello_exit(void)
{
     cdev_del(&xyd_cdev);     //从内核卸载驱动
     unregister_chrdev_region(MKDEV(major, 0),1);   //释放设备号
     printk(KERN_EMERG "linux2.6 exit !\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
