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
/* �������� */
static pthread_cond_t cond   = PTHREAD_COND_INITIALIZER;

#ifdef Debug
#define debug printf
#else
#define debug //
#endif

/* ͼƬ���������� */
typedef struct PixelDatas {
	int iWidth;   /* ���: һ���ж��ٸ����� */
	int iHeight;  /* �߶�: һ���ж��ٸ����� */
	int iBpp;     /* һ�������ö���λ����ʾ */
	int iLineBytes;  /* һ�������ж����ֽ� */
	int iTotalBytes; /* �����ֽ��� */ 
	unsigned char *aucPixelDatas;  /* �������ݴ洢�ĵط� */
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


#pragma pack(push) /* ����ǰpack����ѹջ���� */
#pragma pack(1)    /* �����ڽṹ�嶨��֮ǰʹ��,����Ϊ���ýṹ���и���Ա��1�ֽڶ��� */

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

#pragma pack(pop) /* �ָ���ǰ��pack���� */

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

	/* ��ȡ�ļ���Ϣͷ */
    ptBITMAPFILEHEADER = (BITMAPFILEHEADER *)filemem;
	
   	ptBITMAPFILEHEADER->bfType = 0x4D42;    
    ptBITMAPFILEHEADER->bfSize = 0x25836;   
    ptBITMAPFILEHEADER->bfReserved1 = 0x0;   
    ptBITMAPFILEHEADER->bfReserved2 = 0x0;
    ptBITMAPFILEHEADER->bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
 
    /* ��ȡλͼ��Ϣͷ */
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
	unsigned char *file_name="test1.bmp";  //Ϊʲô������ָ��
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
	//ʹ��mmap���ܻ������Ϊ�򿪵�Ϊ���ļ�
	memset(filemem,0,lenth);
	printf("filemem=%p\n",filemem);
	
	/* ��ȡͼƬ��ʼ��ַ */
  	mov=filemem;
	
	bmp_init(mov);
	
	//photo_par[i].iLineWidthReal = photo_par[i].iWidth * photo_par[i].iBMPBpp / 8;
	//photo_par[i].iLineWidthAlign = (photo_par[i].iLineWidthReal + 3) & ~0x3;   /* ��4ȡ�� */

	/* ʵ��ͼ��洢��λ�� */
	pucdest = mov+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	
	pucdest= pucdest +(tVideoZoom.iHeight-1)*tVideoZoom.iWidth*4;
	pucSrc=tVideoZoom.aucPixelDatas;

	
	pucdest1=(unsigned int *)pucdest;
	
	for(j=0;j<tVideoZoom.iHeight;j++)
		{
			pucdest1=(unsigned int *)pucdest-j*tVideoZoom.iWidth;
			//ÿ�ζ�λ���еĿ�ͷʱ����Ҫ�ظ�����
			//��pucdest1=(unsigned int *)pucdest1-j*tVideoZoom.iWidth;

			
			//pucdest1=(unsigned int *)(pucdest-j*tVideoZoom.iWidth*4);  ��������ַ���
			
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
			//pthread_cond_wait(&cond,&mutex); //˯��
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

/* �ο�luvcview */

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
/* ��fb�豸:lcd�豸 */
	
	
	
	unsigned int line_width;
	unsigned int pixel_width;

	
	
	fd_fb = open("/dev/fb0", O_RDWR);
	if (fd_fb < 0)
	{
		debug("can't open /dev/fb0\n");
		return 0;
	}
	/* ͨ��ioctl��ȡ�ɱ����:var */
	if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &var))
	{
		debug("can't get var\n");
		return -1;
	}
	debug("x = %d\n",var.xres);
	debug("y = %d\n",var.yres);
	debug("Bpp = %d\n",var.bits_per_pixel);
	/* ͨ��ioctl��ȡ�ɱ����:fix */
	if (ioctl(fd_fb, FBIOGET_FSCREENINFO, &fix))
	{
		debug("can't get fix\n");
		return -1;
	}
	debug("size : %d\n",fix.smem_len);
	/* �п� */
	line_width  = var.xres * var.bits_per_pixel / 8;
	/* һ������ռ�˼����ֽ� */
	pixel_width = var.bits_per_pixel / 8;
	/* �Դ��С */
	screen_size = var.xres * var.yres * var.bits_per_pixel / 8;
	/* ӳ���Դ� */
	
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
	
	/* 1������Ƶ�豸 */
	iFd = open("/dev/video15",O_RDWR);
	if(iFd < 0)
	{
		debug("can't open /dev/video\n");
		return 0;
	}
	
	/* 2��VIDIOC_QUERYCAP ȷ�����Ƿ���Ƶ��׽�豸,֧�����ֽӿ�(streaming/read,write) */
	error = ioctl(iFd,VIDIOC_QUERYCAP,&tV4L2Cap);
	if(error)
	{
		debug("no this video device\n");
		return -1;
	}
	/* 2.1������Ƿ���ƵCAPTURE�豸 */
	if (!(tV4L2Cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
    	debug("not a video capture device\n");
       return -1;
    }
	/* 2.2��֧�����ֽӿ�:mmap read/write */
	if (tV4L2Cap.capabilities & V4L2_CAP_STREAMING) 
	{
	    debug("supports streaming i/o\n");
	}
    
	if (tV4L2Cap.capabilities & V4L2_CAP_READWRITE) 
	{
	    debug("supports read i/o\n");
	}
	/* 3��VIDIOC_ENUM_FMT ��ѯ֧�����ָ�ʽ */
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
	/* 4�� VIDIOC_S_FMT ��������ͷʹ�����ָ�ʽ */
	memset(&tV4l2Fmt, 0, sizeof(struct v4l2_format));
	tV4l2Fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	tV4l2Fmt.fmt.pix.pixelformat = tV4L2FmtDesc.pixelformat;
	debug("Support :%d\n",tV4l2Fmt.fmt.pix.pixelformat);
	tV4l2Fmt.fmt.pix.width       = 800;
	tV4l2Fmt.fmt.pix.height      = 480;
	tV4l2Fmt.fmt.pix.field       = V4L2_FIELD_ANY;

    /* ��������������޷�ĳЩ����(����ֱ���),
     * ���������Щ����, ���ҷ��ظ�Ӧ�ó���
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

	
	/* ��ʼ��ptVideoBufIn�ṹ�壬Ϊת����׼�� */
	ptVideoBufIn.iBpp = (tV4l2Fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV) ? 24 : \
                                        (tV4l2Fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG) ? 0 :  \
                                        (tV4l2Fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_RGB565) ? 16 :  \
                                        0;
	ptVideoBufIn.iHeight = tV4l2Fmt.fmt.pix.height;
	ptVideoBufIn.iWidth = tV4l2Fmt.fmt.pix.width;
	ptVideoBufIn.iLineBytes = ptVideoBufIn.iWidth*ptVideoBufIn.iBpp/8;
	ptVideoBufIn.iTotalBytes = ptVideoBufIn.iLineBytes * ptVideoBufIn.iHeight;
	debug("ptVideoBufIn.iBpp = %d\n",ptVideoBufIn.iBpp);
	/* 5��VIDIOC_REQBUFS  ����buffer */
	memset(&tV4l2ReqBuffs, 0, sizeof(struct v4l2_requestbuffers));
	/* ��Ϊ����Ҫ����4��buffer:ʵ������VIDIOC_REQBUFS��ȡ������Ϣ������ */
	tV4l2ReqBuffs.count   = 4;
	tV4l2ReqBuffs.type    = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	/* ��ʾ����Ļ�����֧��MMAP */
	tV4l2ReqBuffs.memory  = V4L2_MEMORY_MMAP;
	/* Ϊ����buffer��׼�� */
	error = ioctl(iFd, VIDIOC_REQBUFS, &tV4l2ReqBuffs);
	if (error) 
	{
		debug("Unable to allocate buffers.\n");
	    return -1;     
	}
	/* �ж��Ƿ�֧��mmap */
	if (tV4L2Cap.capabilities & V4L2_CAP_STREAMING)
	{
		 /* map the buffers */
        for (i = 0; i < tV4l2ReqBuffs.count; i++) 
        {
        	memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
        	tV4l2Buf.index = i;
        	tV4l2Buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        	tV4l2Buf.memory = V4L2_MEMORY_MMAP;
			/* 6��VIDIOC_QUERYBUF ȷ��ÿһ��buffer����Ϣ ���� mmap */
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

	/* 7��VIDIOC_QBUF  ������� */
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
	
	/* 8����������ͷ��ʼ������ */
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
	/* ���豸�ڵ� */
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
	unsigned char flag=0;// ��־�߳��������ź����������ʧЧ
	struct pollfd fds[1];
	unsigned int *fbmem1;
	unsigned int *re_fbmem;
	static int error;

	
	
	


	/* 1���򿪴����� */
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



	/* 8.1��ʹ��poll���ȴ��Ƿ������� */
	fds[0].fd = iFd;
	fds[0].events = POLLIN;
	
	/* YUV��ʽ������<------>��LCD����ʾ:rgb565 */
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
		/* 9��VIDIOC_DQBUF    �Ӷ�����ȡ�� */
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
		/* ���� */
		
		//void *(*start_routine)(void*)
		//PicZoom(&ptVideoBufOut,&tVideoZoom);	
		debug("************show6**********\n");
		pthread_mutex_lock(&mutex);
		
		to_senter_show(tVideoZoom,fbmem,tVideoZoom.aucPixelDatas);
		pthread_mutex_unlock(&mutex);
		
		//debug("show time:\n");
		//screen_size=tV4l2Fmt.fmt.pix.width*tV4l2Fmt.fmt.pix.height*4;
		
		 
		
		
			
		/* ��ʾת��������:�Ѿ�ת��Ϊ16bpp�� */
		debug("************show7**********\n");
		memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
		tV4l2Buf.index  = ListNum;
		tV4l2Buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		tV4l2Buf.memory = V4L2_MEMORY_MMAP;
		/* VIDIOC_QBUF     ������� */
		error = ioctl(iFd, VIDIOC_QBUF, &tV4l2Buf);
		if (error) 
		{
			debug("Unable to queue buffer.\n");
			return -1;
		}
#if 0
		debug("stop capture......\n");
		/* VIDIOC_STREAMOFF ֹͣ�豸 */
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

/* ͼƬ�����㷨 */
/**********************************************************************
 * �������ƣ� PicZoom
 * ���������� ����ȡ����ֵ��������ͼƬ
 *            ע��ú���������ڴ���������ź��ͼƬ,�����Ҫ��free�����ͷŵ�
 *            "����ȡ����ֵ"��ԭ����ο�����"lantianyu520"������"ͼ�������㷨"
 * ��������� ptOriginPic - �ں�ԭʼͼƬ����������
 *            ptBigPic    - �ں����ź��ͼƬ����������
 * ��������� ��
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
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

	for (x = 0; x < dwDstWidth; x++)//���ɱ� pdwSrcXTable
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
	        /* ԭͼ����: pdwSrcXTable[x]��srcy
	         * ��������: x, y
			 */
			 memcpy(pucDest+x*dwPixelBytes, pucSrc+pdwSrcXTable[x]*dwPixelBytes, dwPixelBytes);
	    }
	}

	free(pdwSrcXTable);
	return 0;
}
