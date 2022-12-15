#include <stdio.h>
#include <unistd.h>
#include <linux/fb.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include "lcd.h"
#include <sys/ioctl.h>
#include <linux/input.h>
#include <linux/string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "mp3_linklist.h"
#include "mp3_play.h"

#define S_IRUSR 00400
#define S_IWUSR 00200

#define MAIN_VIEW	1
#define TEMP_DAMP 	2
#define MP3			3
#define ENVIR		4
#define PROTECT		5
#define SETTING		6
#define TEMP_ADD  	7
#define TEMP_SUB	8
#define DAMP_ADD	9
#define DAMP_SUB	10
#define MP3_LAST	11
#define MP3_PAUSE	12
#define MP3_CONT 	13
#define MP3_PLAY 	14
#define MP3_STOP  	15
#define MP3_NEXT  	16

#define u32 unsigned int 
#define u16 unsigned short 
#define u8 unsigned char

typedef struct FlagTag
{
	unsigned char mainview;
	unsigned char temp_damp;
	unsigned char mp3;
	unsigned char envir;
	unsigned char protect;
	unsigned char setting;
}FLAG;
typedef struct PidTag
{
	int mp3;
	int temp_damp;
	int envior;
	int protect;
	int setting;
}PID;
typedef struct TouchTag
{
	int x;						//触摸坐标
	int y;
	unsigned char value;		//触摸坐标对应的键值
	unsigned char press;		//触摸是否松开
} TOUCH;

typedef struct MiscTag
{
	unsigned char pretemp;
	unsigned char predamp;
	unsigned char curtemp;
	unsigned char curdamp;
	//char tel[12];
	//char passwd[7];
} MISCDATA;

typedef struct ShnumTag
{
	int touch;
	int flag;
	int pid;
	int miscdata;
}SHNUM;
typedef struct KeyTag
{
	int touch;
	int flag;
	int pid;
	int miscdata;
}KEY;


