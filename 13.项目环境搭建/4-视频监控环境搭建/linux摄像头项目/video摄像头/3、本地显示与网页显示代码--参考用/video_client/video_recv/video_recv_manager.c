
#include <config.h>
#include <video_recv_manager.h>
#include <string.h>

static PT_VideoRecv g_ptVideoRecvHead = NULL;


int RegisterVideoRecv(PT_VideoRecv ptVideoRecv)
{
	PT_VideoRecv ptTmp;

	if (!g_ptVideoRecvHead)
	{
		g_ptVideoRecvHead   = ptVideoRecv;
		ptVideoRecv->ptNext = NULL;
	}
	else
	{
		ptTmp = g_ptVideoRecvHead;
		while (ptTmp->ptNext)
		{
			ptTmp = ptTmp->ptNext;
		}
		ptTmp->ptNext     = ptVideoRecv;
		ptVideoRecv->ptNext = NULL;
	}

	return 0;
}

void ShowVideoRecv(void)
{
	int i = 0;
	PT_VideoRecv ptTmp = g_ptVideoRecvHead;

	while (ptTmp)
	{
		printf("%02d %s\n", i++, ptTmp->name);
		ptTmp = ptTmp->ptNext;
	}
}

PT_VideoRecv GetVideoRecv(char *pcName)
{
	PT_VideoRecv ptTmp = g_ptVideoRecvHead;
	
	while (ptTmp)
	{
		if (strcmp(ptTmp->name, pcName) == 0)
		{
			return ptTmp;
		}
		ptTmp = ptTmp->ptNext;
	}
	return NULL;
}

int VideoRecvInit(void)
{
	int iError;

    iError = Video_Recv_Init();

	return iError;
}




