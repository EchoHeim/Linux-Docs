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

static int SpFmt[] = {V4L2_PIX_FMT_YUYV, V4L2_PIX_FMT_MJPEG, V4L2_PIX_FMT_RGB565};
static char *ShowFmt[] = {"YUV", "MJPEG", "RGB565"};

/* ͼƬ���������� */
typedef struct PixelDatas {
	int iWidth;   /* ���: һ���ж��ٸ����� */
	int iHeight;  /* �߶�: һ���ж��ٸ����� */
	int iBpp;     /* һ�������ö���λ����ʾ */
	int iLineBytes;  /* һ�������ж����ֽ� */
	int iTotalBytes; /* �����ֽ��� */ 
	unsigned char *aucPixelDatas;  /* �������ݴ洢�ĵط� */
}T_PixelDatas, *PT_PixelDatas;


int isSpFmt(int FmtPix)
{
	int i=0;
	for(i=0;i<sizeof(SpFmt)/sizeof(SpFmt[0]);i++)
	{
		if(SpFmt[i] == FmtPix)
		{
			printf("Fomat is :%s\n",ShowFmt[i]);
			return 0;
		}
	}
	return -1;
}


 
static unsigned int
Pyuv422torgb565(unsigned char * input_ptr, unsigned char * output_ptr, unsigned int image_width, unsigned int image_height)
{
	unsigned int i, size;
	unsigned char Y, Y1, U, V;
	unsigned char *buff = input_ptr;
	unsigned char *output_pt = output_ptr;

    unsigned int r, g, b;
    unsigned int color;
    
	size = image_width * image_height /2;
	for (i = size; i > 0; i--) {
		/* bgr instead rgb ?? */
		Y = buff[0] ;
		U = buff[1] ;
		Y1 = buff[2];
		V = buff[3];
		buff += 4;
		r = R_FROMYV(Y,V);
		g = G_FROMYUV(Y,U,V); //b
		b = B_FROMYU(Y,U); //v
        /* ��r,g,b��ɫ����Ϊrgb565��16λֵ */
        r = r >> 3;
        g = g >> 2;
        b = b >> 3;
        color = (r << 11) | (g << 5) | b;
        *output_pt++ = color & 0xff;
        *output_pt++ = (color >> 8) & 0xff;
			
		r = R_FROMYV(Y1,V);
		g = G_FROMYUV(Y1,U,V); //b
		b = B_FROMYU(Y1,U); //v
        /* ��r,g,b��ɫ����Ϊrgb565��16λֵ */
        r = r >> 3;
        g = g >> 2;
        b = b >> 3;
        color = (r << 11) | (g << 5) | b;
        *output_pt++ = color & 0xff;
        *output_pt++ = (color >> 8) & 0xff;
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

	ptPixelDatasOut->iBpp = 16;
	ptPixelDatasOut->iLineBytes  = ptPixelDatasOut->iWidth * ptPixelDatasOut->iBpp / 8;
	ptPixelDatasOut->iTotalBytes = ptPixelDatasOut->iLineBytes * ptPixelDatasOut->iHeight;

	if (!ptPixelDatasOut->aucPixelDatas)
	{
		ptPixelDatasOut->aucPixelDatas = malloc(ptPixelDatasOut->iTotalBytes);
	}
	
	Pyuv422torgb565(ptPixelDatasIn->aucPixelDatas, ptPixelDatasOut->aucPixelDatas, ptPixelDatasOut->iWidth, ptPixelDatasOut->iHeight);
	
	return 0;
 
}
int main(void)
{
	int iFd;
	int error;
	int cnt=0;
	int i=0;
	int ListNum;
	int iType = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	unsigned char* pucVideBuf[4];
	T_PixelDatas ptVideoBufIn;
	T_PixelDatas ptVideoBufOut;
	//unsigned char *LcdTmp;
	struct v4l2_capability tV4L2Cap;
	struct v4l2_fmtdesc tV4L2FmtDesc;

	struct v4l2_format  tV4l2Fmt;
	
	struct v4l2_requestbuffers tV4l2ReqBuffs;

	struct v4l2_buffer tV4l2Buf;

	struct pollfd fds[1];

/*********************************************************************/
/* ��fb�豸:lcd�豸 */
	int fd_fb;
	struct fb_var_screeninfo var;	/* Current var */
	struct fb_fix_screeninfo fix;	/* Current fix */
	int screen_size;
	unsigned char *fbmem;
	unsigned int line_width;
	unsigned int pixel_width;

	
	
	fd_fb = open("/dev/fb0", O_RDWR);
	if (fd_fb < 0)
	{
		printf("can't open /dev/fb0\n");
		return -1;
	}
	/* ͨ��ioctl��ȡ�ɱ����:var */
	if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &var))
	{
		printf("can't get var\n");
		return -1;
	}
	printf("x = %d\n",var.xres);
	printf("y = %d\n",var.yres);
	printf("Bpp = %d\n",var.bits_per_pixel);
	/* ͨ��ioctl��ȡ�ɱ����:fix */
	if (ioctl(fd_fb, FBIOGET_FSCREENINFO, &fix))
	{
		printf("can't get fix\n");
		return -1;
	}
	printf("size : %d\n",fix.smem_len);
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
		printf("can't mmap\n");
		return -1;
	}
