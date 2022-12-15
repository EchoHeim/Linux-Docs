#ifndef _DISP_MANAGER_H
#define _DISP_MANAGER_H

#include <pic_operation.h>
#include <video_recv_manager.h>

/* ��ʾ����,������������Ͻ�/���½�����
 * �����ͼ��,������ͼ����ļ���
 */
typedef struct Layout {
	int iTopLeftX;
	int iTopLeftY;
	int iBotRightX;
	int iBotRightY;
	char *strIconName;
}T_Layout, *PT_Layout;


/* VideoMem��״̬:
 * ����/����Ԥ��׼����ʾ����/���ڵ�ǰ�߳�
 */
typedef enum {
	VMS_FREE = 0,
	VMS_USED_FOR_PREPARE,
	VMS_USED_FOR_CUR,	
}E_VideoMemState;

/* VideoMem���ڴ���ͼƬ��״̬:
 * �հ�/��������/�Ѿ�����
 */
typedef enum {
	PS_BLANK = 0,
	PS_GENERATING,
	PS_GENERATED,	
}E_PicState;


typedef struct VideoMem {
	int iID;                        /* IDֵ,���ڱ�ʶ��ͬ��ҳ�� */
	int bDevFrameBuffer;            /* 1: ���VideoMem����ʾ�豸���Դ�; 0: ֻ��һ����ͨ���� */
	E_VideoMemState eVideoMemState; /* ���VideoMem��״̬ */
	E_PicState ePicState;           /* VideoMem���ڴ���ͼƬ��״̬ */
	T_PixelDatas tPixelDatas;       /* �ڴ�: �����洢ͼ�� */
	struct VideoMem *ptNext;        /* ���� */
}T_VideoMem, *PT_VideoMem;

typedef struct DispOpr {
	char *name;              /* ��ʾģ������� */
	int iXres;               /* X�ֱ��� */
	int iYres;               /* Y�ֱ��� */
	int iBpp;                /* һ�������ö���λ����ʾ */
	int iLineWidth;          /* һ������ռ�ݶ����ֽ� */
	unsigned char *pucDispMem;   /* �Դ��ַ */
	int (*DeviceInit)(void);     /* �豸��ʼ������ */
	int (*ShowPixel)(int iPenX, int iPenY, unsigned int dwColor);    /* ��ָ�������������Ϊĳ��ɫ */
	int (*CleanScreen)(unsigned int dwBackColor);                    /* ����Ϊĳ��ɫ */
	int (*ShowPage)(PT_PixelDatas ptPixelDatas);                         /* ��ʾһҳ,����Դ��ptVideoMem */
	struct DispOpr *ptNext;      /* ���� */
}T_DispOpr, *PT_DispOpr;


int RegisterDispOpr(PT_DispOpr ptDispOpr);

void ShowDispOpr(void);

int DisplayInit(void);

void SelectAndInitDefaultDispDev(char *name);

int GetDispResolution(int *piXres, int *piYres, int *piBpp);
int AllocVideoMem(int iNum);


PT_VideoMem GetDevVideoMem(void);

PT_VideoMem GetVideoMem(int iID, int bCur);

void PutVideoMem(PT_VideoMem ptVideoMem);

void ClearVideoMem(PT_VideoMem ptVideoMem, unsigned int dwColor);


void ClearVideoMemRegion(PT_VideoMem ptVideoMem, PT_Layout ptLayout, unsigned int dwColor);

int FBInit(void);

int CRTInit(void);

int GetVideoBufForDisplay(PT_VideoBuf ptFrameBuf);
void FlushPixelDatasToDev(PT_PixelDatas ptPixelDatas);

#endif /* _DISP_MANAGER_H */

