#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#define GPM4_BASE 0x110002E0
unsigned long *gpm4base = NULL;
#define GPM4CON (*(volatile unsigned long *)gpm4base)
#define GPM4DAT (*(volatile unsigned long *)(gpm4base+1))
static dev_t leddrv_num;
static struct cdev *leddrv_cdev = NULL;
static struct class *leddrv_class = NULL;
static int led_minor;
/* 4、编写操作函数 */
static int leddrv_open(struct inode *inod, struct file *fil)
{
  led_minor =  iminor(inod);
	if(led_minor == 0)
			GPM4DAT &= ~(1<<0); 	
	if(led_minor == 1)
			GPM4DAT &= ~(1<<1); 
	if(led_minor == 2)
			GPM4DAT &= ~(1<<2); 
	if(led_minor == 3)
			GPM4DAT &= ~(1<<3); 
	return 0;
}
static int leddrv_release(struct inode *inod, struct file *fil)
{
	led_minor =  iminor(inod);
	if(led_minor == 0)
			GPM4DAT |= (1<<0); 	
	if(led_minor == 1)
			GPM4DAT |= (1<<1); 
	if(led_minor == 2)
			GPM4DAT |= (1<<2); 
	if(led_minor == 3)
			GPM4DAT |= (1<<3); 
	return 0;
}

/* 3、构造file_operations结构体 */

static struct file_operations leddrv_fops =
{
   .owner   = THIS_MODULE,
   .open    = leddrv_open,
   .release = leddrv_release,
};

/* 2、编写初始化和退出函数 */ 

static unsigned char *node_name[4] = {"led0","led1","led2","led3"};

static int __init leddrv_init(void)
{
	int i;
	
    /* 5、注册 cdev */
    // 5.1、申请设备号
    alloc_chrdev_region(&leddrv_num,0,4,"leddrv");

	// 5.2、构造cdev结构体
    leddrv_cdev = cdev_alloc();

	leddrv_cdev->count = 4;
	leddrv_cdev->dev   = leddrv_num;
	leddrv_cdev->ops   = &leddrv_fops;
    leddrv_cdev->owner = THIS_MODULE;

	// 5.3、初始化cdev结构体，关联file_operations
	cdev_init(leddrv_cdev,&leddrv_fops);

	// 5.4、注册cdev
	cdev_add(leddrv_cdev,leddrv_num,4);

	// 6.1、自动生成设备节点

	leddrv_class = class_create(THIS_MODULE,"leddrv_class");

	for(i=0;i<4;i++)
	  device_create(leddrv_class,NULL,leddrv_num+i,NULL,node_name[i]);

	/* 7.1、地址映射 */
    gpm4base = (unsigned long *)ioremap(GPM4_BASE,8);

	/* 8、初始化LED */
    GPM4CON |=0x1111<<0;
	GPM4DAT |=0xF<<0;

	return 0;
}

static void __exit leddrv_exit(void)
{
    int i;
	
    // 7.2、取消地址映射
    iounmap(gpm4base);
	
    // 6.2、摧毁节点

	for(i=0;i<4;i++)    
	  device_destroy(leddrv_class,leddrv_num+i);

	class_destroy(leddrv_class);
    

	// 5.5、卸载注册
	cdev_del(leddrv_cdev);

	// 5.7、释放设备号
	unregister_chrdev_region(leddrv_num,4);

}

/* 1、指定入口出口 */
module_init(leddrv_init);
module_exit(leddrv_exit);
MODULE_LICENSE("GPL");

