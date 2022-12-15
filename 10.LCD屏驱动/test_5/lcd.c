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

#define FB_NAME     "/dev/fb0"   //�򿪵�֡�����豸��

extern unsigned char use_hz_index[];
extern unsigned char use_zf_index[];
extern unsigned char use_hz[];
extern unsigned char use_zf[];


extern const unsigned char fontdata_8x16[];

/* �ļ�ͷ�ṹ 14byte  */ 
typedef struct
{
	char cfType[2];         /* �ļ�����, ����Ϊ "BM" (0x4D42)*/
	char cfSize[4];         /* �ļ��Ĵ�С(�ֽ�) */
	char cfReserved[4];     /* ����, ����Ϊ 0 */
	char cfoffBits[4];      /* λͼ����������ļ�ͷ��ƫ����(�ֽ�)*/
}__attribute__((packed)) BITMAPFILEHEADER;       

/* λͼ��Ϣͷ�ṹ40byte */
typedef struct
{
	char ciSize[4];         /* size of BITMAPINFOHEADER */
	char ciWidth[4];        /* λͼ���(����) */
	char ciHeight[4];       /* λͼ�߶�(����) */
	char ciPlanes[2];       /* Ŀ���豸��λƽ����, ������Ϊ1 */
	char ciBitCount[2];     /* ÿ�����ص�λ��, 1,4,8��24 */
	char ciCompress[4];     /* λͼ���е�ѹ������,0=��ѹ�� */
	char ciSizeImage[4];    /* ͼ���С(�ֽ�) */
	char ciXPelsPerMeter[4];/* Ŀ���豸ˮƽÿ�����ظ��� */
	char ciYPelsPerMeter[4];/* Ŀ���豸��ֱÿ�����ظ��� */
	char ciClrUsed[4];      /* λͼʵ��ʹ�õ���ɫ�����ɫ�� */
	char ciClrImportant[4]; /* ��Ҫ��ɫ�����ĸ��� */
}__attribute__((packed)) BITMAPINFOHEADER;       


//λͼ����ɫ�ṹ��(888)
typedef struct
{
	unsigned short blue:8;
	unsigned short green:8;
	unsigned short red:	8;
}__attribute__((packed)) PIXEL;


typedef struct
{
	unsigned char *fbp;              //�ļ�ӳ��������ַָ��
	long screensize;                 //ÿ֡ͼ��Ĵ�С(�ֽ�)
	struct fb_var_screeninfo vinfo;  //�򿪵�֡�����豸�Ŀɱ����
	struct fb_fix_screeninfo finfo;  //�򿪵�֡�����豸�Ĳ��ɱ����
	int  fp;                         //�򿪵��ļ�������
	int bpp;                         //ɫ��
	int screen_high;                 //��Ļ��                     
	int screen_wide;                 //��Ļ��
}screen_data;


screen_data mydata;                   //����һ��ȫ�ֱ������ȫ������
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
    // ���㵥֡����ռ�����ֽ�
    mydata.screensize  = mydata.vinfo.xres * mydata.vinfo.yres * mydata.vinfo.bits_per_pixel / 8;  
	mydata.screen_wide = mydata.vinfo.xres;
	mydata.screen_high = mydata.vinfo.yres;
	mydata.bpp         = mydata.vinfo.bits_per_pixel;
    //��fp��ָ���ļ��дӿ�ʼ��screensize��С
    //�����ݸ�ӳ��������õ�һ��ָ�����ռ�
    //��ָ��
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
    munmap (mydata.fbp, mydata.screensize); /*���ӳ��*/
    close (mydata.fp);                      /*�ر��ļ�*/
}



