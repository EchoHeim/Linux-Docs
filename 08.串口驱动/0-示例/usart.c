#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
static unsigned int *base=NULL;
static unsigned int *base0=NULL;
#define GPA1CON (*(volatile unsigned int *)(base+0))

#define ULCON2 (*(volatile unsigned int *)(base0+0))
#define UCON2 (*(volatile unsigned int *)(base0+1))
#define UFCON2 (*(volatile unsigned int *)(base0+2))
#define UTRSTAT2 (*(volatile unsigned int *)(base0+4))
#define UTXH2 (*(volatile unsigned int *)(base0+8))
#define URXH2 (*(volatile unsigned int *)(base0+9))
#define UBRDIV2 (*(volatile unsigned int *)(base0+10))
#define UFRACVAL2 (*(volatile unsigned int *)(base0+11))



int myusart_open(struct inode *num,struct file *file)
{
	return 0;
}
int myusart_close(struct inode *num,struct file *file)
{
	return 0;
}
ssize_t myusart_read(struct file *fp, char __user *buffer, size_t size, loff_t *offset)
{
	unsigned char ch;
	//等待数据寄存器不为空
	while(!(UTRSTAT2 &(0x01<<0)));
	ch=URXH2;
	copy_to_user(buffer,&ch,1);
	return 0;
}

ssize_t myusart_write(struct file *fp, const char __user *buffer, size_t size, loff_t *offset)
{
	unsigned char ch;
	while(!(UTRSTAT2 &(0x01<<1)));
	copy_from_user(&ch,buffer,1);
	UTXH2=ch;
	return 0;
}

static struct file_operations my_fops=
{
	.owner=THIS_MODULE,
	.open=myusart_open,
	.release=myusart_close,
	.read=myusart_read,
	.write=myusart_write,
};
static struct miscdevice misc=
{
	.name="myusart2",
	.minor=255,
	.fops=&my_fops,
};
static int __init myusart_init(void)
{
	base=(unsigned int *)ioremap(0x11400020,0x16);
	base0=(unsigned int *)ioremap(0x13820000,0x32);
	GPA1CON &=~0xff;
	GPA1CON |=((0x2<<0)|(0x2<<4));
	
	//ULCON2 &=0x00000000;
	ULCON2 |=(0x11<<0);
	
	//UCON2 &=0x00000000;
	UCON2 |=((0x01<<0)|(0x01<<2));

	//UFCON2 &=0x00000000;
	UFCON2 |=(0x01<<0);

	UBRDIV2=0x35;
	UFRACVAL2=0x4;
	int ret=misc_register(&misc);
	if(ret<0)
	{
		printk("register failed!!\n");
		return -1;
	}
	printk("register succeed!!!\n");
	return 0;
}
static void __exit myusart_exit(void)
{
	misc_deregister(&misc);
}
module_init(myusart_init);
module_exit(myusart_exit);
MODULE_LICENSE("GPL");











