#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/videodev2.h>
#include <linux/fb.h>
#include <stdlib.h>

#include <string.h>

#include <sys/time.h>
#include "tslib.h"

#include<pthread.h>
#include<assert.h>
//#define Debug
static int SpFmt[] = {V4L2_PIX_FMT_YUYV, V4L2_PIX_FMT_MJPEG, V4L2_PIX_FMT_RGB565};
static char *ShowFmt[] = {"YUV", "MJPEG", "RGB565"};

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/* 条件变量 */
static pthread_cond_t cond   = PTHREAD_COND_INITIALIZER;

#ifdef Debug
#define debug printf
#else
#define debug //
#endif

/* 图片的象素数据 */
typedef struct PixelDatas {
	int iWidth;   /* 宽度: 一行有多少个象素 */
	int iHeight;  /* 高度: 一列有多少个象素 */
	int iBpp;     /* 一个象素用多少位来表示 */
	int iLineBytes;  /* 一行数据有多少字节 */
	int iTotalBytes; /* 所有字节数 */ 
	unsigned char *aucPixelDatas;  /* 象素数据存储的地方 */
}T_PixelDatas, *PT_PixelDatas;



//*********************ts**********************//
struct tsdev *ts;
//*********************ts**********************//

//**********************lcd********************//
unsigned char *fbmem;
struct fb_var_screeninfo var;	/* Current var */
struct fb_fix_screeninfo fix;	/* Current fix */
static int screen_size;
static int fd_fb;
//**********************lcd********************//


//**********************camera********************//
T_PixelDatas tVideoZoom;
struct v4l2_buffer tV4l2Buf;
static int iFd;
T_PixelDatas ptVideoBufOut;
static int ListNum;
T_PixelDatas ptVideoBufIn;
unsigned char* pucVideBuf[4];
//**********************camara********************//


#pragma pack(push) /* 将当前pack设置压栈保存 */
#pragma pack(1)    /* 必须在结构体定义之前使用,这是为了让结构体中各成员按1字节对齐 */

