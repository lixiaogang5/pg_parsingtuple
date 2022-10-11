#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>


int main()
{
	char buf[64] = {0};
        struct flock fl;
        memset(&fl, 0x00, sizeof(fl));
        fl.l_type   = F_RDLCK;
        fl.l_whence = SEEK_SET;
        fl.l_start  = 7;
        fl.l_len    = 6;
        fl.l_pid    = getpid();

        fprintf(stdout, "pid = %d\n", fl.l_pid);
        int fd = open("test.txt", O_RDWR);
        if(-1 == fd) {
                perror("open");
                exit(-1);
        }

	sleep(3);
        int flag = fcntl(fd, F_SETLK, &fl);
        if(-1 == flag && (errno == EACCES || errno == EAGAIN)) {
                perror("fcntl"); //效果等同于strerror(errno)
                exit(-1);
        }

        if(-1 == read(fd, buf, sizeof(buf))) {
                perror("read");
                exit(-1);
        }

	fl.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &fl);
	

	if(strlen(buf)) fprintf(stdout, "%s\n", buf);
        close(fd);
        return 0;
}

