#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include "lcd.h"


#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int

#define FB_NAME     "/dev/fb0"   //打开的帧缓冲设备名

extern unsigned char use_hz_index[];
extern unsigned char use_zf_index[];
extern unsigned char use_hz[];
extern unsigned char use_zf[];


extern const unsigned char fontdata_8x16[];

/* 文件头结构 14byte  */ 
typedef struct
{
	char cfType[2];         /* 文件类型, 必须为 "BM" (0x4D42)*/
	char cfSize[4];         /* 文件的大小(字节) */
	char cfReserved[4];     /* 保留, 必须为 0 */
	char cfoffBits[4];      /* 位图阵列相对于文件头的偏移量(字节)*/
}__attribute__((packed)) BITMAPFILEHEADER;       

/* 位图信息头结构40byte */
typedef struct
{
	char ciSize[4];         /* size of BITMAPINFOHEADER */
	char ciWidth[4];        /* 位图宽度(像素) */
	char ciHeight[4];       /* 位图高度(像素) */
	char ciPlanes[2];       /* 目标设备的位平面数, 必须置为1 */
	char ciBitCount[2];     /* 每个像素的位数, 1,4,8或24 */
	char ciCompress[4];     /* 位图阵列的压缩方法,0=不压缩 */
	char ciSizeImage[4];    /* 图像大小(字节) */
	char ciXPelsPerMeter[4];/* 目标设备水平每米像素个数 */
	char ciYPelsPerMeter[4];/* 目标设备垂直每米像素个数 */
	char ciClrUsed[4];      /* 位图实际使用的颜色表的颜色数 */
	char ciClrImportant[4]; /* 重要颜色索引的个数 */
}__attribute__((packed)) BITMAPINFOHEADER;       


//位图的颜色结构体(888)
typedef struct
{
	unsigned short blue:8;
	unsigned short green:8;
	unsigned short red:	8;
}__attribute__((packed)) PIXEL;


typedef struct
{
	unsigned char *fbp;              //文件映射的虚拟地址指针
	long screensize;                 //每帧图像的大小(字节)
	struct fb_var_screeninfo vinfo;  //打开的帧缓冲设备的可变参数
	struct fb_fix_screeninfo finfo;  //打开的帧缓冲设备的不可变参数
	int  fp;                         //打开的文件描述符
	int bpp;                         //色深
	int screen_high;                 //屏幕高                     
	int screen_wide;                 //屏幕宽
}screen_data;


screen_data mydata;                   //定义一个全局变量存放全局数据
BITMAPFILEHEADER FileHead;
BITMAPINFOHEADER InfoHead;


int FB_init (void)
{
    mydata.fp = open (FB_NAME, O_RDWR);
    if (mydata.fp < 0) 
	{
        printf("open fb0 fail!!!\r\n");
        return -1;
    }
    printf("open fb0 success\r\n");

    if (ioctl(mydata.fp, FBIOGET_FSCREENINFO, &mydata.finfo)) 
	{
        printf("get finfo fail\r\n");
        return -1;
    }	
    if (ioctl(mydata.fp, FBIOGET_VSCREENINFO, &mydata.vinfo)) 
	{
        printf("get vinfo fail \r\n");
        return -1;
    }
	printf("LCD size:%d*%d   bpp:%d\r\n",mydata.vinfo.xres,mydata.vinfo.yres,mydata.vinfo.bits_per_pixel);
    // 计算单帧画面占多少字节
    mydata.screensize  = mydata.vinfo.xres * mydata.vinfo.yres * mydata.vinfo.bits_per_pixel / 8;  
	mydata.screen_wide = mydata.vinfo.xres;
	mydata.screen_high = mydata.vinfo.yres;
	mydata.bpp         = mydata.vinfo.bits_per_pixel;
    //把fp所指的文件中从开始到screensize大小
    //的内容给映射出来，得到一个指向这块空间
    //的指针
    mydata.fbp = (unsigned char *) mmap (NULL, mydata.screensize, PROT_READ | PROT_WRITE, MAP_SHARED, mydata.fp, 0);
    if (NULL == mydata.fbp) 
	{
        printf ("mmap fail\r\n");
        return -1;
    }
    return 0;
}
void FB_close(void )
{
    munmap (mydata.fbp, mydata.screensize); /*解除映射*/
    close (mydata.fp);                      /*关闭文件*/
}



