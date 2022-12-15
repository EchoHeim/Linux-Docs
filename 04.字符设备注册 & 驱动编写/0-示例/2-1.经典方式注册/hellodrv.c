#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/mm.h>
/*经典方式不会产生设备节点，需要手动创建

主设备号你可以创建成功后打印出来也可以  cat /proc/devices 查看到主设备号，
然后  mknod /dev/my_hello c 主设备号 次设备号  
*/
static int major;
static struct file_operations hello_fops = 
{
	.owner = THIS_MODULE,
};
static int __init hello_init(void)
{
	major=register_chrdev(0,"my_hello",&hello_fops);
	if(major<0)
	{
		printk("register fail!!!\n");
		return -1;
	}
	printk("register success!!! major = %d\n",major);
	return 0;
}
static void __exit hello_exit(void)
{
	unregister_chrdev(major,"my_hello");
	printk("bye bye!!!\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