/*********************************************************************/	
	
	/* 1������Ƶ�豸 */
	iFd = open("/dev/video0",O_RDWR);
	if(iFd < 0)
	{
		printf("can't open /dev/video\n");
		goto exit_video;
	}
	
	/* 2��VIDIOC_QUERYCAP ȷ�����Ƿ���Ƶ��׽�豸,֧�����ֽӿ�(streaming/read,write) */
	error = ioctl(iFd,VIDIOC_QUERYCAP,&tV4L2Cap);
	if(error)
	{
		printf("no this video device\n");
		goto exit_video;
	}
	/* 2.1������Ƿ���ƵCAPTURE�豸 */
	if (!(tV4L2Cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
    	printf("not a video capture device\n");
        goto exit_video;
    }
	/* 2.2��֧�����ֽӿ�:mmap read/write */
	if (tV4L2Cap.capabilities & V4L2_CAP_STREAMING) 
	{
	    printf("supports streaming i/o\n");
	}
    
	if (tV4L2Cap.capabilities & V4L2_CAP_READWRITE) 
	{
	    printf("supports read i/o\n");
	}

	/* 3��VIDIOC_ENUM_FMT ��ѯ֧�����ָ�ʽ */
	memset(&tV4L2FmtDesc, 0, sizeof(tV4L2FmtDesc));
	tV4L2FmtDesc.index = 0;
	tV4L2FmtDesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	while ((error = ioctl(iFd, VIDIOC_ENUM_FMT, &tV4L2FmtDesc)) == 0) 
	{
		printf("ok %d\n",++cnt);
        if (!isSpFmt(tV4L2FmtDesc.pixelformat))
        {
            printf("Support :%d\n",tV4L2FmtDesc.pixelformat);
            break;
        }
		tV4L2FmtDesc.index++;
	}
	/* 4�� VIDIOC_S_FMT ��������ͷʹ�����ָ�ʽ */
	memset(&tV4l2Fmt, 0, sizeof(struct v4l2_format));
	tV4l2Fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	tV4l2Fmt.fmt.pix.pixelformat = tV4L2FmtDesc.pixelformat;
	printf("Support :%d\n",tV4l2Fmt.fmt.pix.pixelformat);
	tV4l2Fmt.fmt.pix.width       = 320;
	tV4l2Fmt.fmt.pix.height      = 240;
	tV4l2Fmt.fmt.pix.field       = V4L2_FIELD_ANY;

    /* ��������������޷�ĳЩ����(����ֱ���),
     * ���������Щ����, ���ҷ��ظ�Ӧ�ó���
     */
    error = ioctl(iFd, VIDIOC_S_FMT, &tV4l2Fmt); 
    if (error) 
    {
    	printf("Unable to set format\n");
        goto exit_video;        
    }
	
	printf("Support Format:%d\n",tV4l2Fmt.fmt.pix.pixelformat);
	printf("Support width:%d\n",tV4l2Fmt.fmt.pix.width);
	printf("Support height:%d\n",tV4l2Fmt.fmt.pix.height);

	
	/* ��ʼ��ptVideoBufIn�ṹ�壬Ϊת����׼�� */
	ptVideoBufIn.iBpp = (tV4l2Fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV) ? 16 : \
                                        (tV4l2Fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG) ? 0 :  \
                                        (tV4l2Fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_RGB565) ? 16 :  \
                                        0;
	ptVideoBufIn.iHeight = tV4l2Fmt.fmt.pix.height;
	ptVideoBufIn.iWidth = tV4l2Fmt.fmt.pix.width;
	ptVideoBufIn.iLineBytes = ptVideoBufIn.iWidth*ptVideoBufIn.iBpp/8;
	ptVideoBufIn.iTotalBytes = ptVideoBufIn.iLineBytes * ptVideoBufIn.iHeight;
	printf("ptVideoBufIn.iBpp = %d\n",ptVideoBufIn.iBpp);
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
		printf("Unable to allocate buffers.\n");
	    goto exit_video;        
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
			    printf("Unable to query buffer.\n");
			    goto exit_video;
		}

            printf("length = %d\n",tV4l2Buf.length);
			
        	pucVideBuf[i] = mmap(0 /* start anywhere */ ,
        			  tV4l2Buf.length, PROT_READ, MAP_SHARED, iFd,
        			  tV4l2Buf.m.offset);
        	if (pucVideBuf[i] == MAP_FAILED) 
            {
        	    printf("Unable to map buffer\n");
        	    goto exit_video;
        	}
			printf("mmap %d addr:%p\n",i,pucVideBuf[i]);
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
    	    printf("Unable to queue buffer.\n");
    	    goto exit_video;
    	}
    }
	printf("ready to read data\n");
	
	/* 8����������ͷ��ʼ������ */
    error = ioctl(iFd, VIDIOC_STREAMON, &iType);
    if (error) 
    {
    	printf("Unable to start capture.\n");
    	goto exit_video;
    }
	/* 8.1��ʹ��poll���ȴ��Ƿ������� */
	fds[0].fd = iFd;
	fds[0].events = POLLIN;
	
	/* YUV��ʽ������<------>��LCD����ʾ:rgb565 */
	initLut();
	ptVideoBufOut.aucPixelDatas =NULL;