void Mp3_playing(unsigned char key,song *mp3_head);
void Temp_Damp_pic(u16 x ,u16 y ,u32 color , u8 temp , u8 damp);
void Key_PicAndNum_create(u16 x, u16 y);
int main()
{	
	SHNUM shnum;
	KEY key;
	
	TOUCH *ptouch_xy=NULL;
	FLAG *myflag=NULL;
	PID *savepid=NULL;
	MISCDATA *pdata=NULL;
		
	int fd;
	int pid_main=0,pid_view=0,pid_mp3=0,pid_temp_damp=0,pid_envir=0,pid_protect=0,pid_setting=0;
	int status=0;
	struct input_event ev_key;	
	
	FB_init (); 				  		 //初始化帧缓冲设备
	fd = open("/dev/input/event0", 0);  //打开event0设备(触摸屏)
	if (fd < 0)
	{
		perror("open device key!");
		exit(1);
	}
			   
	key.touch=ftok(".",10);
	shnum.touch=shmget(key.touch,sizeof(struct TouchTag),IPC_CREAT);
	ptouch_xy=(TOUCH *)shmat(shnum.touch,NULL,0);
	memset(ptouch_xy,0,sizeof(struct TouchTag));

	key.flag=ftok(".",11);
	shnum.flag=shmget(key.flag,sizeof(struct FlagTag),IPC_CREAT);
	myflag=(FLAG *)shmat(shnum.flag,NULL,0);
	memset(myflag,0,sizeof(struct FlagTag));
	myflag->mainview=1;

	key.pid=ftok(".",12);
	shnum.pid=shmget(key.pid,sizeof(struct PidTag),IPC_CREAT);
	savepid=(PID *)shmat(shnum.pid,NULL,0);
	memset(savepid,0,sizeof(struct PidTag));

	key.miscdata=ftok(".",13);
	shnum.miscdata=shmget(key.miscdata,sizeof(struct MiscTag),IPC_CREAT);
	pdata=(MISCDATA *)shmat(shnum.miscdata,NULL,0);
	memset(pdata,0,sizeof(struct MiscTag));
	pdata->curtemp=16;pdata->curdamp=80;pdata->pretemp=32;pdata->predamp=50;
	
  	pid_main=fork();
	if(pid_main==0)
   	{
   		printf("触摸屏进程pid = %d 父进程pid = %d \n",getpid(),getppid());
		while (1)
		{			
			printf("touchvalue = %d\r\n",ptouch_xy->value);
			printf("mainview= %d  temp = %d mp3 = %d\r\n",myflag->mainview,myflag->temp_damp,myflag->mp3);
			if(ptouch_xy->press!=200)
			{
				memset(ptouch_xy,0,sizeof(struct TouchTag));
			}
			read(fd, &ev_key, sizeof(struct input_event));
	        if (EV_ABS == ev_key.type) 
			{
				switch(ev_key.code)
				{
					case ABS_X:
			          //  ptouch_xy->x= ev_key.value;		
						break;					
					case ABS_Y:
			          //  ptouch_xy->y= ev_key.value;			
						break;	
					case ABS_PRESSURE:
					 //	ptouch_xy->press=ev_key.value;
						break;
					default:printf("unknow code !\r\n");
				}
				if(myflag->mainview==1)
				{
					if(ptouch_xy->y>175&&ptouch_xy->y<280)
					{
						if(ptouch_xy->x>70&&ptouch_xy->x<170)
							ptouch_xy->value=TEMP_DAMP;
						else if(ptouch_xy->x>207&&ptouch_xy->x<307)
							ptouch_xy->value=MP3;
						else if(ptouch_xy->x>350&&ptouch_xy->x<450)
							ptouch_xy->value=ENVIR;
						else if(ptouch_xy->x>490&&ptouch_xy->x<590)
							ptouch_xy->value=PROTECT;
						else if(ptouch_xy->x>632&&ptouch_xy->x<732)
							ptouch_xy->value=SETTING;
					}
				}
				else if(myflag->mp3==1)
				{
					if(ptouch_xy->y>290&&ptouch_xy->y<340)
					{
						if(ptouch_xy->x>150&&ptouch_xy->x<200)
							ptouch_xy->value=MP3_LAST;
						else if(ptouch_xy->x>220&&ptouch_xy->x<270)
							ptouch_xy->value=MP3_PAUSE;
						else if(ptouch_xy->x>290&&ptouch_xy->x<340)
							ptouch_xy->value=MP3_PLAY;
						else if(ptouch_xy->x>365&&ptouch_xy->x<415)
							ptouch_xy->value=MP3_STOP;
						else if(ptouch_xy->x>440&&ptouch_xy->x<490)
							ptouch_xy->value=MP3_NEXT;
					}
				}
				else if(myflag->temp_damp==1)
				{
					if(ptouch_xy->x>70&&ptouch_xy->x<120)
					{
						if(ptouch_xy->y>105&&ptouch_xy->y<155)
							ptouch_xy->value=TEMP_ADD;
						else if(ptouch_xy->y>195&&ptouch_xy->y<245)
							ptouch_xy->value=TEMP_SUB;
					}
					else if(ptouch_xy->x>515&&ptouch_xy->x<565)
					{
						if(ptouch_xy->y>105&&ptouch_xy->y<155)
							ptouch_xy->value=DAMP_ADD;
						else if(ptouch_xy->y>195&&ptouch_xy->y<245)
							ptouch_xy->value=DAMP_SUB;
					}
				}
				if(myflag->mainview!=1)
				{
					if(ptouch_xy->x>665&&ptouch_xy->x<705&&ptouch_xy->y>5&&ptouch_xy->y<50)
						ptouch_xy->value=MAIN_VIEW;
					else if(ptouch_xy->x>665&&ptouch_xy->x<720)
					{
						if(ptouch_xy->y>85&&ptouch_xy->y<140)
							ptouch_xy->value=TEMP_DAMP;
						else if(ptouch_xy->y>170&&ptouch_xy->y<220)
							ptouch_xy->value=ENVIR;
						else if(ptouch_xy->y>245&&ptouch_xy->y<300)
							ptouch_xy->value=SETTING;
					}
					else if(ptouch_xy->x>730&&ptouch_xy->x<785)
					{
						if(ptouch_xy->y>85&&ptouch_xy->y<140)
							ptouch_xy->value=MP3;
						else if(ptouch_xy->y>170&&ptouch_xy->y<220)
							ptouch_xy->value=PROTECT;
					}
				}
			}
		}
   }
   if(pid_main>0)
   {
		Show_bmp(0,0,"mainview.bmp");	
		printf("起始进程pid = %d ，父进程pid = %d \n",getpid(),getppid());
		while(1)
		{
			if(ptouch_xy->value==MP3&&myflag->mp3!=1)
			{
				memset(myflag,0,sizeof(struct FlagTag));
				myflag->mp3=1;
				pid_mp3=fork();
				if(pid_mp3==0)
				{
					Show_bmp(0,0,"musicview.bmp");
					
					printf("音乐进程pid = %d 父进程pid = %d \n",getpid(),getppid());
					char mp3_pathname[128] = {0};
					song *mp3_head;				
				 	strcpy(mp3_pathname,"mp3/");
				 	mp3_head = Linklist_create(mp3_pathname);
					shmid = shmget(IPC_PRIVATE,1024,S_IRUSR|S_IWUSR);
				    if(shmid < 0)
					   exit(1);
				   //映射到本进程(父进程)的寻址空间
				    p_addr = shmat(shmid,NULL,0);
				    memset(p_addr,0,1024);
					while(1)
					{
						if(ptouch_xy->value>=MAIN_VIEW&&ptouch_xy->value<=SETTING)
						{
							memset(myflag,0,sizeof(struct FlagTag));
							if(ptouch_xy->value==MAIN_VIEW)
							{
								myflag->mainview=1;
								Show_bmp(0,0,"mainview.bmp"); 
							}
							if(first_play==0)
								Stop_play(grandson_pid);
							kill(getpid(),SIGKILL);
							break;
						}
						else
						{
							Mp3_playing(ptouch_xy->value,mp3_head);
						}
					}
				}				
				else if(pid_mp3<0)
				{
					printf("mp3进程创建失败!\r\n");
					return -1;
				}
				else
				{
					savepid->mp3=pid_mp3;
				}
			}
			if(ptouch_xy->value==TEMP_DAMP&&myflag->temp_damp!=1)
			{
				memset(myflag,0,sizeof(struct FlagTag));
				myflag->temp_damp=1;
				pid_temp_damp=fork();
				if(pid_temp_damp==0)
				{
					unsigned char ttemp=0,tdamp=0;
					Show_bmp(0,0,"temp_damp.bmp");		
					Show_str(210,110,NONE,BLACK,"预设温度",16,16);
					Show_str(242,130,NONE,WHITE,"℃",32,32);
					Show_str(210,200,NONE,BLACK,"预设湿度",16,16);
					Show_str(242,220,NONE,WHITE," %",32,32);		
					
					Show_str(320,115,NONE,BLACK,"当前温度",16,16);
					Show_str(352,135,NONE,WHITE,"℃",32,32);
					Show_str(415,115,NONE,BLACK,"当前湿度",16,16);
					Show_str(447,135,NONE,WHITE," %",32,32);	
					
					Show_str(70,160,NONE,WHITE,"温度加",16,16);
					Show_str(70,250,NONE,WHITE,"温度减",16,16);
					Show_str(520,160,NONE,WHITE,"湿度加",16,16);
					Show_str(520,250,NONE,WHITE,"湿度减",16,16);
					Show_num(210,130,BLUE,WHITE,pdata->pretemp,2,32,32);	//预设温度值
					Show_num(210,220,BLUE,WHITE,pdata->predamp,2,32,32);	//预设湿度值
					Show_num(320,135,BLUE,WHITE,pdata->curtemp,2,32,32);	//当前温度值
					Show_num(415,135,BLUE,WHITE,pdata->curdamp,2,32,32);	//当前湿度值							
					Temp_Damp_pic(375,190,BLUE,pdata->curtemp,pdata->curdamp);
					
					printf("温湿度进程pid = %d 父进程pid = %d \n",getpid(),getppid());					
					while(1)
					{
						if(ptouch_xy->value>=MAIN_VIEW&&ptouch_xy->value<=SETTING)
						{
							memset(myflag,0,sizeof(struct FlagTag));
							if(ptouch_xy->value==MAIN_VIEW)
							{
								myflag->mainview=1;
								Show_bmp(0,0,"mainview.bmp"); 
							}
							kill(getpid(),SIGKILL);
							break;
						}
						if(ttemp!=pdata->curtemp||tdamp!=pdata->curdamp)
						{
							ttemp=pdata->curtemp;
							tdamp=pdata->curdamp;
							Show_num(320,135,BLUE,WHITE,pdata->curtemp,2,32,32);	//当前温度值
							Show_num(415,135,BLUE,WHITE,pdata->curdamp,2,32,32);	//当前湿度值							
							Temp_Damp_pic(375,190,BLUE,pdata->curtemp,pdata->curdamp);
						}
						if(ptouch_xy->value>=TEMP_ADD&&ptouch_xy->value<=DAMP_SUB)
						{
							switch(ptouch_xy->value)
							{
								case TEMP_ADD: if(pdata->curtemp<50)pdata->pretemp+=1;break;
								case TEMP_SUB: if(pdata->curtemp>0)pdata->pretemp-=1;break;
								case DAMP_ADD: if(pdata->curdamp<90)pdata->predamp+=1;break;
								case DAMP_SUB: if(pdata->curdamp>20)pdata->predamp-=1;break;
								default:break;
							}						
							Show_num(210,130,BLUE,WHITE,pdata->pretemp,2,32,32);	//预设温度值
							Show_num(210,220,BLUE,WHITE,pdata->predamp,2,32,32);	//预设湿度值
							while(ptouch_xy->value!=0);
						}
					}
				}				
				else if(pid_temp_damp<0)
				{
					printf("温湿度进程创建失败!\r\n");
					return -1;
				}
				else
				{
					savepid->temp_damp=pid_temp_damp;
				}
			}
			if(ptouch_xy->value==ENVIR&&myflag->envir!=1)
			{
				memset(myflag,0,sizeof(struct FlagTag));
				myflag->envir=1;
				pid_envir=fork();
				if(pid_envir==0)
				{
					printf("环境监测进程pid = %d 父进程pid = %d \n",getpid(),getppid());
					Show_bmp(0,0,"all.bmp");
					while(1)
					{
						if(ptouch_xy->value>=MAIN_VIEW&&ptouch_xy->value<=SETTING)
						{
							memset(myflag,0,sizeof(struct FlagTag));
							if(ptouch_xy->value==MAIN_VIEW)
							{
								myflag->mainview=1;
								Show_bmp(0,0,"mainview.bmp"); 
							}
							kill(getpid(),SIGKILL);
							break;
						}
						
					}
				}				
				else if(pid_envir<0)
				{
					printf("环境检测进程创建失败!\r\n");
					return -1;
				}
				else
				{
					savepid->envior=pid_envir;
				}
			}
			if(ptouch_xy->value==PROTECT&&myflag->protect!=1)
			{
				memset(myflag,0,sizeof(struct FlagTag));
				myflag->protect=1;
				pid_protect=fork();
				if(pid_protect==0)
				{
					printf("安防进程pid = %d 父进程pid = %d \n",getpid(),getppid());
					Show_bmp(0,0,"all.bmp");
					while(1)
					{
						if(ptouch_xy->value>=MAIN_VIEW&&ptouch_xy->value<=SETTING)
						{
							memset(myflag,0,sizeof(struct FlagTag));
							if(ptouch_xy->value==MAIN_VIEW)
							{
								myflag->mainview=1;
								Show_bmp(0,0,"mainview.bmp"); 
							}
							kill(getpid(),SIGKILL);
							break;
						}
						
					}
				}				
				else if(pid_protect<0)
				{
					printf("安防进程创建失败!\r\n");
					return -1;
				}
				else
				{
					savepid->protect=pid_protect;
				}
			}
			if(ptouch_xy->value==SETTING&&myflag->setting!=1)
			{
				memset(myflag,0,sizeof(struct FlagTag));
				myflag->setting=1;
				pid_setting=fork();
				if(pid_setting==0)
				{
					printf("设置进程pid = %d 父进程pid = %d \n",getpid(),getppid());
					Show_bmp(0,0,"all.bmp");
					Key_PicAndNum_create(70,70);
					while(1)
					{
						if(ptouch_xy->value>=MAIN_VIEW&&ptouch_xy->value<=SETTING)
						{
							memset(myflag,0,sizeof(struct FlagTag));
							if(ptouch_xy->value==MAIN_VIEW)
							{
								myflag->mainview=1;
								Show_bmp(0,0,"mainview.bmp"); 
							}
							kill(getpid(),SIGKILL);
							break;
						}
						
					}
				}				
				else if(pid_setting<0)
				{
					printf("设置进程创建失败!\r\n");
					return -1;
				}
				else
				{
					savepid->setting=pid_setting;
				}
			}
			while(ptouch_xy->press!=0);
		}
		waitpid(-1,&status,0);	
   	}
   if(pid_main<0)
   {
  		 printf("process create is failed!");
   }
	shmdt(ptouch_xy);
	shmdt(myflag);
	shmdt(savepid);
	close(fd);
	FB_close();						//关闭帧缓冲设备
	printf("\n\nCLOSE!\n\n");
	return 0;
   
}

