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

	//遍历链表
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
函数功能：查找一个结点
函数参数：head用来确定是哪一个链表，name是要查找的结点
函数返回值：成功返回0，失败返回-1
*/
int Linklist_find(song *head, char *name)
{        
	song *tail = NULL;

	tail = head;
	 
	//先判断链表是否为空
	if(tail == NULL)
	{
		return -1;
	}
	
	//开始查找
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
函数功能：删除一个结点
函数参数：head表示是哪一个链表，name是要删除的结点
函数返回值：删除成功返回0，删除失败返回－1
*/
/*
int Linklist_del(node_t *head, char *name)
{
	
}
*/
