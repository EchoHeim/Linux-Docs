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

static int SpFmt[] 		= {V4L2_PIX_FMT_YUYV, V4L2_PIX_FMT_MJPEG, V4L2_PIX_FMT_RGB565};
static char *ShowFmt[] 	= {"YUV", "MJPEG", "RGB565"};

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

int main(void)
{
	int iFd;
	int error;
	int cnt=0;
	int i=0;

	char* pucVideBuf[4];
	struct v4l2_capability tV4L2Cap;
	struct v4l2_fmtdesc tV4L2FmtDesc;

	struct v4l2_format  tV4l2Fmt;
	
	struct v4l2_requestbuffers tV4l2ReqBuffs;

	struct v4l2_buffer tV4l2Buf;
	/* 1������Ƶ�豸 ls /dev/video* */
	iFd = open("/dev/video15",O_RDWR);
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
	/* ����Ƿ���ƵCAPTURE�豸:read/wirte mmap */
	if (!(tV4L2Cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
	{
		printf("not a video capture device\n");
		goto exit_video;
	}
	/* ֧�����ֽӿ�:mmap read/write */
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
		/* ��ʽ������ */
		tV4L2FmtDesc.index++;
	}
	/* 4�� VIDIOC_S_FMT ��������ͷʹ�����ָ�ʽ */
	memset(&tV4l2Fmt, 0, sizeof(struct v4l2_format));
	tV4l2Fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	tV4l2Fmt.fmt.pix.pixelformat = tV4L2FmtDesc.pixelformat;
	printf("Support :%d\n",tV4l2Fmt.fmt.pix.pixelformat);
	tV4l2Fmt.fmt.pix.width       = 800;
	tV4l2Fmt.fmt.pix.height      = 480;
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

	/* 5��VIDIOC_REQBUFS  ����buffer */
	memset(&tV4l2ReqBuffs, 0, sizeof(struct v4l2_requestbuffers));
	/* ��Ϊ����Ҫ����4��buffer:ʵ������VIDIOC_REQBUFS��ȡ������Ϣ������ */
	tV4l2ReqBuffs.count   = 4;//������ٸ�
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
	/* 8.1��ʹ��poll���ȴ��Ƿ������� */
	
	close(iFd);
	return 0;
exit_video:
	close(iFd);
	return -1;
}



