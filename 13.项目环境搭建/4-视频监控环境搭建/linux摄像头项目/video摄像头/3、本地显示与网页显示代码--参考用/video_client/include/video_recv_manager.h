
#ifndef _VIDEO_RECV_MANAGER_H
#define _VIDEO_RECV_MANAGER_H

#include <config.h>
#include <pic_operation.h>
#include <linux/videodev2.h>
#include <pthread.h>

typedef struct VideoBuf {
    T_PixelDatas tPixelDatas;
    int iPixelFormat;
  /* signal fresh frames */
  pthread_mutex_t db;
  pthread_cond_t  db_update;
}T_VideoBuf, *PT_VideoBuf;

typedef struct VideoRecv {
    char *name;
	
    int (*Connect_To_Server)(int *SocketClient, const char *ip);
    int (*DisConnect_To_Server)(int *SocketClient);
    int (*Init)(int *SocketClient);
    int (*GetFormat)(void);
    int (*Get_Video)(int *SocketClient, PT_VideoBuf ptVideoBuf);	
    struct VideoRecv *ptNext;
}T_VideoRecv, *PT_VideoRecv;

int VideoRecvInit(void);
void ShowVideoRecv(void);
int RegisterVideoRecv(PT_VideoRecv ptVideoRecv);
int Video_Recv_Init(void);
PT_VideoRecv GetVideoRecv(char *pcName);

#endif

