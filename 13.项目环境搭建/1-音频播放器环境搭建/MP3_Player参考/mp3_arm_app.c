/*
*===============MP3 播放器==================
*在linux系统基于ARM9的MP3 播放器。
*功能:在没有按键控制下可实现歌曲的自动循环播放
		 在按键控制可实现以下功能。
*K1键:开始播放
*K2键:暂停
*K3键:继续
*K4键:停止
*K5键:下一曲
*K6键:上一曲
*/
#include "mp3_file.h"

int main(void)
{
	int btn_fd, ret, key_val;
	char mp3_pathname[128] = {0};
	song *mp3_head;

	//打开MP3控制按键的驱动设备
	btn_fd = open("/dev/my_buttons",O_RDWR);
	if(btn_fd < 0)
	{
		perror("open /dev/my_buttons fail");
		exit(1);
	}

	printf("============================MP3 Player=========================\n");
	
	//将MP3文件下的歌曲创建成双向循环链表
	strcpy(mp3_pathname,"/home/MP3");
	mp3_head = Linklist_create(mp3_pathname);
	//创建共享内存
	shmid = shmget(IPC_PRIVATE,1024,PERM);
	if(shmid < 0)
		exit(1);
	//映射到本进程(父进程)的寻址空间
	p_addr = shmat(shmid,NULL,0);
	memset(p_addr,0,1024);
	

	while(1)
	{
		ret = read(btn_fd,&key_val,4);

		if(ret != 0)
		{
			printf("read key value fail\n");
			continue;
		}

		if(first_play)
		{
			switch(key_val)
			{
				case 1:first_play = 0;Start_play_song(mp3_head);break;
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:printf("==========PLASE PRESS K1 TO START FIRST!=========\n");break;
				default:break;
			}
		}
		else
		{
			switch(key_val)
			{
				case 1:	continue;
				case 2:
						{
							if(do_work == 1)
								Pause_song(grandson_pid);
							break;
						}
				case 3:
						{printf("***********\n");
							if(do_work == 0)
								Continue_play(grandson_pid);
							break;
						}
				case 4: Stop_play(grandson_pid);break;
				case 5: Next_song(grandson_pid);break;
				case 6: Pre_song(grandson_pid);break;
				default:break;
			}
		}
	}
	
	return 0;
	
}
