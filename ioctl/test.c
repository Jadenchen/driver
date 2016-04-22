#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "devone_ioctl.h"


#define DEVFILE "/dev/devone0"

void read_buffer (int fd)
{

    unsigned char buf[64];
    int ret;

    ret = read(fd, buf, sizeof(buf));
    int i;

    printf ("ret %d \n", ret);
    if (ret == -1)
        printf ("read error \n");
    for (i = 0; i < ret; i++)
        printf ("%02x", buf[i]);

    printf ("\n");
}


int main (void)
{
    struct ioctl_cmd cmd;
    int ret, fd;

    fd = open (DEVFILE, O_RDWR);
    if (fd == -1) {
        printf ("open failed \n");
        return -1;
    }
    //memset fill memory with constant c
    //  void *memset(void *s, int c, size_t n);
    //memset is used to initiate cmd 
    memset (&cmd, 0, sizeof(cmd));
   
    ret = ioctl (fd, IOCTL_VALGET, &cmd);

    if(ret == -1) {
        printf ("ioctl failed \n");
    }

    printf ("val %d\n", cmd.val);

    //read buffer
    read_buffer(fd);

    memset(&cmd, 0, sizeof(cmd));
    cmd.val = 0xcc;
    ret = ioctl (fd, IOCTL_VALSET, &cmd);
    //   ret = ioctl (fd, 2, &cmd);
    if (ret == -1)
        printf ("ioctl failed 2\n");


   // read buffer
    read_buffer(fd);

    memset(&cmd, 0 , sizeof(cmd));
    ret = ioctl(fd, IOCTL_VALGET, &cmd);
 
    if (ret == -1)
        printf ("ioctl failed 3\n");

    printf ("val %d \n", cmd.val);

    close (fd);

    return 0;
}