typedef struct tagBITMAPFILEHEADER { /* bmfh */
	unsigned short bfType; 
	unsigned long  bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned long  bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER { /* bmih */
	unsigned long  biSize;
	unsigned long  biWidth;
	unsigned long  biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned long  biCompression;
	unsigned long  biSizeImage;
	unsigned long  biXPelsPerMeter;
	unsigned long  biYPelsPerMeter;
	unsigned long  biClrUsed;
	unsigned long  biClrImportant;
} BITMAPINFOHEADER;

#pragma pack(pop) /* 恢复先前的pack设置 */

static int PicZoom(PT_PixelDatas ptOriginPic, PT_PixelDatas ptZoomPic);
int IsTimeOver500MS(struct timeval *PerTime,struct timeval	*CurTime)
{
	int PerMS;
	int CurMS;
	int ret;
	PerMS = PerTime->tv_sec * 1000 + PerTime->tv_usec /1000;
	CurMS = CurTime->tv_sec * 1000 + CurTime->tv_usec /1000;
	
	ret = CurMS - (PerMS + 500);
	if(ret > 0)
		return 1;
	else
		return 0;
}

void bmp_init(unsigned char *filemem)
{
	BITMAPFILEHEADER *ptBITMAPFILEHEADER;
	BITMAPINFOHEADER *ptBITMAPINFOHEADER;

	/* 获取文件信息头 */
    ptBITMAPFILEHEADER = (BITMAPFILEHEADER *)filemem;
	
   	ptBITMAPFILEHEADER->bfType = 0x4D42;    
    ptBITMAPFILEHEADER->bfSize = 0x25836;   
    ptBITMAPFILEHEADER->bfReserved1 = 0x0;   
    ptBITMAPFILEHEADER->bfReserved2 = 0x0;
    ptBITMAPFILEHEADER->bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
 
    /* 获取位图信息头 */
	ptBITMAPINFOHEADER = (BITMAPINFOHEADER *)(filemem + sizeof(BITMAPFILEHEADER));
	
    ptBITMAPINFOHEADER->biSize = 0x28;
    ptBITMAPINFOHEADER->biWidth = tVideoZoom.iWidth;
    ptBITMAPINFOHEADER->biHeight = tVideoZoom.iHeight;
    ptBITMAPINFOHEADER->biPlanes = 0x01;
    ptBITMAPINFOHEADER->biBitCount = 32;
    ptBITMAPINFOHEADER->biCompression = 0;
    ptBITMAPINFOHEADER->biSizeImage = ptBITMAPFILEHEADER->bfOffBits+tVideoZoom.iTotalBytes;
    ptBITMAPINFOHEADER->biXPelsPerMeter = 0x60;
    ptBITMAPINFOHEADER->biYPelsPerMeter = 0x60;
    ptBITMAPINFOHEADER->biClrUsed = 0;
    ptBITMAPINFOHEADER->biClrImportant = 0;
     
}


void *get_bmp(void *arg)
{

	BITMAPFILEHEADER *ptBITMAPFILEHEADER;
	BITMAPINFOHEADER *ptBITMAPINFOHEADER;

	//static int count=0;
	
	unsigned char *filemem=NULL;
	unsigned char *mov=NULL;
	unsigned char *pucSrc;
	unsigned char *pucdest=NULL;
	unsigned char *file_name="test1.bmp";  //为什么不能用指针
	unsigned int *pucdest1,*pucSrc1;
	unsigned int *dest = NULL;
	int fd;
	int j,i;
	int lenth;
	int color;
	unsigned char r,g,b,c;
	//sprintf(file_name,"%d.bmp",count);
	
	//count++;
	
	fd=open(file_name,O_RDWR|O_CREAT,0777);
	pthread_mutex_lock(&mutex);
	lenth=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+tVideoZoom.iTotalBytes;
	filemem=(unsigned char *)malloc(lenth);
	//使用mmap可能会出错，因为打开的为空文件
	memset(filemem,0,lenth);
	printf("filemem=%p\n",filemem);
	
	/* 获取图片起始地址 */
  	mov=filemem;
	
	bmp_init(mov);
	
	//photo_par[i].iLineWidthReal = photo_par[i].iWidth * photo_par[i].iBMPBpp / 8;
	//photo_par[i].iLineWidthAlign = (photo_par[i].iLineWidthReal + 3) & ~0x3;   /* 向4取整 */

	/* 实际图像存储的位置 */
	pucdest = mov+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	
	pucdest= pucdest +(tVideoZoom.iHeight-1)*tVideoZoom.iWidth*4;
	pucSrc=tVideoZoom.aucPixelDatas;

	
	pucdest1=(unsigned int *)pucdest;
	
	for(j=0;j<tVideoZoom.iHeight;j++)
		{
			pucdest1=(unsigned int *)pucdest-j*tVideoZoom.iWidth;
			//每次定位到行的开头时，不要重复减，
			//如pucdest1=(unsigned int *)pucdest1-j*tVideoZoom.iWidth;

			
			//pucdest1=(unsigned int *)(pucdest-j*tVideoZoom.iWidth*4);  最好用这种方法
			
			for(i=0;i<tVideoZoom.iWidth;i++)
				{
					
					c=*pucSrc++;
					r=*pucSrc++;
					g=*pucSrc++;
					b=*pucSrc++;
					
					color=(c>>0)|(b>>24)|(g<<16)|(r<<8);
					
					dest = pucdest1 + i;
					
					*dest = color;
			
				}
			
			
		}
	pthread_mutex_unlock(&mutex);
	printf("************%d %d",i,j);
	write(fd, filemem,lenth);
	printf("*******************get_bmp******************\n");
	close(fd);
	return 0;
}

void *zoom_size(void *arg)
{

	struct ts_sample samp;
	int ret;
	static int mul=1;
	//int rec_TotalBytes;
	unsigned char *mm;
	static struct timeval PerTime={0,0};
	
	while(1)
		{
			//pthread_mutex_lock(&mutex);
			//pthread_cond_wait(&cond,&mutex); //睡眠
			ret = ts_read(ts, &samp, 1);
	
			if(IsTimeOver500MS(&PerTime,&samp.tv))
			{
				PerTime = samp.tv;
				if(samp.pressure)
				{
						printf("pthread success!\n");
				
						
						mul=mul<<1;
						
						if(mul==16)
						{
							mul=1;
						}
						printf("******mul=%d\n",mul);
						debug("zoom:\n");
						debug("====================1 fail\n");
						debug("====================malloc =%p\n",tVideoZoom.aucPixelDatas);
						
						tVideoZoom.aucPixelDatas = NULL;
						debug("====================fbmem =%p\n",fbmem);
						debug("====================2 fail\n");	
						
						debug("====================3 fail\n");
						tVideoZoom.iBpp = ptVideoBufOut.iBpp;
						tVideoZoom.iWidth = 800/mul;
						tVideoZoom.iHeight = 480/mul;
						tVideoZoom.iLineBytes = tVideoZoom.iWidth * tVideoZoom.iBpp/8;
						tVideoZoom.iTotalBytes = tVideoZoom.iLineBytes*tVideoZoom.iHeight;
					
						debug("====================3 fail\n");
						pthread_mutex_lock(&mutex);
						debug("====================777777 fail\n");
						free(tVideoZoom.aucPixelDatas);
						tVideoZoom.aucPixelDatas = (unsigned char *)malloc(tVideoZoom.iTotalBytes);
							if(NULL == tVideoZoom.aucPixelDatas)
							{
								printf("====================malloc fail\n");
								
							}
						memset(fbmem,0,var.xres*var.yres*4);	
						debug("====================malloc= %p\n",tVideoZoom.aucPixelDatas);
						pthread_mutex_unlock(&mutex);

					
			
				}
			}
			//rec_TotalBytes=tVideoZoom.iTotalBytes;
			//sleep(1);
			//pthread_mutex_unlock(&mutex);
		}
}
int isSpFmt(int FmtPix)
{
	int i=0;
	for(i=0;i<sizeof(SpFmt)/sizeof(SpFmt[0]);i++)
	{
		if(SpFmt[i] == FmtPix)
		{
			debug("Fomat is :%s\n",ShowFmt[i]);
			return 0;
		}
	}
	return -1;
}

static unsigned int
Pyuv422torgb32(unsigned char * input_ptr,unsigned char *output_ptr, unsigned int image_width, unsigned int image_height)
{
	unsigned int i, size;
	unsigned char Y, Y1, U, V;
	unsigned char *buff = input_ptr;
	unsigned int *output_pt = (unsigned int *)output_ptr;
	unsigned int x;
	unsigned int y;
    unsigned int r, g, b;
    unsigned int color;
    
	size = image_width * image_height /2;
	debug("size ==%d\n",size);
	for (i = size; i >0; i--) {
		/* bgr instead rgb ?? */
		Y = buff[0] ;
		U = buff[1] ;
		Y1 = buff[2];
		V = buff[3];
		buff += 4;
		r = R_FROMYV(Y,V);
		g = G_FROMYUV(Y,U,V); //b
		b = B_FROMYU(Y,U); //v
        
     
       
        color = (r << 16) | (g << 8) | (b<<0);
        *output_pt++ = color; 
		
		r = R_FROMYV(Y1,V);
		g = G_FROMYUV(Y1,U,V); //b
		b = B_FROMYU(Y1,U); //v
     
		 color = (r << 16) | (g << 8) | b;
        *output_pt++ = color;
	}
		

	return 0;
} 

/* 参考luvcview */

static int Yuv2RgbConvert(PT_PixelDatas ptVideoBufIn, PT_PixelDatas ptVideoBufOut)
{
	PT_PixelDatas ptPixelDatasIn  = ptVideoBufIn;
	PT_PixelDatas ptPixelDatasOut = ptVideoBufOut;

	ptPixelDatasOut->iWidth  = ptPixelDatasIn->iWidth;
	ptPixelDatasOut->iHeight = ptPixelDatasIn->iHeight;

	ptPixelDatasOut->iBpp = 32;
	ptPixelDatasOut->iLineBytes  = ptPixelDatasOut->iWidth * ptPixelDatasOut->iBpp / 8;
	ptPixelDatasOut->iTotalBytes = ptPixelDatasOut->iLineBytes * ptPixelDatasOut->iHeight;
	//debug("ptPixelDatasOut->iTotalBytes=%d\n",ptPixelDatasOut->iTotalBytes);

	if (!ptPixelDatasOut->aucPixelDatas)
	{
		ptPixelDatasOut->aucPixelDatas = (unsigned char *)malloc(ptPixelDatasOut->iTotalBytes);
	}
	
	Pyuv422torgb32(ptPixelDatasIn->aucPixelDatas, ptPixelDatasOut->aucPixelDatas, ptPixelDatasOut->iWidth, ptPixelDatasOut->iHeight);
	
	return 0;
 
}

int to_senter_show(T_PixelDatas tVideoZoom,unsigned char *fbmem2,unsigned char *re_fbmem1)
{
	int x,y;
	int x1,y1;
	unsigned int *fbmem1=(unsigned int *)fbmem2;   
	unsigned int *re_fbmem=(unsigned int *)re_fbmem1;
	x1=(800-tVideoZoom.iWidth)>>1;
	y1=(480-tVideoZoom.iHeight)>>1;
	fbmem1+=y1*800;
	debug("************%d %d\n",tVideoZoom.iHeight,y1);
	for (y =0; y < tVideoZoom.iHeight; y++)
		{		
		for(x=0;x<800;x++)
			{
				
				if((x>=x1)&&(x<x1+tVideoZoom.iWidth))
					{
						*fbmem1++=*re_fbmem++;
					}
				else
					{
						*fbmem1++=0;
					}
	
			}
		
		}
		
		return 0;
}
static int lcd_init()
{
	/*********************************************************************/
/* 打开fb设备:lcd设备 */
	
	
	
	unsigned int line_width;
	unsigned int pixel_width;

	
	
	fd_fb = open("/dev/fb0", O_RDWR);
	if (fd_fb < 0)
	{
		debug("can't open /dev/fb0\n");
		return 0;
	}
	/* 通过ioctl获取可变参数:var */
	if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &var))
	{
		debug("can't get var\n");
		return -1;
	}
	debug("x = %d\n",var.xres);
	debug("y = %d\n",var.yres);
	debug("Bpp = %d\n",var.bits_per_pixel);
	/* 通过ioctl获取可变参数:fix */
	if (ioctl(fd_fb, FBIOGET_FSCREENINFO, &fix))
	{
		debug("can't get fix\n");
		return -1;
	}
	debug("size : %d\n",fix.smem_len);
	/* 行宽 */
	line_width  = var.xres * var.bits_per_pixel / 8;
	/* 一个像素占了几个字节 */
	pixel_width = var.bits_per_pixel / 8;
	/* 显存大小 */
	screen_size = var.xres * var.yres * var.bits_per_pixel / 8;
	/* 映射显存 */
	
	fbmem = (unsigned char *)mmap(NULL ,screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
	if (fbmem == (unsigned char *)-1)
	{
		debug("can't mmap\n");
		return -1;
	}
/*********************************************************************/	
	return 0;
}