//	while(1)
//	{
		error = poll(fds, 1, -1);
    	if (error <= 0)
    	{
        	printf("poll error!\n");
        	return -1;
    	}
	memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
	tV4l2Buf.type    = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	tV4l2Buf.memory  = V4L2_MEMORY_MMAP;
		/* 9��VIDIOC_DQBUF    �Ӷ�����ȡ�� */
	    error = ioctl(iFd, VIDIOC_DQBUF, &tV4l2Buf);
	    if (error < 0) 
	    {
	    	printf("Unable to dequeue buffer.\n");
	    	return -1;
	    }
		printf("where is %d buffer\n",tV4l2Buf.index);
		printf("star printf video data:\n");
	
		ListNum = tV4l2Buf.index;
		ptVideoBufIn.aucPixelDatas = pucVideBuf[ListNum];
		Yuv2RgbConvert(&ptVideoBufIn,&ptVideoBufOut);
		
		printf("show time:\n");
		memcpy(fbmem,ptVideoBufOut.aucPixelDatas,screen_size);
		/* ��ʾת��������:�Ѿ�ת��Ϊ16bpp�� */
		
		memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
		tV4l2Buf.index  = ListNum;
		tV4l2Buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		tV4l2Buf.memory = V4L2_MEMORY_MMAP;
		/* VIDIOC_QBUF     ������� */
		error = ioctl(iFd, VIDIOC_QBUF, &tV4l2Buf);
		if (error) 
	    {
		    printf("Unable to queue buffer.\n");
		    return -1;
		}
#if 0
		printf("stop capture......\n");
		/* VIDIOC_STREAMOFF ֹͣ�豸 */
		error = ioctl(iFd, VIDIOC_STREAMOFF, &iType);
	    if (error) 
	    {
	    	printf("Unable to stop capture.\n");
	    	return -1;
	    }
	 	printf("stop capture......ok\n");
#endif
//	}
	close(iFd);
	return 0;
exit_video:
	close(iFd);
	return -1;
}



