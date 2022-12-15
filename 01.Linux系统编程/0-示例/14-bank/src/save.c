#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/msg.h>
#include "../inc/bank.h"
#include "../inc/dao.h"

void sigint (int signum) {
	printf ("存款服务：即将停止。\n");
	exit (0);
}

int main (void) {
	if (signal (SIGINT, sigint) == SIG_ERR) {
		perror ("signal");
		return -1;
	}

	int reqid = msgget (KEY_REQUEST, 0);
	if (reqid == -1) {
		perror ("msgget");
		return -1;
	}

	int resid = msgget (KEY_RESPOND, 0);
	if (resid == -1) {
		perror ("msgget");
		return -1;
	}

	printf ("存款服务：启动就绪。\n");

	for (;;) {
		SAVE_REQUEST req;

		if (msgrcv (reqid, &req, sizeof (req) - sizeof (req.type),
			TYPE_SAVE, 0) == -1) {
			perror ("msgrcv");
			continue;
		}

		SAVE_RESPOND res = {req.pid, ""};
		ACCOUNT acc;

		if (get (req.id, &acc) == -1) {
			sprintf (res.error, "无效账号！");
			goto send_respond;
		}

		if (strcmp (req.name, acc.name)) {
			sprintf (res.error, "无效户名！");
			goto send_respond;
		}

		acc.balance += req.money;

		if (update (&acc) == -1) {
			sprintf (res.error, "更新账户失败！");
			goto send_respond;
		}

		res.balance = acc.balance;

send_respond:

		if (msgsnd (resid, &res, sizeof (res) - sizeof (res.type),
			0) == -1) {
			perror ("msgsnd");
			continue;
		}
	}

	return 0;
}
