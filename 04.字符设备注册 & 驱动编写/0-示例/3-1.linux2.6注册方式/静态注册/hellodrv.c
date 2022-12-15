#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
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
static int major = 100;    
static struct cdev xyd_cdev;
static int __init hello_init(void)
{
    int ret;
    cdev_init(&xyd_cdev,&dev_ops); //对结构体进行初始化，把fops加入到结构体中   
    xyd_cdev.dev = MKDEV(major, 0);
    xyd_cdev.owner = THIS_MODULE;
	ret = register_chrdev_region(xyd_cdev.dev, 1, "hello_2.6");
    ret = cdev_add(&xyd_cdev,xyd_cdev.dev,1);  //真正的向内核注册这个设备   
    if(ret < 0)
    {
        printk (KERN_EMERG "cdev_add  err\r\n");
        goto out;
    }  
    return 0; 
 out:  
    unregister_chrdev_region(xyd_cdev.dev,1);	
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
