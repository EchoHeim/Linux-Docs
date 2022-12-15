/*
*===============MP3 ������==================
*��linuxϵͳ����ARM9��MP3 ��������
*����:��û�а��������¿�ʵ�ָ������Զ�ѭ������
		 �ڰ������ƿ�ʵ�����¹��ܡ�
*K1��:��ʼ����
*K2��:��ͣ
*K3��:����
*K4��:ֹͣ
*K5��:��һ��
*K6��:��һ��
*/
#include "mp3_file.h"

int main(void)
{
	int btn_fd, ret, key_val;
	char mp3_pathname[128] = {0};
	song *mp3_head;

	//��MP3���ư����������豸
	btn_fd = open("/dev/my_buttons",O_RDWR);
	if(btn_fd < 0)
	{
		perror("open /dev/my_buttons fail");
		exit(1);
	}

	printf("============================MP3 Player=========================\n");
	
	//��MP3�ļ��µĸ���������˫��ѭ������
	strcpy(mp3_pathname,"/home/MP3");
	mp3_head = Linklist_create(mp3_pathname);
	//���������ڴ�
	shmid = shmget(IPC_PRIVATE,1024,PERM);
	if(shmid < 0)
		exit(1);
	//ӳ�䵽������(������)��Ѱַ�ռ�
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