void Mp3_playing(unsigned char key,song *mp3_head)
{
	if(first_play)
   {	
	   switch(key)
	   {
		   case MP3_PLAY:first_play = 0;Start_play_song(mp3_head);break;
		   case MP3_LAST:
		   case MP3_PAUSE:
		   case MP3_CONT: 
		   case MP3_NEXT:
		   case MP3_STOP:break;
		   default:break;
	   }
   }
	else
   {	
	   switch(key)
	   {
		   case MP3_PLAY: break;
		   case MP3_PAUSE:
				   {
					   if(do_work == 1)
						   Pause_song(grandson_pid);
					   else
						   Continue_play(grandson_pid); 	
					  break;
				   }
		   case MP3_STOP: Stop_play(grandson_pid);break;
		   case MP3_NEXT: Next_song(grandson_pid);break;
		   case MP3_LAST: Pre_song(grandson_pid);break;
		   default:break;
	   }
	}
}


void Temp_Damp_pic(u16 x ,u16 y ,u32 color , u8 temp , u8 damp)
{
	GUI_CircleFill(x+5,y,5,color,color);
	GUI_RectangleFill(x,y,x+10,y+40,color,color);
	GUI_CircleFill(x+35,y,5,color,color);
	GUI_RectangleFill(x+30,y,x+40,y+40,color,color);
	GUI_CircleFill(x+5,y+40,5,color,color);
	GUI_CircleFill(x+35,y+40,5,color,color);
	if(temp!=0)
	{
		GUI_CircleFill(x+5,y+40,4,RED,RED);
		GUI_RectangleFill(x+1,y+((100-temp)*40/100),x+9,y+40,RED,RED);
	}
	if(damp!=0)
	{
		GUI_CircleFill(x+35,y+40,4,GREEN,GREEN);
		GUI_RectangleFill(x+31,y+((100-damp)*40/100),x+39,y+40,GREEN,GREEN);
	}
	Show_str(x-2,y+55,NONE,color,"温湿度",16,16);
}

void Key_PicAndNum_create(u16 x, u16 y)
{
	int i=0,j=0;
	int key_num[]={1,2,3,4,5,6,7,8,9,0};
	GUI_Rectangle(0+x,10+y,239+x,70+y,GREEN);
	GUI_Rectangle(5+x,15+y,234+x,65+y,BLUE);

	for(j=0;j<4;j++)
	{
		for(i=0;i<3;i++)
		{
			GUI_RectangleFill(x+2+i*78,y+82+j*59,x+78+i*78,y+138+j*59,BLACK,GREEN);
			if(j==3&&i>0)
			{
			}
			else
			{
				Show_num(x+30+i*80,y+95+j*59,NONE,BLACK,key_num[i+3*j],1,32,32);	
			}
		}
	}
}