/************************************************************************
 把存放在内存中的字符拼接为一个长整形数据返回。
实际是我们的数字在内存中存放以字节形式存放的，
如0x12345678,其实是0x78,0x56,0x34,0x12这样存放
************************************************************************/
long chartolong( char * string, int length )
{
	long number;

	if (length <= 4)
	{
		memset( &number, 0x00, sizeof(long) );  //清空
		memcpy( &number, string, length );      //填充
	}

	return number;
}

int Show_bmp( int x,int y ,char *bmpfile )
{
	FILE *fp;
	int rc;
	int ciBitCount, ciWidth, ciHeight;
	int line_x, line_y;
	long int location = 0, BytesPerLine = 0;
	char tmp[1024*10];

	/* (1)打开位图文件 */
	fp = fopen( bmpfile, "rb" );   //以二进制的只读方式打开文件
	if (fp == NULL)
	{
		printf("open bmpfile fail\r\n");
		return -1;
	}

	/*(2) 读取位图文件头 */
	rc = fread( &FileHead, sizeof(BITMAPFILEHEADER),1, fp);
	if ( rc != 1)
	{
		printf("get FileHead fail\r\n");
		fclose( fp );
		return -2;
	}

	/*(3) 判断位图的类型 */
	if (memcmp(FileHead.cfType, "BM", 2) != 0)  //内存对比
	{
		printf("picture is not bmp\r\n");
		fclose( fp );
		return -3;
	}

	/* (4)读取位图信息头 */
	rc = fread( (char *)&InfoHead, sizeof(BITMAPINFOHEADER),1, fp );
	if ( rc != 1)
	{
		printf("get FileHead fail\r\n");
		fclose( fp );
		return -4;
	}

	ciWidth    = (int) chartolong( InfoHead.ciWidth,    4 );//获得图片宽
	ciHeight   = (int) chartolong( InfoHead.ciHeight,   4 );//获得图片高
	ciBitCount = (int) chartolong( InfoHead.ciBitCount, 4 );//获得图片色深

	/*(5)将文件光标移动到文件的数据区 */
	fseek(fp, (int)chartolong(FileHead.cfoffBits, 4), SEEK_SET);

	/*(6)计算每行有多少个字节*/
	BytesPerLine = ciWidth * (ciBitCount / 8);
	printf("pic:\r\nw:%d\r\nh:%d\r\nbpp:%d\r\noffset:%d\r\nchar:%d\r\n", ciWidth, ciHeight, ciBitCount, (int)chartolong(FileHead.cfoffBits, 4),BytesPerLine);

	line_x = 0;
	line_y = 0;

	while (!feof(fp))//循环读取文件数据直到文件结尾
	{
		PIXEL pix;
		unsigned  int tmp=0xffffffff;

		/*(1)读取颜色值(本程序图片是24bpp，所以每次读3字节)*/
		rc = fread((char *)&pix, ciBitCount/8, 1, fp);
		if (rc != 1 )    break;

		/*(2)计算图片在framebuff 中的起始地址*/
		location = (line_x+x) * (mydata.bpp/8) + (y+ciHeight - line_y - 1) * mydata.screen_wide * (mydata.bpp/8);

		/*(3)颜色组合成一个数据*/
		tmp = pix.red  <<16  | pix.green << 8 | pix.blue<<0;
		
		/*(4)在虚拟内存填充该像素点的颜色*/
		*((unsigned  int*)(mydata.fbp + location)) = tmp;

		/*(5)设置下一个点*/
		line_x++;
		if (line_x == ciWidth )
		{
			line_x = 0;
			line_y++;

			if (line_y==ciHeight-1)
			{
				break;
			}
		}
	}
	
	fclose( fp );
	return( 0 );
}


