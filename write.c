#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>


int main()
{
        struct flock fl;
        memset(&fl, 0x00, sizeof(fl));
        fl.l_type   = F_WRLCK;
        fl.l_whence = SEEK_SET;
        fl.l_start  = 0;
        fl.l_len    = 5;
        fl.l_pid    = getpid();

        fprintf(stdout, "pid = %d\n", fl.l_pid);
        int fd = open("test.txt", O_RDWR);
        if(-1 == fd) {
                perror("open");
                exit(-1);
        }

        int flag = fcntl(fd, F_SETLK, &fl);
        if(-1 == flag && (errno == EACCES || errno == EAGAIN)) {
                perror("fcntl");
                exit(-1);
        }

        if(-1 == write(fd, "TEST CODE.", strlen("TEST CODE."))) {
                perror("write");
                exit(-1);
        }

	sleep(5);

	fl.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &fl);

        close(fd);
        return 0;
}

