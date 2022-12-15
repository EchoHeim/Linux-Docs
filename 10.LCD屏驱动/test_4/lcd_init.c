#include "includes.h"

screen_data mydata;                   //定义一个全局变量存放全局数据

int Lcd_init (void)
{
    mydata.fp = open(FB_NAME, O_RDWR);
    if (mydata.fp < 0) 
	{
        printf("打开帧缓冲设备失败!\r\n");
        return -1;
    }
    printf("打开帧缓冲设备成功!\r\n");
    if (ioctl(mydata.fp, FBIOGET_FSCREENINFO, &mydata.finfo)) 
	{
        printf("打开帧缓冲设备失败!\r\n");
        return -1;
    }
    if (ioctl(mydata.fp, FBIOGET_VSCREENINFO, &mydata.vinfo)) 
	{
        printf("打开帧缓冲设备失败!\r\n");
        return -1;
    }
	printf("LCD 分辨率:%d*%d   像素(bpp):%d\r\n",mydata.vinfo.xres,mydata.vinfo.yres,mydata.vinfo.bits_per_pixel);
    // 计算单帧画面占多少字节
    mydata.screensize  = mydata.vinfo.xres * mydata.vinfo.yres * mydata.vinfo.bits_per_pixel / 8;  
	mydata.screen_wide = mydata.vinfo.xres;
	mydata.screen_high = mydata.vinfo.yres;
	mydata.bpp         = mydata.vinfo.bits_per_pixel;
    //把fp所指的文件中从开始到screensize大小的内容给映射出来，得到一个指向这块空间的指针;

    mydata.fbp = (unsigned char *) mmap (NULL, mydata.screensize, PROT_READ | PROT_WRITE, MAP_SHARED, mydata.fp, 0);
    if (NULL == mydata.fbp) 
	{
        printf ("mmap fail\r\n");
        return -1;
    }
    return 0;
}

void Lcd_close(void )
{
    munmap (mydata.fbp, mydata.screensize); /*解除映射*/
    close (mydata.fp);                      /*关闭文件*/
}

/************************************************************************
 把存放在内存中的字符拼接为一个长整形数据返回。
实际是我们的数字在内存中存放以字节形式存放的，
如:0x12345678,其实是0x78,0x56,0x34,0x12这样存放。
************************************************************************/
long char_to_long( char * string, int length )
{
	long number;
	if (length <= 4)
	{
		memset( &number, 0x00, sizeof(long) );  //清空
		memcpy( &number, string, length );      //填充
	}
	return number;
}

void lcd_clear(unsigned long color)		//清屏
{
	int x,y;
	for(x=0;x<800;x++)
	{
		for(y=0;y<480;y++)
			show_point(x,y,color);
	}
}