void Show_point(unsigned short x, unsigned short y, unsigned int c)
{
    unsigned int location;
	if(c==NONE)
	{
		return ;
	}
    //每个像素点的位数/8=每个像素占用的字节数
    location = x * (mydata.vinfo.bits_per_pixel / 8) + y  *  mydata.finfo.line_length;

	/*直接赋值来改变屏幕上某点的颜色
	    注明：这几个赋值是针对每像素四
	    字节来设置的，如果针对每像素2 
	    字节,比如RGB565，则需要进行转化*/
	
    *(mydata.fbp + location)     = c     & 0xff;    /* 蓝色的色深 */  
    *(mydata.fbp + location + 1) = c >> 8  & 0xff;  /* 绿色的色深*/ 
    *(mydata.fbp + location + 2) = c >> 16 & 0xff;  /* 红色的色深*/
    *(mydata.fbp + location + 3) = c >> 24 & 0xff;  /* 是否透明*/
}

void LCD_Clear(unsigned int color)
{
	unsigned short x,y;
	for(x=0;x<800;x++)
	{
		for(y=0;y<480;y++)
		{
			Show_point(x,y,color);
		}
	}
} 
unsigned char Num_to_char(unsigned int num)
{
	unsigned char rev=0;
	switch(num)
	{
		case 0:	  rev='0'; break;
		case 1:	  rev='1'; break;
		case 2:	  rev='2'; break;
		case 3:	  rev='3'; break;
		case 4:	  rev='4'; break;
		case 5:	  rev='5'; break;
		case 6:	  rev='6'; break;
		case 7:	  rev='7'; break;
		case 8:	  rev='8'; break;
		case 9:	  rev='9'; break;
		default: rev='X'; break;
	}
	return rev;
}

unsigned int Ci_fang(unsigned int x)
{
	unsigned int i=0,y=1;
	for(i=0;i<x;i++)
	{
		y*=10;
	}
	return y;
}

void Read_from_HZK(const unsigned char *s, char* const chs,unsigned char width,unsigned char high)
{
    FILE *fp;
    unsigned long offset;
	unsigned char ZK[10]="HZK";
	unsigned char ch;
	ZK[3]=Num_to_char(width/10%10);
	ZK[4]=Num_to_char(width%10);
    //根据内码找出汉字在HZK16中的偏移位置
    offset = ((s[0] - 0xa1) * 94 + (s[1] - 0xa1)) * width*high/8;

	//打开字库文件
    if((fp = fopen(ZK, "r")) == NULL)
    {
    	printf("字库打开失败!\r\n");
        return;                                 
    }
	//文件指针偏移到要找的汉字处
    fseek(fp, offset, SEEK_SET);  
	
	//读取该汉字的字模
    fread(chs, width*high/8, 1, fp);                      
    fclose(fp);
}
void Read_from_ZFK(const unsigned char *s, char* const chs,unsigned char width,unsigned char high)
{
	int i=0,j=0;
    for (i=0 ;i < ASCII_NUM_use();i++)
	{
		if (*s == use_zf_index[i])
		{
			break;
		}
	}
	if(i==ASCII_NUM_use())
	{
		printf("字符库中无此字符!\n");
		return ;
	}
	for(j=0;j<width*high/8;j++)
	{
		chs[j]=use_zf[(width*high/8)*i+j];
	}
}


