#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include "../inc/dao.h"

const char* ID_FILE = "id.dat";

int genid (void) {
	int id = 1000;

	int fd = open (ID_FILE, O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	if (read (fd, &id, sizeof (id)) == -1) {
		perror ("read");
		return -1;
	}

	id++;

	if (lseek (fd, 0, SEEK_SET) == -1) {
		perror ("lseek");
		return -1;
	}

	if (write (fd, &id, sizeof (id)) == -1) {
		perror ("write");
		return -1;
	}

	close (fd);
	return id;
}

int save (const ACCOUNT* acc) {
	char pathname[PATH_MAX+1];
	sprintf (pathname, "%d.acc", acc -> id);

	int fd = creat (pathname, 0644);
	if (fd == -1) {
		perror ("creat");
		return -1;
	}

	if (write (fd, acc, sizeof (*acc)) == -1) {
		perror ("write");
		return -1;
	}

	close (fd);
	return 0;
}

int get (int id, ACCOUNT* acc) {
	char pathname[PATH_MAX+1];
	sprintf (pathname, "%d.acc", id);

	int fd = open (pathname, O_RDONLY);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	if (read (fd, acc, sizeof (*acc)) == -1) {
		perror ("read");
		return -1;
	}

	close (fd);
	return 0;
}

int update (const ACCOUNT* acc) {
	char pathname[PATH_MAX+1];
	sprintf (pathname, "%d.acc", acc -> id);

	int fd = open (pathname, O_WRONLY);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	if (write (fd, acc, sizeof (*acc)) == -1) {
		perror ("write");
		return -1;
	}

	close (fd);
	return 0;
}

int delete (int id) {
	char pathname[PATH_MAX+1];
	sprintf (pathname, "%d.acc", id);

	if (unlink (pathname) == -1) {
		perror ("unlink");
		return -1;
	}

	return 0;
}
