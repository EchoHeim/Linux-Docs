#ifndef _MP3_LINKLIST_H
#define _MP3_LINKLIST_H

typedef struct node_s 
{    
 	char name[128];
	struct node_s *next;
	struct node_s *prev;
}song;



extern song * Linklist_create(char *path_name);
extern int Linklist_find(song *head, char *name);

#endif