void Show_ascii_8x16(int x, int y,unsigned int backcolor,unsigned int forecolor,unsigned char ch)
{

    unsigned char *dots = (unsigned char *)&fontdata_8x16[ch * 16];
    int i, j;  
    for (i = 0; i < 16; i++) 
	{ 
        for (j = 7; j >= 0; j--) 
		{
            if (dots[i] & (1 << j)) 
			{
                Show_point(x + 7 - j, y, forecolor);
            }
            else 
			{
                Show_point(x + 7 - j, y, backcolor);
            }
        }
		y++;
    }
}

void Show_chinese(unsigned int x, unsigned int y, unsigned int bc, unsigned int fc,  const unsigned char * chs,unsigned char width,unsigned char high)
{
    int i, j;
    char data[1000];
	if(*chs>0xa0)
  	  Read_from_HZK(chs, data,width,high);      //去字库中读取汉字字模
   	else
	  Read_from_ZFK(chs,data,width,high);
  
    for (i = 0; i < width*high/8; i++)         //显示32个点
	{	
        if (i % (width/8) == 0 && i!=0)
            y++;                     //每行两字节,16X16点阵   
        for (j = 7; j >= 0; j--) 
		{
            if (data[i] & (0x1 << j))//描绘前景色 
			{
                Show_point(x + ( 7 - j) + (i % (width/8)) * 8, y, fc); //由高到低,
            } 
			else                     //描绘背景色;
			{               
                Show_point(x + ( 7 - j) + (i % (width/8)) * 8, y, bc);
            }
        }
    }
}
void Show_str(int x, int y,unsigned int backcolor,unsigned int forecolor,const unsigned char *str,unsigned char width,unsigned char high)
{
    const unsigned char *ptr_hz;
	unsigned char i=0;
    ptr_hz = str;

    /*显示字符串*/
    while(*ptr_hz != '\0') 
	{
        /*判断是否是字符(字符的ASCII范围为0-127)*/
        if (*ptr_hz<128) 
		{
			if(width/2==8)
			{
				Show_ascii_8x16(x, y, backcolor,forecolor , *ptr_hz);
	            x += 8;
			}
			else
			{
				Show_chinese(x,y,backcolor,forecolor,ptr_hz,width/2,high);
				x+=width/2;
			}
            ptr_hz++;
            
        }
        /*显示汉字*/
        else 
		{    
        	Show_chinese(x, y, backcolor,forecolor,ptr_hz,width,high);
            x      += width;
            ptr_hz += 2;    
        }
		if(x>=800-width)
		{
			x=0;
			y+=high;
			if(y>=480-high)
				break;
		}
    }

}



void Show_num(int x, int y,unsigned int backcolor,unsigned int forecolor,int num , unsigned char len,unsigned char width,unsigned char high)
{
	unsigned char i=0,down=0;
	unsigned char str[20]="\0";
	if(num<0)
	{
		str[down++]='-';
		num=-num;
	}
	for(i=len;i>0;i--)
	{
		str[down++]=Num_to_char((num/Ci_fang(i-1))%10);
	}
	printf("num = %s \n",str);
	Show_str( x,y,backcolor,forecolor,str,width,high);
}

/**************************************************************************
***** 函数名：   Paint_Bmp()
***** 功能：     显示指定大小图片
***** 参数：     x0 开始位置，y0开始位置  ，high高度，width 宽度 ，bmp 图片数据数组
***** 返回值：	 无
****************************************************************************/
void Paint_Bmp(int x0,int y0,int width,int high,const unsigned char bmp[])
{
	int x,y;
	u32 c;
	int p = 0;
	
    for( y = y0 ; y < (high+y0) ; y++ )
    {
    	for( x = x0 ; x < (width+x0) ; x++ )
    	{
    		c = bmp[p+1] | (bmp[p]<<8) | bmp[p+2]<<16 | (bmp[p+3]<<24) ;
			if ( ( (x) < LCD_WIDTH) && ( (y) < LCD_HEIGHT) )
			Show_point(x,y,c);  
    		p = p + 4 ;
    	}
    }
}


