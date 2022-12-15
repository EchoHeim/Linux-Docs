#include "mp3_file.h"

//���ű�ʶ
int first_play = 1;
int do_work = 0;

//�ӽ��̡����ӽ���id
pid_t son_pid;
pid_t grandson_pid;

//�����ڴ�
int shmid;
char *p_addr;


/*********************************************
*��������:Auto_play
*��������:��������ͷָ��head
*����ֵ      :��
*��������:�����������ӽ��̴������ӽ���
				�����ӽ����е���execlp���������Ÿ���
				�ӽ��̵ȴ����ӽ��̽���ǰ���������꣬
				��û���κΰ������µ�������Զ�ѭ��������һ�ס�
***********************************************/
void  Auto_play(song *head)
{
	pid_t pid;
	int song_len;
	char *sh_addr;
	song *song_tmp;
	char my_song[128] = {"/home/MP3/"};

	song_tmp = head;

	while(song_tmp)
	{
		pid = fork();	//�������ӽ���

		if(pid < 0)
		{
			perror("create grandson fail\n");
			exit(1);
		}
		else if(pid == 0)	//���ӽ���
		{
			strcat(my_song,song_tmp->name);
			song_len = strlen(my_song);
			//my_song[song_len-1] = '\0';	//�����һ���ַ�'\n'����β�㣬Ϊ��excel����

			printf("This song is %s\n",song_tmp->name);
			execlp("madplay","madplay",my_song,NULL);
		}
		else	//�ӽ���
		{
			//�ڴ�ӳ��
			sh_addr = shmat(shmid,NULL,0);
			//�����ӽ��̵�ID �ź͵�ǰ���ŵĸ������ָ�봫�빲���ڴ�
			memcpy(sh_addr,&pid,sizeof(pid_t));
			memcpy(sh_addr+sizeof(pid_t),&song_tmp,4);

			//�ȴ����ӽ��̰ѵ�ǰ���������꣬�����ӽ��̽�����
			//�����ӽ��̲���һ�׺�û�а������£����Զ�ѭ������
			if(pid == wait(NULL))
			{
				song_tmp = song_tmp->next;
				printf("The next song is %s\n",song_tmp->name);
			}
			
		}
			
			
	}
	
}


/*********************************************
*��������:Start_play_song
*��������:�����б��ͷָ��head
*����ֵ     :��
*��������:��ʼ���Ÿ���
				�����ӽ���
***********************************************/
void Start_play_song(song *head)
{
	pid_t pid;
	pid = fork();

	if(pid == 0)	//�ӽ���
	{
		Auto_play(head);	//���ò��Ÿ�������
	}
	else if(pid > 0)//������
	{
		son_pid = pid;
		do_work = 1;
		sleep(1);
		//���ӽ������Ѿ������ӽ��̵�ID�ź͵�ǰ���Ÿ�����
		//��������ŵ������ڴ棬�����ӽ���idȡ����
		memcpy(&grandson_pid,p_addr,sizeof(pid_t));
		
	}
	else
	{
		perror("creat son fail");
		exit(1);
	}
}

/*********************************************
*��������:Pause_song
*��������:����ID��
*����ֵ      :��
*��������:�����ӽ��̷�����ͣ�ź�
***********************************************/
void Pause_song(pid_t pid)
{
	printf("\n==========PAUSE!==========\n");
	printf("PLASE PRESS k3 TO CONTINUE\n");

	kill(pid,SIGSTOP);
	do_work = 0;	
}

/*********************************************
*��������:Continue_play
*��������:����ID��
*����ֵ		:��
*��������:�����ӽ��̷��ͼ����ź�
***********************************************/
void Continue_play(pid_t pid)
{
	printf("\n==========CONTINUE!========\n");
	
	kill(pid,SIGCONT);
	do_work = 1;
}

/*********************************************
*��������:Stop_play
*��������:����ID��
*����ֵ		:��
*��������:ֹͣ���Ÿ���
***********************************************/
void Stop_play(pid_t pid)
{
	printf("\n==========STOP!========\n");

	kill(pid,SIGKILL);		//ɱ�����ӽ���
	kill(son_pid,SIGKILL);	//ɱ���ӽ���
	do_work = 0;
	first_play = 1;
}

/*********************************************
*��������:Next_song
*��������:���̵�ID
*����ֵ		:��
*��������:��һ��
***********************************************/
void Next_song(pid_t pid)
{
	 song *nextsong;    
	 printf("\n=========NEXT MP3========\n");    
	 /*memcpy(&nextsong, p_addr+sizeof(pid_t)+1, 4);*/    
	 memcpy(&nextsong, p_addr+sizeof(pid_t), 4);    
	 nextsong = nextsong->next;
	 
	 kill(pid,SIGKILL);    //ɱ�����ӽ���
	 kill(son_pid,SIGKILL);//ɱ���ӽ���

	 //�ȴ��������̶���������´����ӽ��̺����ӽ���
	 wait(NULL);
	 Start_play_song(nextsong);
}

/*********************************************
*��������:Pre_song
*��������:���̵�ID
*����ֵ		:��
*��������:��һ��
***********************************************/
void Pre_song(pid_t pid)
{
	song *prevsong;    
	printf("\n===========PREV MP3==========\n");    
	/*memcpy(&prevsong, p_addr+sizeof(pid_t)+1, 4);*/    
	memcpy(&prevsong, p_addr+sizeof(pid_t), 4);    
	prevsong = prevsong->prev;    

	kill(pid,SIGKILL);    
	kill(son_pid,SIGKILL);    
	wait(NULL);    
	Start_play_song(prevsong);
}


