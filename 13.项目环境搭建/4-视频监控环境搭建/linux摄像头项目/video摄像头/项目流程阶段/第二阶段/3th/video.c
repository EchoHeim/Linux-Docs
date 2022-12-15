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

/* 图片的象素数据 */
typedef struct PixelDatas {
	int iWidth;   /* 宽度: 一行有多少个象素 */
	int iHeight;  /* 高度: 一列有多少个象素 */
	int iBpp;     /* 一个象素用多少位来表示 */
	int iLineBytes;  /* 一行数据有多少字节 */
	int iTotalBytes; /* 所有字节数 */ 
	unsigned char *aucPixelDatas;  /* 象素数据存储的地方 */
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
        /* 把r,g,b三色构造为rgb565的16位值 */
        r = r >> 3;
        g = g >> 2;
        b = b >> 3;
        color = (r << 11) | (g << 5) | b;
        *output_pt++ = color & 0xff;
        *output_pt++ = (color >> 8) & 0xff;
			
		r = R_FROMYV(Y1,V);
		g = G_FROMYUV(Y1,U,V); //b
		b = B_FROMYU(Y1,U); //v
        /* 把r,g,b三色构造为rgb565的16位值 */
        r = r >> 3;
        g = g >> 2;
        b = b >> 3;
        color = (r << 11) | (g << 5) | b;
        *output_pt++ = color & 0xff;
        *output_pt++ = (color >> 8) & 0xff;
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
/* 打开fb设备:lcd设备 */
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
	/* 通过ioctl获取可变参数:var */
	if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &var))
	{
		printf("can't get var\n");
		return -1;
	}
	printf("x = %d\n",var.xres);
	printf("y = %d\n",var.yres);
	printf("Bpp = %d\n",var.bits_per_pixel);
	/* 通过ioctl获取可变参数:fix */
	if (ioctl(fd_fb, FBIOGET_FSCREENINFO, &fix))
	{
		printf("can't get fix\n");
		return -1;
	}
	printf("size : %d\n",fix.smem_len);
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
		printf("can't mmap\n");
		return -1;
	}
/*********************************************************************/	
	
	/* 1、打开视频设备 */
	iFd = open("/dev/video0",O_RDWR);
	if(iFd < 0)
	{
		printf("can't open /dev/video\n");
		goto exit_video;
	}
	
	/* 2、VIDIOC_QUERYCAP 确定它是否视频捕捉设备,支持哪种接口(streaming/read,write) */
	error = ioctl(iFd,VIDIOC_QUERYCAP,&tV4L2Cap);
	if(error)
	{
		printf("no this video device\n");
		goto exit_video;
	}
	/* 2.1、检测是否视频CAPTURE设备 */
	if (!(tV4L2Cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
    	printf("not a video capture device\n");
        goto exit_video;
    }
	/* 2.2、支持哪种接口:mmap read/write */
	if (tV4L2Cap.capabilities & V4L2_CAP_STREAMING) 
	{
	    printf("supports streaming i/o\n");
	}
    
	if (tV4L2Cap.capabilities & V4L2_CAP_READWRITE) 
	{
	    printf("supports read i/o\n");
	}

	/* 3、VIDIOC_ENUM_FMT 查询支持哪种格式 */
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
	/* 4、 VIDIOC_S_FMT 设置摄像头使用哪种格式 */
	memset(&tV4l2Fmt, 0, sizeof(struct v4l2_format));
	tV4l2Fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	tV4l2Fmt.fmt.pix.pixelformat = tV4L2FmtDesc.pixelformat;
	printf("Support :%d\n",tV4l2Fmt.fmt.pix.pixelformat);
	tV4l2Fmt.fmt.pix.width       = 320;
	tV4l2Fmt.fmt.pix.height      = 240;
	tV4l2Fmt.fmt.pix.field       = V4L2_FIELD_ANY;

    /* 如果驱动程序发现无法某些参数(比如分辨率),
     * 它会调整这些参数, 并且返回给应用程序
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

	
	/* 初始化ptVideoBufIn结构体，为转化做准备 */
	ptVideoBufIn.iBpp = (tV4l2Fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV) ? 16 : \
                                        (tV4l2Fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG) ? 0 :  \
                                        (tV4l2Fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_RGB565) ? 16 :  \
                                        0;
	ptVideoBufIn.iHeight = tV4l2Fmt.fmt.pix.height;
	ptVideoBufIn.iWidth = tV4l2Fmt.fmt.pix.width;
	ptVideoBufIn.iLineBytes = ptVideoBufIn.iWidth*ptVideoBufIn.iBpp/8;
	ptVideoBufIn.iTotalBytes = ptVideoBufIn.iLineBytes * ptVideoBufIn.iHeight;
	printf("ptVideoBufIn.iBpp = %d\n",ptVideoBufIn.iBpp);
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
		printf("Unable to allocate buffers.\n");
	    goto exit_video;        
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
    	    printf("Unable to queue buffer.\n");
    	    goto exit_video;
    	}
    }
	printf("ready to read data\n");
	
	/* 8、启动摄像头开始读数据 */
    error = ioctl(iFd, VIDIOC_STREAMON, &iType);
    if (error) 
    {
    	printf("Unable to start capture.\n");
    	goto exit_video;
    }
	/* 8.1、使用poll来等待是否有数据 */
	fds[0].fd = iFd;
	fds[0].events = POLLIN;
	
	/* YUV格式的数据<------>在LCD上显示:rgb565 */
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
		/* 9、VIDIOC_DQBUF    从队列中取出 */
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
		/* 显示转化的数据:已经转化为16bpp了 */
		
		memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
		tV4l2Buf.index  = ListNum;
		tV4l2Buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		tV4l2Buf.memory = V4L2_MEMORY_MMAP;
		/* VIDIOC_QBUF     放入队列 */
		error = ioctl(iFd, VIDIOC_QBUF, &tV4l2Buf);
		if (error) 
	    {
		    printf("Unable to queue buffer.\n");
		    return -1;
		}
#if 0
		printf("stop capture......\n");
		/* VIDIOC_STREAMOFF 停止设备 */
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



