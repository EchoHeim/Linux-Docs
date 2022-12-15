#include "includes.h"

extern screen_data mydata;
extern const unsigned char fontdata_8x16[];

BITMAPFILEHEADER FileHead;
BITMAPINFOHEADER InfoHead;

void show_point(unsigned int x, unsigned int y, unsigned int c)
{
    unsigned int location;
    //每个像素点的位数/8=每个像素占用的字节数
    location = x * (mydata.vinfo.bits_per_pixel / 8) + y * mydata.finfo.line_length;
	/*直接赋值来改变屏幕上某点的颜色
	    注明：这几个赋值是针对每像素四字节来设置的，如果针对每像素2字节,比如RGB565，则需要进行转化*/

    *(mydata.fbp + location)     = c     & 0xff;    /* 蓝色的色深 */  
    *(mydata.fbp + location + 1) = c >> 8  & 0xff;  /* 绿色的色深*/ 
    *(mydata.fbp + location + 2) = c >> 16 & 0xff;  /* 红色的色深*/
    *(mydata.fbp + location + 3) = c >> 24 & 0xff;  /* 是否透明*/
}

void show_string(int x, int y,unsigned int forecolor,unsigned int backcolor,const unsigned char *str)
{/*显示字符串*/
    const unsigned char *ptr_hz;
    ptr_hz = str;

    while(*ptr_hz != '\0') 
	{
        if (*ptr_hz<128)  /*判断是否是字符(字符的ASCII范围为0-127)*/
		{
			show_char(x, y, forecolor, backcolor, *ptr_hz);
            x += 8;
			if(x>784)
			{
				x = 0;
				y += 16;
			}
            ptr_hz++;
        }
        else /*显示汉字*/
		{    
        	show_chinese_16(x, y, forecolor, backcolor,ptr_hz);
            x += 16;
			if(x>784)
			{
				x = 0;
				y += 16;
			}
            ptr_hz += 2;    
        }
    }
}

int show_bmp( int point_x, int point_y, char *bmpfile )
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
		printf("打开bmp文件失败!\n");
		return -1;
	}

	/*(2) 读取位图文件头 */
	rc = fread( &FileHead, sizeof(BITMAPFILEHEADER),1, fp);
	if ( rc != 1)
	{
		printf("获取文件头失败!\r\n");
		fclose( fp );
		return -2;
	}

	/*(3) 判断位图的类型 */
	if (memcmp(FileHead.cfType, "BM", 2) != 0)  //内存对比
	{
		printf("错误:图片不是bmp格式!\r\n");
		fclose( fp );
		return -3;
	}

	/* (4)读取位图信息头 */
	rc = fread( (char *)&InfoHead, sizeof(BITMAPINFOHEADER),1, fp );
	if ( rc != 1)
	{
		printf("获取文件头失败!\r\n");
		fclose( fp );
		return -4;
	}

	ciWidth    = (int) char_to_long( InfoHead.ciWidth,    4 );//获得图片宽
	ciHeight   = (int) char_to_long( InfoHead.ciHeight,   4 );//获得图片高
	ciBitCount = (int) char_to_long( InfoHead.ciBitCount, 4 );//获得图片色深

	/*(5)将文件光标移动到文件的数据区 */
	fseek(fp, (int)char_to_long(FileHead.cfoffBits, 4), SEEK_SET);

	/*(6)计算每行有多少个字节*/
	BytesPerLine = ciWidth * (ciBitCount / 8);
	printf("图片分辨率:%d*%d   像素:%d\r\n图片数据区偏移量:%d\r\n每行像素数:%d\r\n", ciWidth, ciHeight, ciBitCount, (int)char_to_long(FileHead.cfoffBits, 4),BytesPerLine);

	if(((point_x+ciWidth)>800)||((point_y+ciHeight)>480))	//判断图片显示是否超出屏幕;
	{
		printf("图片显示超出屏幕范围!\n");
		return -1;
	}
	line_x = 0;
	line_y = -point_y;
	
	while (!feof(fp))//循环读取文件数据直到文件结尾
	{
		PIXEL pix;
		unsigned int tmp=0xffffffff;

		/*(1)读取颜色值(本程序图片是24bpp，所以每次读3字节)*/
		rc = fread((char *)&pix, ciBitCount/8, 1, fp);
		if (rc != 1 )    break;

		/*(2)计算图片在framebuff 中的起始地址*/
		location = line_x * (mydata.bpp/8) + (ciHeight - line_y - 1) * mydata.screen_wide * (mydata.bpp/8) + 4*point_x;

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
				break;
		}
	}
	fclose( fp );
	return( 0 );
}

void show_char(int x, int y,unsigned int forecolor,unsigned int backcolor,unsigned char ch)
{
    unsigned char *dots = (unsigned char *)&fontdata_8x16[ch * 16];
    int i, j;  

    for (i = 0; i < 16; i++) 
	{ 
        for (j = 7; j >= 0; j--) 
		{
            if (dots[i] & (1 << j)) 
                show_point(x + 7 - j, y, forecolor);
            else 
                show_point(x + 7 - j, y, backcolor);
        }
		y++;
    }
}

void Read_from_HZK16(const unsigned char *s, char* const chs)
{
    FILE *fp;
    unsigned long offset;

    offset = ((s[0] - 0xa1) * 94 + (s[1] - 0xa1)) * 32;	//根据内码找出汉字在HZK16中的偏移位置

    if((fp = fopen("HZK16", "r")) == NULL)	//打开字库文件
        return;                                 

    fseek(fp, offset, SEEK_SET);  //文件指针偏移到要找的汉字处

    fread(chs, 32, 1, fp);        //读取该汉字的字模              

    fclose(fp);
}

void show_chinese_16(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc,  const unsigned char * chs)
{
    int i, j;
    char data[32];

    Read_from_HZK16(chs, data);      //去字库中读取汉字字模
    for (i = 0; i < 32; i++)         //显示32个点
	{
        if (i % 2 == 0)  y++;       //每行两字节,16X16点阵

        for (j = 7; j >= 0; j--) 
		{
            if (data[i] & (0x1 << j)) 
                show_point(x + (7 - j) + (i % 2) * 8, y, fc); //描绘前景色,由高到低;
			else                     
                show_point(x + (7 - j) + (i % 2) * 8, y, bc);	//描绘背景色;
        }
    }
}

