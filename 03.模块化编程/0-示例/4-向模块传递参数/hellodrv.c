#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/stat.h>
static int par = 5;
static char *str = "hello driver!!!!!";
static int arr[10] = {0,1,2,3,4};
static int num;
static int __init hello_init(void)
{
	int i;
	printk("hello init is call!!!\n");
	printk("par = %d\n",par);
	printk("str = %s\n",str);
	for(i=0;i<10;i++)
		printk("%4d",arr[i]);
	printk("\n");
	printk("num = %d\n",num);
	return 0;
}
static void __exit hello_exit(void)
{
	printk("hello_exit is call!!!\n");
}
module_param(par,int,S_IRUGO);
module_param(str,charp,S_IRUGO);
module_param_array(arr,int,&num,S_IRUGO);
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
