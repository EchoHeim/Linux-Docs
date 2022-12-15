#define WHITE 0xffffff

#define FB_NAME "/dev/fb0"        //�򿪵�֡�����豸��

typedef struct
{
	unsigned char *fbp;              	//�ļ�ӳ��������ַָ��
	long screensize;                 	//ÿ֡ͼ��Ĵ�С(�ֽ�)
	struct fb_var_screeninfo vinfo;  	//�򿪵�֡�����豸�Ŀɱ����
	struct fb_fix_screeninfo finfo;  	//�򿪵�֡�����豸�Ĳ��ɱ����
	int fp;                         	//�򿪵��ļ�������
	int bpp;                        //ɫ��
	int screen_high;               //��Ļ��                     
	int screen_wide;               //��Ļ��
}screen_data;

typedef struct		/* �ļ�ͷ�ṹ 14byte  */ 
{
	char cfType[2];         /* �ļ�����(bmpͼƬ), ����Ϊ "BM" (0x4D42)*/
	char cfSize[4];         /* �ļ���С(�ֽ�) */
	char cfReserved[4];     /* ����, ����Ϊ 0 */
	char cfoffBits[4];      /* λͼ����������ļ�ͷ��ƫ����(�ֽ�)*/
}__attribute__((packed)) BITMAPFILEHEADER;       

typedef struct		/* λͼ��Ϣͷ�ṹ40byte */
{
	char ciSize[4];         	/* size of BITMAPINFOHEADER */
	char ciWidth[4];       		/* λͼ���(����) */
	char ciHeight[4];       	/* λͼ�߶�(����) */
	char ciPlanes[2];       	/* Ŀ���豸��λƽ����, ������Ϊ1 */
	char ciBitCount[2];     	/* ÿ�����ص�λ��, 1,4,8��24 */
	char ciCompress[4];     	/* λͼ���е�ѹ������,0=��ѹ�� */
	char ciSizeImage[4];    	/* ͼ���С(�ֽ�) */
	char ciXPelsPerMeter[4];	/* Ŀ���豸ˮƽÿ�����ظ��� */
	char ciYPelsPerMeter[4];	/* Ŀ���豸��ֱÿ�����ظ��� */
	char ciClrUsed[4];      	/* λͼʵ��ʹ�õ���ɫ�����ɫ�� */
	char ciClrImportant[4]; 	/* ��Ҫ��ɫ�����ĸ��� */
}__attribute__((packed)) BITMAPINFOHEADER;

typedef struct		//λͼ����ɫ�ṹ��(888)
{
	unsigned short blue:8;
	unsigned short green:8;
	unsigned short red:8;
}__attribute__((packed)) PIXEL;

