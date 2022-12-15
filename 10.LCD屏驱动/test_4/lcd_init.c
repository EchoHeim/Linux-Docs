#include "includes.h"

screen_data mydata;                   //����һ��ȫ�ֱ������ȫ������

int Lcd_init (void)
{
    mydata.fp = open(FB_NAME, O_RDWR);
    if (mydata.fp < 0) 
	{
        printf("��֡�����豸ʧ��!\r\n");
        return -1;
    }
    printf("��֡�����豸�ɹ�!\r\n");
    if (ioctl(mydata.fp, FBIOGET_FSCREENINFO, &mydata.finfo)) 
	{
        printf("��֡�����豸ʧ��!\r\n");
        return -1;
    }
    if (ioctl(mydata.fp, FBIOGET_VSCREENINFO, &mydata.vinfo)) 
	{
        printf("��֡�����豸ʧ��!\r\n");
        return -1;
    }
	printf("LCD �ֱ���:%d*%d   ����(bpp):%d\r\n",mydata.vinfo.xres,mydata.vinfo.yres,mydata.vinfo.bits_per_pixel);
    // ���㵥֡����ռ�����ֽ�
    mydata.screensize  = mydata.vinfo.xres * mydata.vinfo.yres * mydata.vinfo.bits_per_pixel / 8;  
	mydata.screen_wide = mydata.vinfo.xres;
	mydata.screen_high = mydata.vinfo.yres;
	mydata.bpp         = mydata.vinfo.bits_per_pixel;
    //��fp��ָ���ļ��дӿ�ʼ��screensize��С�����ݸ�ӳ��������õ�һ��ָ�����ռ��ָ��;

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
    munmap (mydata.fbp, mydata.screensize); /*���ӳ��*/
    close (mydata.fp);                      /*�ر��ļ�*/
}

/************************************************************************
 �Ѵ�����ڴ��е��ַ�ƴ��Ϊһ�����������ݷ��ء�
ʵ�������ǵ��������ڴ��д�����ֽ���ʽ��ŵģ�
��:0x12345678,��ʵ��0x78,0x56,0x34,0x12������š�
************************************************************************/
long char_to_long( char * string, int length )
{
	long number;
	if (length <= 4)
	{
		memset( &number, 0x00, sizeof(long) );  //���
		memcpy( &number, string, length );      //���
	}
	return number;
}

void lcd_clear(unsigned long color)		//����
{
	int x,y;
	for(x=0;x<800;x++)
	{
		for(y=0;y<480;y++)
			show_point(x,y,color);
	}
}

