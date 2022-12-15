#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <config.h>
#include <disp_manager.h>
#include <video_recv_manager.h>
#include <convert_manager.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

PT_VideoRecv g_ptVideoRecvOpr;
int iSocketClient;

extern int PicMerge(int iX, int iY, PT_PixelDatas ptSmallPic, PT_PixelDatas ptBigPic);

void *RecvVideoThread(void *data)
{
	if(g_ptVideoRecvOpr->Get_Video(&iSocketClient, (PT_VideoBuf)data) < 0)
	{		
		DBG_PRINTF("can not Get_Video\n");
	}

	return data;
}

/* video2lcd </dev/video0,1,...> */
int main(int argc, char **argv)
{	
	int iError;
	pthread_t RecvVideo_Id;
	PT_VideoConvert ptVideoConvert;
	int iPixelFormatOfVideo;
	int iPixelFormatOfDisp;

	PT_VideoBuf ptVideoBufCur;
	T_VideoBuf tVideoBuf;
	T_VideoBuf tConvertBuf;
	T_VideoBuf tFrameBuf;

	int iLcdWidth;
	int iLcdHeigt;
	int iLcdBpp;

	int iTopLeftX;
	int iTopLeftY;
    
	if (argc != 2)
	{
		printf("Usage:\n");
		printf("%s <ip>\n", argv[0]);
		return -1;
	}

	
	/* 一系列的初始化 */
	/* 注册显示设备 */
	DisplayInit();
	/* 可能可支持多个显示设备: 选择和初始化指定的显示设备 */
	SelectAndInitDefaultDispDev("crt");
	GetDispResolution(&iLcdWidth, &iLcdHeigt, &iLcdBpp);
	GetVideoBufForDisplay(&tFrameBuf);
	iPixelFormatOfDisp = tFrameBuf.iPixelFormat;

	VideoRecvInit();
	ShowVideoRecv();
	g_ptVideoRecvOpr = GetVideoRecv("http");
	iPixelFormatOfVideo = g_ptVideoRecvOpr->GetFormat();

	VideoConvertInit();
	ptVideoConvert = GetVideoConvertForFormats(iPixelFormatOfVideo, iPixelFormatOfDisp);
	if (NULL == ptVideoConvert)
	{
	    DBG_PRINTF("can not support this format convert\n");
	    return -1;
	}


	/* 启动摄像头设备 */
	if(g_ptVideoRecvOpr->Connect_To_Server(&iSocketClient, argv[1]) < 0)
	{		
		DBG_PRINTF("can not Connect_To_Server\n");
		return -1;
	}

	if(g_ptVideoRecvOpr->Init(&iSocketClient) < 0)
	{
		DBG_PRINTF("can not Init\n");
		return -1;
	}

	memset(&tVideoBuf, 0, sizeof(tVideoBuf));
	tVideoBuf.tPixelDatas.aucPixelDatas = malloc(30000);
	memset(&tConvertBuf, 0, sizeof(tConvertBuf));
	tConvertBuf.iPixelFormat     = iPixelFormatOfDisp;
	tConvertBuf.tPixelDatas.iBpp = iLcdBpp;
	if( pthread_mutex_init(&tVideoBuf.db, NULL) != 0 )		/* 初始化 global.db 成员 */
	{
		return -1;
	}
	if( pthread_cond_init(&tVideoBuf.db_update, NULL) != 0 )	/* 初始化 global.db_update(条件变量) 成员 */
	{
		DBG_PRINTF("could not initialize condition variable\n");
		return -1;
	}

	/* 创建获取摄像头数据的线程 */
	pthread_create(&RecvVideo_Id, NULL, &RecvVideoThread, &tVideoBuf);

	while (1)
	{
		pthread_cond_wait(&tVideoBuf.db_update, &tVideoBuf.db);
		ptVideoBufCur = &tVideoBuf;

		if (iPixelFormatOfVideo != iPixelFormatOfDisp)
		{
			/* 转换为RGB */
			iError = ptVideoConvert->Convert(&tVideoBuf, &tConvertBuf);
			DBG_PRINTF("Convert %s, ret = %d\n", ptVideoConvert->name, iError);
			if (iError)
			{
				DBG_PRINTF("Convert for %s error!\n", argv[1]);
				continue;
			}            
			ptVideoBufCur = &tConvertBuf;
		}		

		/* 合并进framebuffer */
		/* 接着算出居中显示时左上角坐标 */
		iTopLeftX = (iLcdWidth - ptVideoBufCur->tPixelDatas.iWidth) / 2;
		iTopLeftY = (iLcdHeigt - ptVideoBufCur->tPixelDatas.iHeight) / 2;

		PicMerge(iTopLeftX, iTopLeftY, &ptVideoBufCur->tPixelDatas, &tFrameBuf.tPixelDatas);

		FlushPixelDatasToDev(&tFrameBuf.tPixelDatas);

		/* 把framebuffer的数据刷到LCD上, 显示 */
	}

	pthread_detach(RecvVideo_Id);		// 等待线程结束,以便回收它的资源
	
	return 0;
}