static int camera_init(void)
{
	int i=0;
	int cnt=0;
	int error;

	int iType = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	struct v4l2_capability tV4L2Cap;
	struct v4l2_fmtdesc tV4L2FmtDesc;

	struct v4l2_format  tV4l2Fmt;
	
	struct v4l2_requestbuffers tV4l2ReqBuffs;
	
	/* 1、打开视频设备 */
	iFd = open("/dev/video15",O_RDWR);
	if(iFd < 0)
	{
		debug("can't open /dev/video\n");
		return 0;
	}
	
	/* 2、VIDIOC_QUERYCAP 确定它是否视频捕捉设备,支持哪种接口(streaming/read,write) */
	error = ioctl(iFd,VIDIOC_QUERYCAP,&tV4L2Cap);
	if(error)
	{
		debug("no this video device\n");
		return -1;
	}
	/* 2.1、检测是否视频CAPTURE设备 */
	if (!(tV4L2Cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
    	debug("not a video capture device\n");
       return -1;
    }
	/* 2.2、支持哪种接口:mmap read/write */
	if (tV4L2Cap.capabilities & V4L2_CAP_STREAMING) 
	{
	    debug("supports streaming i/o\n");
	}
    
	if (tV4L2Cap.capabilities & V4L2_CAP_READWRITE) 
	{
	    debug("supports read i/o\n");
	}
	/* 3、VIDIOC_ENUM_FMT 查询支持哪种格式 */
	memset(&tV4L2FmtDesc, 0, sizeof(tV4L2FmtDesc));
	tV4L2FmtDesc.index = 0;
	tV4L2FmtDesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	while ((error = ioctl(iFd, VIDIOC_ENUM_FMT, &tV4L2FmtDesc)) == 0) 
	{
		debug("ok %d\n",++cnt);
        if (!isSpFmt(tV4L2FmtDesc.pixelformat))
        {
            debug("Support :%d\n",tV4L2FmtDesc.pixelformat);
            break;
        }
		tV4L2FmtDesc.index++;
	}
	/* 4、 VIDIOC_S_FMT 设置摄像头使用哪种格式 */
	memset(&tV4l2Fmt, 0, sizeof(struct v4l2_format));
	tV4l2Fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	tV4l2Fmt.fmt.pix.pixelformat = tV4L2FmtDesc.pixelformat;
	debug("Support :%d\n",tV4l2Fmt.fmt.pix.pixelformat);
	tV4l2Fmt.fmt.pix.width       = 800;
	tV4l2Fmt.fmt.pix.height      = 480;
	tV4l2Fmt.fmt.pix.field       = V4L2_FIELD_ANY;

    /* 如果驱动程序发现无法某些参数(比如分辨率),
     * 它会调整这些参数, 并且返回给应用程序
     */
    error = ioctl(iFd, VIDIOC_S_FMT, &tV4l2Fmt); 
    if (error) 
    {
    	debug("Unable to set format\n");
       return -1;   
    }
	
	debug("Support Format:%d\n",tV4l2Fmt.fmt.pix.pixelformat);
	debug("Support width:%d\n",tV4l2Fmt.fmt.pix.width);
	debug("Support height:%d\n",tV4l2Fmt.fmt.pix.height);

	
	/* 初始化ptVideoBufIn结构体，为转化做准备 */
	ptVideoBufIn.iBpp = (tV4l2Fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV) ? 24 : \
                                        (tV4l2Fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG) ? 0 :  \
                                        (tV4l2Fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_RGB565) ? 16 :  \
                                        0;
	ptVideoBufIn.iHeight = tV4l2Fmt.fmt.pix.height;
	ptVideoBufIn.iWidth = tV4l2Fmt.fmt.pix.width;
	ptVideoBufIn.iLineBytes = ptVideoBufIn.iWidth*ptVideoBufIn.iBpp/8;
	ptVideoBufIn.iTotalBytes = ptVideoBufIn.iLineBytes * ptVideoBufIn.iHeight;
	debug("ptVideoBufIn.iBpp = %d\n",ptVideoBufIn.iBpp);
	/* 5、VIDIOC_REQBUFS  申请buffer */
	memset(&tV4l2ReqBuffs, 0, sizeof(struct v4l2_requestbuffers));
	/* 人为的想要分配4个buffer:实际上由VIDIOC_REQBUFS获取到的信息来决定 */
	tV4l2ReqBuffs.count   = 4;
	tV4l2ReqBuffs.type    = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	/* 表示申请的缓冲是支持MMAP */
	tV4l2ReqBuffs.memory  = V4L2_MEMORY_MMAP;
	/* 为分配buffer做准备 */
	error = ioctl(iFd, VIDIOC_REQBUFS, &tV4l2ReqBuffs);
	if (error) 
	{
		debug("Unable to allocate buffers.\n");
	    return -1;     
	}
	/* 判断是否支持mmap */
	if (tV4L2Cap.capabilities & V4L2_CAP_STREAMING)
	{
		 /* map the buffers */
        for (i = 0; i < tV4l2ReqBuffs.count; i++) 
        {
        	memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
        	tV4l2Buf.index = i;
        	tV4l2Buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        	tV4l2Buf.memory = V4L2_MEMORY_MMAP;
			/* 6、VIDIOC_QUERYBUF 确定每一个buffer的信息 并且 mmap */
        	error = ioctl(iFd, VIDIOC_QUERYBUF, &tV4l2Buf);
        	if (error) 
		{
			    debug("Unable to query buffer.\n");
			   return -1;
		}

            debug("length = %d\n",tV4l2Buf.length);
			
        	pucVideBuf[i] = mmap(0 /* start anywhere */ ,
        			  tV4l2Buf.length, PROT_READ, MAP_SHARED, iFd,
        			  tV4l2Buf.m.offset);
        	if (pucVideBuf[i] == MAP_FAILED) 
            {
        	    debug("Unable to map buffer\n");
        	   return -1;
        	}
			debug("mmap %d addr:%p\n",i,pucVideBuf[i]);
		}
	}

	/* 7、VIDIOC_QBUF  放入队列 */
    for (i = 0; i <tV4l2ReqBuffs.count; i++) 
    {
    	memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
    	tV4l2Buf.index = i;
    	tV4l2Buf.type  = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    	tV4l2Buf.memory = V4L2_MEMORY_MMAP;
    	error = ioctl(iFd, VIDIOC_QBUF, &tV4l2Buf);
    	if (error)
        {
    	    debug("Unable to queue buffer.\n");
    	  	 return -1;
    	}
    }
	debug("ready to read data\n");
	
	/* 8、启动摄像头开始读数据 */
    error = ioctl(iFd, VIDIOC_STREAMON, &iType);
    if (error) 
    {
    	debug("Unable to start capture.\n");
    	return -1;
    }
	return 0;
}


struct tsdev* open_ts(void)
{
	/* 打开设备节点 */
	struct tsdev *tss;
	char *tsdevice=NULL;

	if( (tsdevice = getenv("TSLIB_TSDEVICE")) != NULL ) 
	{
		tss = ts_open(tsdevice,0);
	} 
	else 
	{
         tss = ts_open("/dev/input/event0", 0);
	}
	if (!tss) 
	{
		debug("can't open ts\n");
		return NULL;
	}
	debug("start config.........\n");
	if (ts_config(tss)) 
	{
		debug("ts_config ok\n");
		return NULL;
	}
	debug("end config......\n");
	return tss;
	
}

int main(void)
{

	pthread_t tid1;
	pthread_t tid2;
	unsigned char flag=0;// 标志线程里面缩放后外面的缩放失效
	struct pollfd fds[1];
	unsigned int *fbmem1;
	unsigned int *re_fbmem;
	static int error;

	
	
	


	/* 1、打开触摸屏 */
	ts = open_ts();
	

	if(lcd_init())
		{
			int fd_fb;
			debug("fbmem init fail\n");
		}
	
	if(camera_init())
		{
				close(iFd);
				debug("camera init fail\n");
		}



	/* 8.1、使用poll来等待是否有数据 */
	fds[0].fd = iFd;
	fds[0].events = POLLIN;
	
	/* YUV格式的数据<------>在LCD上显示:rgb565 */
	initLut();
	ptVideoBufOut.aucPixelDatas =NULL;
	memset(fbmem,0,var.xres*var.yres*4);
	
	while(1)
	{
		//pthread_mutex_lock(&mutex);
		error = poll(fds, 1, -1);
		if (error <= 0)
		{
			debug("poll error!\n");
			return -1;
		}
		memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
		tV4l2Buf.type    = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		tV4l2Buf.memory  = V4L2_MEMORY_MMAP;
		/* 9、VIDIOC_DQBUF    从队列中取出 */
		error = ioctl(iFd, VIDIOC_DQBUF, &tV4l2Buf);
		if (error < 0) 
		{
			debug("Unable to dequeue buffer.\n");
			return -1;
		}
		debug("where is %d buffer\n",tV4l2Buf.index);
		debug("star debug video data:\n");

		ListNum = tV4l2Buf.index;
		ptVideoBufIn.aucPixelDatas = pucVideBuf[ListNum];
		Yuv2RgbConvert(&ptVideoBufIn,&ptVideoBufOut);

		if(flag==0)
		{
		debug("zoom:\n");
		tVideoZoom.iBpp = ptVideoBufOut.iBpp;
		tVideoZoom.iWidth = 800;
		tVideoZoom.iHeight = 480;
		tVideoZoom.iLineBytes = tVideoZoom.iWidth * tVideoZoom.iBpp/8;
		tVideoZoom.iTotalBytes = tVideoZoom.iLineBytes*tVideoZoom.iHeight;
		if (!tVideoZoom.aucPixelDatas)
		{
		   	tVideoZoom.aucPixelDatas = (unsigned char *)malloc(tVideoZoom.iTotalBytes);
		}
		pthread_create(&tid1,NULL,zoom_size, NULL);
		PicZoom(&ptVideoBufOut,&tVideoZoom);
		pthread_create(&tid2,NULL,get_bmp, NULL);
		
		flag=1;
		}
		else
			{
			PicZoom(&ptVideoBufOut,&tVideoZoom);
			}
		/* 缩放 */
		
		//void *(*start_routine)(void*)
		//PicZoom(&ptVideoBufOut,&tVideoZoom);	
		debug("************show6**********\n");
		pthread_mutex_lock(&mutex);
		
		to_senter_show(tVideoZoom,fbmem,tVideoZoom.aucPixelDatas);
		pthread_mutex_unlock(&mutex);
		
		//debug("show time:\n");
		//screen_size=tV4l2Fmt.fmt.pix.width*tV4l2Fmt.fmt.pix.height*4;
		
		 
		
		
			
		/* 显示转化的数据:已经转化为16bpp了 */
		debug("************show7**********\n");
		memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
		tV4l2Buf.index  = ListNum;
		tV4l2Buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		tV4l2Buf.memory = V4L2_MEMORY_MMAP;
		/* VIDIOC_QBUF     放入队列 */
		error = ioctl(iFd, VIDIOC_QBUF, &tV4l2Buf);
		if (error) 
		{
			debug("Unable to queue buffer.\n");
			return -1;
		}
#if 0
		debug("stop capture......\n");
		/* VIDIOC_STREAMOFF 停止设备 */
		error = ioctl(iFd, VIDIOC_STREAMOFF, &iType);
		if (error) 
		{
		debug("Unable to stop capture.\n");
		return -1;
		}
		debug("stop capture......ok\n");
#endif
	//	pthread_mutex_unlock(&mutex);
	}
	close(iFd);
	munmap(fbmem, screen_size);

	return 0;
}

/* 图片缩放算法 */
/**********************************************************************
 * 函数名称： PicZoom
 * 功能描述： 近邻取样插值方法缩放图片
 *            注意该函数会分配内存来存放缩放后的图片,用完后要用free函数释放掉
 *            "近邻取样插值"的原理请参考网友"lantianyu520"所著的"图像缩放算法"
 * 输入参数： ptOriginPic - 内含原始图片的象素数据
 *            ptBigPic    - 内含缩放后的图片的象素数据
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 ***********************************************************************/
static int PicZoom(PT_PixelDatas ptOriginPic, PT_PixelDatas ptZoomPic)
{
	unsigned long dwDstWidth = ptZoomPic->iWidth;
	unsigned long* pdwSrcXTable;
	unsigned long x;
	unsigned long y;
	unsigned long dwSrcY;
	unsigned char *pucDest;
	unsigned char *pucSrc;
	unsigned long dwPixelBytes = ptOriginPic->iBpp/8;

	debug("src:\n");
	debug("%d x %d, %d bpp, data: 0x%x\n", ptOriginPic->iWidth, ptOriginPic->iHeight, ptOriginPic->iBpp, (unsigned int)ptOriginPic->aucPixelDatas);

	debug("dest:\n");
	debug("%d x %d, %d bpp, data: 0x%x\n", ptZoomPic->iWidth, ptZoomPic->iHeight, ptZoomPic->iBpp, (unsigned int)ptZoomPic->aucPixelDatas);

	if (ptOriginPic->iBpp != ptZoomPic->iBpp)
	{
		return -1;
	}

	pdwSrcXTable = malloc(sizeof(unsigned long) * dwDstWidth);
	if (NULL == pdwSrcXTable)
	{
	    debug("malloc error!\n");
	    return -1;
	}

	for (x = 0; x < dwDstWidth; x++)//生成表 pdwSrcXTable
	{
	    	pdwSrcXTable[x]=(x*ptOriginPic->iWidth/ptZoomPic->iWidth);
	}

	for (y = 0; y < ptZoomPic->iHeight; y++)
	{			
	    dwSrcY = (y * ptOriginPic->iHeight / ptZoomPic->iHeight);

		pucDest = ptZoomPic->aucPixelDatas + y*ptZoomPic->iLineBytes;
		pucSrc  = ptOriginPic->aucPixelDatas + dwSrcY*ptOriginPic->iLineBytes;
		
	    for (x = 0; x <dwDstWidth; x++)
	    {
	        /* 原图座标: pdwSrcXTable[x]，srcy
	         * 缩放座标: x, y
			 */
			 memcpy(pucDest+x*dwPixelBytes, pucSrc+pdwSrcXTable[x]*dwPixelBytes, dwPixelBytes);
	    }
	}

	free(pdwSrcXTable);
	return 0;
}
