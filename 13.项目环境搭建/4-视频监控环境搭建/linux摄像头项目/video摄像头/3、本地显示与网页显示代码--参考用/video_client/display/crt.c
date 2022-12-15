#include <config.h>
#include <disp_manager.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <string.h>
#include <vga.h>
#include <vgagl.h>

static GraphicsContext *physicalscreen;
static GraphicsContext *virtualscreen;

static int CRTDeviceInit(void);
static int CRTShowPixel(int iX, int iY, unsigned int dwColor);
static int CRTCleanScreen(unsigned int dwBackColor);
//static int CRTDeviceExit(void);
static int CRTShowPage(PT_PixelDatas ptPixelDatas);

static T_DispOpr g_tCRTOpr = {
	.name        = "crt",
	.DeviceInit  = CRTDeviceInit,
	//.DeviceExit  = CRTDeviceExit,
	.ShowPixel   = CRTShowPixel,
	.CleanScreen = CRTCleanScreen,
	.ShowPage    = CRTShowPage,
};

/* ��ʾģ���ʼ��:svga */
static int CRTDeviceInit(void)
{
    vga_init();
    vga_setmode(G640x480x64K);
    gl_setcontextvga(G640x480x64K);

    /* ���"������Ļ" */
    physicalscreen = gl_allocatecontext();
    gl_getcontext(physicalscreen);

    /* ���"������Ļ" */
    gl_setcontextvgavirtual(G640x480x64K);
    virtualscreen = gl_allocatecontext();
    gl_getcontext(virtualscreen);

    /* ����"������Ļ"Ϊ��ǰ��ʹ�õ�"��Ļ" */
    gl_setcontext(virtualscreen);
    
	g_tCRTOpr.iXres = 640;
	g_tCRTOpr.iYres = 480;
	g_tCRTOpr.iBpp  = 32; 

    g_tCRTOpr.iLineWidth = g_tCRTOpr.iXres * g_tCRTOpr.iBpp / 8;

    g_tCRTOpr.pucDispMem = malloc(g_tCRTOpr.iLineWidth * g_tCRTOpr.iYres);
        
	return 0;
}

#if 0
static int CRTDeviceExit(void)
{
	vga_setmode(TEXT);
	return 0;
}
#endif

static int CRTShowPixel(int iX, int iY, unsigned int dwColor)
{
	int iRed, iGreen, iBlue;
	
	iRed   = (dwColor >> 16) & 0xff;
	iGreen = (dwColor >> 8) & 0xff;
	iBlue  = (dwColor >> 0) & 0xff;

//	gl_setpalettecolor(5, iRed>>2, iGreen>>2, iBlue>>2);   /* 0xE7DBB5	*/ /* ���Ƶ�ֽ */
//	vga_setcolor(5);

//	vga_drawpixel(iX, iY);

    gl_setpixelrgb(iX, iY, iRed, iGreen, iBlue);

    gl_copyscreen(physicalscreen);

	return 0;
}


static int CRTCleanScreen(unsigned int dwBackColor)
{
	int iX;
	int iY;
	int iRed, iGreen, iBlue;
	
	iRed   = (dwBackColor >> 16) & 0xff;
	iGreen = (dwBackColor >> 8) & 0xff;
	iBlue  = (dwBackColor >> 0) & 0xff;

//	gl_setpalettecolor(4, iRed>>2, iGreen>>2, iBlue>>2);   /* 0xE7DBB5  */ /* ���Ƶ�ֽ */
//	vga_setcolor(4);

	for (iX = 0; iX < 320; iX++)
		for (iY = 0; iY < 200; iY++)
            gl_setpixelrgb(iX, iY, iRed, iGreen, iBlue);

    gl_copyscreen(physicalscreen);

	return 0;		
}
/* ��ʾ */
static int CRTShowPage(PT_PixelDatas ptPixelDatas)
{
    int x, y;
    unsigned int *pdwColor = (unsigned int *)ptPixelDatas->aucPixelDatas;
    unsigned int dwColor;
    unsigned int dwRed, dwGreen, dwBlue;
    
    if (ptPixelDatas->iBpp != 32)
    {
        return -1;
    }
    
    for (y = 0; y < g_tCRTOpr.iYres; y++)
    {
        for (x = 0; x < g_tCRTOpr.iXres; x++)
        {
            /* 0x00RRGGBB */
            dwColor = *pdwColor++;
            dwRed   = (dwColor >> 16) & 0xff;
            dwGreen = (dwColor >> 8) & 0xff;
            dwBlue  = (dwColor >> 0) & 0xff;
            
            // CRTShowPixel(x, y, dwColor);
            gl_setpixelrgb(x, y, dwRed, dwGreen, dwBlue);
        }
    }

    gl_copyscreen(physicalscreen);
    
    return 0;
}


int CRTInit(void)
{
	return RegisterDispOpr(&g_tCRTOpr);
}

