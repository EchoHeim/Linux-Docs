#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/msg.h>
#include "../inc/bank.h"
#include "../inc/dao.h"

void sigint (int signum) {
	printf ("转账服务：即将停止。\n");
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

	printf ("转账服务：启动就绪。\n");

	for (;;) {
		TRANSFER_REQUEST req;

		if (msgrcv (reqid, &req, sizeof (req) - sizeof (req.type),
			TYPE_TRANSFER, 0) == -1) {
			perror ("msgrcv");
			continue;
		}

		TRANSFER_RESPOND res = {req.pid, ""};
		ACCOUNT acc[2];

		if (get (req.id[0], &acc[0]) == -1) {
			sprintf (res.error, "无效账号！");
			goto send_respond;
		}

		if (strcmp (req.name[0], acc[0].name)) {
			sprintf (res.error, "无效户名！");
			goto send_respond;
		}

		if (strcmp (req.passwd, acc[0].passwd)) {
			sprintf (res.error, "密码错误！");
			goto send_respond;
		}

		if (req.money > acc[0].balance) {
			sprintf (res.error, "余额不足！");
			goto send_respond;
		}

		if (get (req.id[1], &acc[1]) == -1) {
			sprintf (res.error, "无效对方账号！");
			goto send_respond;
		}

		if (strcmp (req.name[1], acc[1].name)) {
			sprintf (res.error, "无效对方户名！");
			goto send_respond;
		}

		acc[0].balance -= req.money;

		if (update (&acc[0]) == -1) {
			sprintf (res.error, "更新账户失败！");
			goto send_respond;
		}

		acc[1].balance += req.money;

		if (update (&acc[1]) == -1) {
			sprintf (res.error, "更新对方账户失败！");
			goto send_respond;
		}

		res.balance = acc[0].balance;

send_respond:

		if (msgsnd (resid, &res, sizeof (res) - sizeof (res.type),
			0) == -1) {
			perror ("msgsnd");
			continue;
		}
	}

	return 0;
}
