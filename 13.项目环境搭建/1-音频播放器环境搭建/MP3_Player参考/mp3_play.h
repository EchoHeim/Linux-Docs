#ifndef _MP3_PLAY_H
#define _MP3_PLAY_H

//共享内存申请标识
#define PERM S_IRUSR|S_IWUSR

extern int do_work;
extern int first_play;

extern pid_t son_pid;
extern pid_t grandson_pid;

extern int shmid;
extern char *p_addr;

extern void  Auto_play(song *head);
extern void Start_play_song(song *head);
extern void Pause_song(pid_t pid);
extern void Continue_play(pid_t pid);
extern void Stop_play(pid_t pid);
extern void Next_song(pid_t pid);
extern void Pre_song(pid_t pid);

#endif
