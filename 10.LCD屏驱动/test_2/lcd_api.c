#include "includes.h"

extern screen_data mydata;
extern const unsigned char fontdata_8x16[];

BITMAPFILEHEADER FileHead;
BITMAPINFOHEADER InfoHead;

void show_point(unsigned int x, unsigned int y, unsigned int c)
{
    unsigned int location;
    //ÿ�����ص��λ��/8=ÿ������ռ�õ��ֽ���
    location = x * (mydata.vinfo.bits_per_pixel / 8) + y * mydata.finfo.line_length;
	/*ֱ�Ӹ�ֵ���ı���Ļ��ĳ�����ɫ
	    ע�����⼸����ֵ�����ÿ�������ֽ������õģ�������ÿ����2�ֽ�,����RGB565������Ҫ����ת��*/

    *(mydata.fbp + location)     = c     & 0xff;    /* ��ɫ��ɫ�� */  
    *(mydata.fbp + location + 1) = c >> 8  & 0xff;  /* ��ɫ��ɫ��*/ 
    *(mydata.fbp + location + 2) = c >> 16 & 0xff;  /* ��ɫ��ɫ��*/
    *(mydata.fbp + location + 3) = c >> 24 & 0xff;  /* �Ƿ�͸��*/
}

void show_string(int x, int y,unsigned int forecolor,unsigned int backcolor,const unsigned char *str)
{/*��ʾ�ַ���*/
    const unsigned char *ptr_hz;
    ptr_hz = str;

    while(*ptr_hz != '\0') 
	{
        if (*ptr_hz<128)  /*�ж��Ƿ����ַ�(�ַ���ASCII��ΧΪ0-127)*/
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
        else /*��ʾ����*/
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

	/* (1)��λͼ�ļ� */
	fp = fopen( bmpfile, "rb" );   //�Զ����Ƶ�ֻ����ʽ���ļ�
	if (fp == NULL)
	{
		printf("��bmp�ļ�ʧ��!\n");
		return -1;
	}

	/*(2) ��ȡλͼ�ļ�ͷ */
	rc = fread( &FileHead, sizeof(BITMAPFILEHEADER),1, fp);
	if ( rc != 1)
	{
		printf("��ȡ�ļ�ͷʧ��!\r\n");
		fclose( fp );
		return -2;
	}

	/*(3) �ж�λͼ������ */
	if (memcmp(FileHead.cfType, "BM", 2) != 0)  //�ڴ�Ա�
	{
		printf("����:ͼƬ����bmp��ʽ!\r\n");
		fclose( fp );
		return -3;
	}

	/* (4)��ȡλͼ��Ϣͷ */
	rc = fread( (char *)&InfoHead, sizeof(BITMAPINFOHEADER),1, fp );
	if ( rc != 1)
	{
		printf("��ȡ�ļ�ͷʧ��!\r\n");
		fclose( fp );
		return -4;
	}

	ciWidth    = (int) char_to_long( InfoHead.ciWidth,    4 );//���ͼƬ��
	ciHeight   = (int) char_to_long( InfoHead.ciHeight,   4 );//���ͼƬ��
	ciBitCount = (int) char_to_long( InfoHead.ciBitCount, 4 );//���ͼƬɫ��

	/*(5)���ļ�����ƶ����ļ��������� */
	fseek(fp, (int)char_to_long(FileHead.cfoffBits, 4), SEEK_SET);

	/*(6)����ÿ���ж��ٸ��ֽ�*/
	BytesPerLine = ciWidth * (ciBitCount / 8);
	printf("ͼƬ�ֱ���:%d*%d   ����:%d\r\nͼƬ������ƫ����:%d\r\nÿ��������:%d\r\n", ciWidth, ciHeight, ciBitCount, (int)char_to_long(FileHead.cfoffBits, 4),BytesPerLine);

	if(((point_x+ciWidth)>800)||((point_y+ciHeight)>480))	//�ж�ͼƬ��ʾ�Ƿ񳬳���Ļ;
	{
		printf("ͼƬ��ʾ������Ļ��Χ!\n");
		return -1;
	}
	line_x = 0;
	line_y = -point_y;
	
	while (!feof(fp))//ѭ����ȡ�ļ�����ֱ���ļ���β
	{
		PIXEL pix;
		unsigned int tmp=0xffffffff;

		/*(1)��ȡ��ɫֵ(������ͼƬ��24bpp������ÿ�ζ�3�ֽ�)*/
		rc = fread((char *)&pix, ciBitCount/8, 1, fp);
		if (rc != 1 )    break;

		/*(2)����ͼƬ��framebuff �е���ʼ��ַ*/
		location = line_x * (mydata.bpp/8) + (ciHeight - line_y - 1) * mydata.screen_wide * (mydata.bpp/8) + 4*point_x;

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

    offset = ((s[0] - 0xa1) * 94 + (s[1] - 0xa1)) * 32;	//���������ҳ�������HZK16�е�ƫ��λ��

    if((fp = fopen("HZK16", "r")) == NULL)	//���ֿ��ļ�
        return;                                 

    fseek(fp, offset, SEEK_SET);  //�ļ�ָ��ƫ�Ƶ�Ҫ�ҵĺ��ִ�

    fread(chs, 32, 1, fp);        //��ȡ�ú��ֵ���ģ              

    fclose(fp);
}

void show_chinese_16(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc,  const unsigned char * chs)
{
    int i, j;
    char data[32];

    Read_from_HZK16(chs, data);      //ȥ�ֿ��ж�ȡ������ģ
    for (i = 0; i < 32; i++)         //��ʾ32����
	{
        if (i % 2 == 0)  y++;       //ÿ�����ֽ�,16X16����

        for (j = 7; j >= 0; j--) 
		{
            if (data[i] & (0x1 << j)) 
                show_point(x + (7 - j) + (i % 2) * 8, y, fc); //���ǰ��ɫ,�ɸߵ���;
			else                     
                show_point(x + (7 - j) + (i % 2) * 8, y, bc);	//��汳��ɫ;
        }
    }
}

