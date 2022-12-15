#define WHITE 0xffffff

#define FB_NAME "/dev/fb0"        //打开的帧缓冲设备名

typedef struct
{
	unsigned char *fbp;              	//文件映射的虚拟地址指针
	long screensize;                 	//每帧图像的大小(字节)
	struct fb_var_screeninfo vinfo;  	//打开的帧缓冲设备的可变参数
	struct fb_fix_screeninfo finfo;  	//打开的帧缓冲设备的不可变参数
	int fp;                         	//打开的文件描述符
	int bpp;                        //色深
	int screen_high;               //屏幕高                     
	int screen_wide;               //屏幕宽
}screen_data;

typedef struct		/* 文件头结构 14byte  */ 
{
	char cfType[2];         /* 文件类型(bmp图片), 必须为 "BM" (0x4D42)*/
	char cfSize[4];         /* 文件大小(字节) */
	char cfReserved[4];     /* 保留, 必须为 0 */
	char cfoffBits[4];      /* 位图阵列相对于文件头的偏移量(字节)*/
}__attribute__((packed)) BITMAPFILEHEADER;       

typedef struct		/* 位图信息头结构40byte */
{
	char ciSize[4];         	/* size of BITMAPINFOHEADER */
	char ciWidth[4];       		/* 位图宽度(像素) */
	char ciHeight[4];       	/* 位图高度(像素) */
	char ciPlanes[2];       	/* 目标设备的位平面数, 必须置为1 */
	char ciBitCount[2];     	/* 每个像素的位数, 1,4,8或24 */
	char ciCompress[4];     	/* 位图阵列的压缩方法,0=不压缩 */
	char ciSizeImage[4];    	/* 图像大小(字节) */
	char ciXPelsPerMeter[4];	/* 目标设备水平每米像素个数 */
	char ciYPelsPerMeter[4];	/* 目标设备垂直每米像素个数 */
	char ciClrUsed[4];      	/* 位图实际使用的颜色表的颜色数 */
	char ciClrImportant[4]; 	/* 重要颜色索引的个数 */
}__attribute__((packed)) BITMAPINFOHEADER;

typedef struct		//位图的颜色结构体(888)
{
	unsigned short blue:8;
	unsigned short green:8;
	unsigned short red:8;
}__attribute__((packed)) PIXEL;

