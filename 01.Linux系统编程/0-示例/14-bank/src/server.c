#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include "../inc/bank.h"

static int g_reqid = -1;
static int g_resid = -1;

typedef struct tag_Service {
	char  srv_path[PATH_MAX+1];
	pid_t srv_pid;
}	SERVICE;

static SERVICE g_srv[] = {
	{"./open",     -1},
	{"./close",    -1},
	{"./save",     -1},
	{"./withdraw", -1},
	{"./query",    -1},
	{"./transfer", -1}
};

int init (void) {
	printf ("服务器初始化...\n");

	if ((g_reqid = msgget (KEY_REQUEST,
		0600 | IPC_CREAT | IPC_EXCL)) == -1) {
		perror ("msgget");
		return -1;
	}

	printf ("创建请求消息队列成功！\n");

	if ((g_resid = msgget (KEY_RESPOND,
		0600 | IPC_CREAT | IPC_EXCL)) == -1) {
		perror ("msgget");
		return -1;
	}

	printf ("创建响应消息队列成功！\n");

	return 0;
}

void deinit (void) {
	printf ("服务器终结化...\n");

	if (msgctl (g_reqid, IPC_RMID, NULL) == -1)
		perror ("msgctl");
	else
		printf ("销毁请求消息队列成功！\n");

	if (msgctl (g_resid, IPC_RMID, NULL) == -1)
		perror ("msgctl");
	else
		printf ("销毁响应消息队列成功！\n");
}

int start (void) {
	printf ("启动业务服务...\n");

	size_t i;
	for (i = 0; i < sizeof (g_srv) / sizeof (g_srv[0]); i++) {
		if ((g_srv[i].srv_pid = vfork ()) == -1) {
			perror ("vfork");
			return -1;
		}

		if (g_srv[i].srv_pid == 0) {
			if (execl (g_srv[i].srv_path, g_srv[i].srv_path,
				NULL) == -1) {
				perror ("execl");
				return -1;
			}

			return 0;
		}
	}

	return 0;
}

int stop (void) {
	printf ("停止业务服务...\n");

	size_t i;
	for (i = 0; i < sizeof (g_srv) / sizeof (g_srv[0]); i++)
		if (kill (g_srv[i].srv_pid, SIGINT) == -1) {
			perror ("kill");
			return -1;
		}

	for (;;)
		if (wait (0) == -1) {
			if (errno != ECHILD) {
				perror ("wait");
				return -1;
			}

			break;
		}

	return 0;
}

void sigint(int signum)
{
    printf("%d\n", signum);
    stop();

    exit(0);
}
int main (void) {
	atexit (deinit);
        signal(SIGINT, sigint);
	if (init () == -1)
		return -1;

	if (start () == -1)
		return -1;

	sleep (1);
	printf ("按<回车>退出...\n");
	getchar ();

	if (stop () == -1)
		return -1;

	return 0;
}