/************************************************************************
 �Ѵ�����ڴ��е��ַ�ƴ��Ϊһ�����������ݷ��ء�
ʵ�������ǵ��������ڴ��д�����ֽ���ʽ��ŵģ�
��0x12345678,��ʵ��0x78,0x56,0x34,0x12�������
************************************************************************/
long chartolong( char * string, int length )
{
	long number;

	if (length <= 4)
	{
		memset( &number, 0x00, sizeof(long) );  //���
		memcpy( &number, string, length );      //���
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

	/* (1)��λͼ�ļ� */
	fp = fopen( bmpfile, "rb" );   //�Զ����Ƶ�ֻ����ʽ���ļ�
	if (fp == NULL)
	{
		printf("open bmpfile fail\r\n");
		return -1;
	}

	/*(2) ��ȡλͼ�ļ�ͷ */
	rc = fread( &FileHead, sizeof(BITMAPFILEHEADER),1, fp);
	if ( rc != 1)
	{
		printf("get FileHead fail\r\n");
		fclose( fp );
		return -2;
	}

	/*(3) �ж�λͼ������ */
	if (memcmp(FileHead.cfType, "BM", 2) != 0)  //�ڴ�Ա�
	{
		printf("picture is not bmp\r\n");
		fclose( fp );
		return -3;
	}

	/* (4)��ȡλͼ��Ϣͷ */
	rc = fread( (char *)&InfoHead, sizeof(BITMAPINFOHEADER),1, fp );
	if ( rc != 1)
	{
		printf("get FileHead fail\r\n");
		fclose( fp );
		return -4;
	}

	ciWidth    = (int) chartolong( InfoHead.ciWidth,    4 );//���ͼƬ��
	ciHeight   = (int) chartolong( InfoHead.ciHeight,   4 );//���ͼƬ��
	ciBitCount = (int) chartolong( InfoHead.ciBitCount, 4 );//���ͼƬɫ��

	/*(5)���ļ�����ƶ����ļ��������� */
	fseek(fp, (int)chartolong(FileHead.cfoffBits, 4), SEEK_SET);

	/*(6)����ÿ���ж��ٸ��ֽ�*/
	BytesPerLine = ciWidth * (ciBitCount / 8);
	printf("pic:\r\nw:%d\r\nh:%d\r\nbpp:%d\r\noffset:%d\r\nchar:%d\r\n", ciWidth, ciHeight, ciBitCount, (int)chartolong(FileHead.cfoffBits, 4),BytesPerLine);

	line_x = 0;
	line_y = 0;

	while (!feof(fp))//ѭ����ȡ�ļ�����ֱ���ļ���β
	{
		PIXEL pix;
		unsigned  int tmp=0xffffffff;

		/*(1)��ȡ��ɫֵ(������ͼƬ��24bpp������ÿ�ζ�3�ֽ�)*/
		rc = fread((char *)&pix, ciBitCount/8, 1, fp);
		if (rc != 1 )    break;

		/*(2)����ͼƬ��framebuff �е���ʼ��ַ*/
		location = (line_x+x) * (mydata.bpp/8) + (y+ciHeight - line_y - 1) * mydata.screen_wide * (mydata.bpp/8);

		/*(3)��ɫ��ϳ�һ������*/
		tmp = pix.red  <<16  | pix.green << 8 | pix.blue<<0;
		
		/*(4)�������ڴ��������ص����ɫ*/
		*((unsigned  int*)(mydata.fbp + location)) = tmp;

		/*(5)������һ����*/
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
    //ÿ�����ص��λ��/8=ÿ������ռ�õ��ֽ���
    location = x * (mydata.vinfo.bits_per_pixel / 8) + y  *  mydata.finfo.line_length;

	/*ֱ�Ӹ�ֵ���ı���Ļ��ĳ�����ɫ
	    ע�����⼸����ֵ�����ÿ������
	    �ֽ������õģ�������ÿ����2 
	    �ֽ�,����RGB565������Ҫ����ת��*/
	
    *(mydata.fbp + location)     = c     & 0xff;    /* ��ɫ��ɫ�� */  
    *(mydata.fbp + location + 1) = c >> 8  & 0xff;  /* ��ɫ��ɫ��*/ 
    *(mydata.fbp + location + 2) = c >> 16 & 0xff;  /* ��ɫ��ɫ��*/
    *(mydata.fbp + location + 3) = c >> 24 & 0xff;  /* �Ƿ�͸��*/
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
    //���������ҳ�������HZK16�е�ƫ��λ��
    offset = ((s[0] - 0xa1) * 94 + (s[1] - 0xa1)) * width*high/8;

	//���ֿ��ļ�
    if((fp = fopen(ZK, "r")) == NULL)
    {
    	printf("�ֿ��ʧ��!\r\n");
        return;                                 
    }
	//�ļ�ָ��ƫ�Ƶ�Ҫ�ҵĺ��ִ�
    fseek(fp, offset, SEEK_SET);  
	
	//��ȡ�ú��ֵ���ģ
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
		printf("�ַ������޴��ַ�!\n");
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
  	  Read_from_HZK(chs, data,width,high);      //ȥ�ֿ��ж�ȡ������ģ
   	else
	  Read_from_ZFK(chs,data,width,high);
  
    for (i = 0; i < width*high/8; i++)         //��ʾ32����
	{	
        if (i % (width/8) == 0 && i!=0)
            y++;                     //ÿ�����ֽ�,16X16����   
        for (j = 7; j >= 0; j--) 
		{
            if (data[i] & (0x1 << j))//���ǰ��ɫ 
			{
                Show_point(x + ( 7 - j) + (i % (width/8)) * 8, y, fc); //�ɸߵ���,
            } 
			else                     //��汳��ɫ;
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

    /*��ʾ�ַ���*/
    while(*ptr_hz != '\0') 
	{
        /*�ж��Ƿ����ַ�(�ַ���ASCII��ΧΪ0-127)*/
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
        /*��ʾ����*/
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
***** ��������   Paint_Bmp()
***** ���ܣ�     ��ʾָ����СͼƬ
***** ������     x0 ��ʼλ�ã�y0��ʼλ��  ��high�߶ȣ�width ��� ��bmp ͼƬ��������
***** ����ֵ��	 ��
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


