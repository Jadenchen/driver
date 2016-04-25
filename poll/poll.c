#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>

#define DEVFILE "/dev/devone0"

int main (void)
{
	int fd;
	struct pollfd fds;
	int retval;
	unsigned char buf[64];
	int i;
	ssize_t sz;

	fd = open (DEVFILE, O_RDWR);
	if (fd == -1){
		printf ("open failed \n");
		return -1;
	}

	//initial poll

	do {
		fds.fd = fd;
		fds.events = POLLIN;

		printf ("poll().....\n");
		retval = poll (&fds, 1, 15*1000);
		if (retval == -1){
			printf ("poll() failed \n");
			break;
		}

		if (retval)
			break;
	} while (retval == 0);

	if (fds.revents & POLLIN){
		printf ("read().....\n");
		sz = read(fd, buf, sizeof(buf));
		printf("sz %d\n", sz);
		for (i = 0; i < sz;i++){
			printf ("%02x ",buf[i]);
		}
	}
	printf ("\n");
	close (fd);
	return 0;
}