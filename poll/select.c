#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVFILE "/dev/devone0"

int main (void)
{
	int retval;
	int fd;
	fd_set rfds;
	struct timeval tv;
	ssize_t sz;
	int i;
	unsigned char buf[64];

	fd = open (DEVFILE, O_RDWR);
	if (fd == -1){
		printf ("open failed \n");
		return -1;
	}
	//seclt method
	do {
	//initial select
	FD_ZERO(&rfds);
	FD_SET (fd, &rfds);
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	printf ("select().....\n");
	retval = select (fd+1, &rfds, NULL, NULL, &tv);
	printf("select retval %d\n", retval);
	if (retval == -1){
		printf ("select error \n");
		break;
	}

	if (retval)
		break;

	}while (retval == 0);

	if(FD_ISSET(fd, &rfds)){
		printf ("read().....\n");
		sz = read(fd, buf, sizeof(buf));
		printf("read %d\n", sz);
		for (i = 0; i < sz;i++){
			printf("%02x", buf[i]);
		}
	
	}
	printf ("\n");
	close (fd);

	return 0;
}