#include "mp3_file.h"

//播放标识
int first_play = 1;
int do_work = 0;

//子进程、孙子进程id
pid_t son_pid;
pid_t grandson_pid;

//共享内存
int shmid;
char *p_addr;


/*********************************************
*函数名称:Auto_play
*函数参数:歌曲链表头指针head
*返回值      :无
*函数功能:本函数用于子进程创建孙子进程
				在孙子进程中调用execlp函数来播放歌曲
				子进程等待孙子进程将当前歌曲播放完，
				在没有任何按键按下的情况下自动循环播放下一首。
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
		pid = fork();	//创建孙子进程

		if(pid < 0)
		{
			perror("create grandson fail\n");
			exit(1);
		}
		else if(pid == 0)	//孙子进程
		{
			strcat(my_song,song_tmp->name);
			song_len = strlen(my_song);
			//my_song[song_len-1] = '\0';	//将最后一个字符'\n'换成尾零，为了excel函数

			printf("This song is %s\n",song_tmp->name);
			execlp("madplay","madplay",my_song,NULL);
		}
		else	//子进程
		{
			//内存映射
			sh_addr = shmat(shmid,NULL,0);
			//把孙子进程的ID 号和当前播放的歌曲结点指针传入共享内存
			memcpy(sh_addr,&pid,sizeof(pid_t));
			memcpy(sh_addr+sizeof(pid_t),&song_tmp,4);

			//等待孙子进程把当前歌曲播放完，否则子进程将阻塞
			//当孙子进程播放一首后，没有按键按下，则自动循环播放
			if(pid == wait(NULL))
			{
				song_tmp = song_tmp->next;
				printf("The next song is %s\n",song_tmp->name);
			}
			
		}
			
			
	}
	
}


/*********************************************
*函数名称:Start_play_song
*函数参数:歌曲列表的头指针head
*返回值     :无
*函数功能:开始播放歌曲
				创建子进程
***********************************************/
void Start_play_song(song *head)
{
	pid_t pid;
	pid = fork();

	if(pid == 0)	//子进程
	{
		Auto_play(head);	//调用播放歌曲函数
	}
	else if(pid > 0)//父进程
	{
		son_pid = pid;
		do_work = 1;
		sleep(1);
		//在子进程中已经把孙子进程的ID号和当前播放歌曲的
		//歌曲结点存放到共享内存，将孙子进程id取出来
		memcpy(&grandson_pid,p_addr,sizeof(pid_t));
		
	}
	else
	{
		perror("creat son fail");
		exit(1);
	}
}

/*********************************************
*函数名称:Pause_song
*函数参数:进程ID号
*返回值      :空
*函数功能:给孙子进程发送暂停信号
***********************************************/
void Pause_song(pid_t pid)
{
	printf("\n==========PAUSE!==========\n");
	printf("PLASE PRESS k3 TO CONTINUE\n");

	kill(pid,SIGSTOP);
	do_work = 0;	
}

/*********************************************
*函数名称:Continue_play
*函数参数:进程ID号
*返回值		:空
*函数功能:给孙子进程发送继续信号
***********************************************/
void Continue_play(pid_t pid)
{
	printf("\n==========CONTINUE!========\n");
	
	kill(pid,SIGCONT);
	do_work = 1;
}

/*********************************************
*函数名称:Stop_play
*函数参数:进程ID号
*返回值		:空
*函数功能:停止播放歌曲
***********************************************/
void Stop_play(pid_t pid)
{
	printf("\n==========STOP!========\n");

	kill(pid,SIGKILL);		//杀死孙子进程
	kill(son_pid,SIGKILL);	//杀死子进程
	do_work = 0;
	first_play = 1;
}

/*********************************************
*函数名称:Next_song
*函数参数:进程的ID
*返回值		:空
*函数功能:下一曲
***********************************************/
void Next_song(pid_t pid)
{
	 song *nextsong;    
	 printf("\n=========NEXT MP3========\n");    
	 /*memcpy(&nextsong, p_addr+sizeof(pid_t)+1, 4);*/    
	 memcpy(&nextsong, p_addr+sizeof(pid_t), 4);    
	 nextsong = nextsong->next;
	 
	 kill(pid,SIGKILL);    //杀死孙子进程
	 kill(son_pid,SIGKILL);//杀死子进程

	 //等待两个进程都结束后从新创建子进程和孙子进程
	 wait(NULL);
	 Start_play_song(nextsong);
}

/*********************************************
*函数名称:Pre_song
*函数参数:进程的ID
*返回值		:空
*函数功能:上一曲
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


