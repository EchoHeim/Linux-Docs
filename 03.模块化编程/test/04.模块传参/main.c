#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/stat.h>

char *p="first step!";
int n=5;
int num[10]={0};

static int __init hello(void)
{
	int i=0;
	printk("hello world!\n");
	printk("str = %s",p);
	for(i=0;i<n;i++)
		printk("%d ",num[i]);
	printk("\n");	
	return 0;
}

static void __exit bye(void)
{
	printk("Thanks! bye!\n");
}

module_param(n,int,S_IRUGO);
module_param(p,charp,S_IRUGO);
module_param_array(num,int,NULL,0644);
module_init(hello);
module_exit(bye);
MODULE_LICENSE("GPL");



