#include "mp3_file.h"



song * Linklist_create(char *path_name)
{    
	DIR *dp = NULL;
	char filename[128] = {0};
	struct dirent *den = NULL;    
	song *head = NULL;    
	song *new = NULL;
	song *tail = NULL;
        
	dp = opendir(path_name);   
	printf("path=%s\n",path_name);
	if(NULL == dp)    
	{        
		perror("opendir");        
		exit(0);    
	}    
	while((den = readdir(dp)) != NULL)    
	{
		strcpy(filename,den->d_name);
		if(strlen(filename) < 4)
		{
			memset(filename,0,sizeof(filename));
			continue;
		}

		if((strcmp(filename + (strlen(filename)-4),".mp3")) != 0)
		{
			memset(filename,0,sizeof(filename));
			continue;
		}
		      
		new = malloc(sizeof(song));        
		memcpy(new->name, den->d_name, strlen(den->d_name) + 1);        
		if(head == NULL)        
		{            
			new->next = new;            
			new->prev = new;            
			head = new;        
		}        
		else        
		{            
			new->next = head;            
			new->prev = head->prev;            
			head->prev->next = new;            
			head->prev  = new;        
		}   
	} 

	//��������
	printf("*************Song List**************\n");
	for(tail = head; tail->next != head; tail = tail->next)    
	{        
		printf("%s\n",tail->name);    
	}    
	printf("%s\n",tail->name);
	printf("===============================================================\n");
	closedir(dp);    

	return head;
}



/*
�������ܣ�����һ�����
����������head����ȷ������һ������name��Ҫ���ҵĽ��
��������ֵ���ɹ�����0��ʧ�ܷ���-1
*/
int Linklist_find(song *head, char *name)
{        
	song *tail = NULL;

	tail = head;
	 
	//���ж������Ƿ�Ϊ��
	if(tail == NULL)
	{
		return -1;
	}
	
	//��ʼ����
	while(tail->next != head)
	{
		if(strcmp(tail->name,name) == 0)
		{
			return 0;
		}
		else
			tail = tail->next;
	}

	if(strcmp(tail->name,name) == 0)
		return 0;
	else
		return -1;
}

/*
�������ܣ�ɾ��һ�����
����������head��ʾ����һ������name��Ҫɾ���Ľ��
��������ֵ��ɾ���ɹ�����0��ɾ��ʧ�ܷ��أ�1
*/
/*
int Linklist_del(node_t *head, char *name)
{
	
}
*/
