#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

#define MAX_BUFF 1024

int 
main(void)
{
    int     fd[2], fd2[2], nbytes;
    pid_t   childpid;
    char    readbuffer[80];
    int c;

    pipe(fd);

    if((childpid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if(childpid == 0) 
    {
    	char *afifo = "afifo";
        mkfifo(afifo, 0666);
	int fifofd = open(afifo, O_RDONLY);
	read(fifofd, readbuffer, sizeof(readbuffer));
	close(fifofd);

	//scanf("%s", readbuffer);
	close(fd[0]);
	write(fd[1], readbuffer, strlen(readbuffer));
	exit(0);
    } 
    else 
    {
        //printf("Parent program.\n"); 
        close(fd[1]);
        nbytes = read(fd[0], readbuffer, 2);
        readbuffer[nbytes]='\0';
        printf("Data received: %s\n", readbuffer);
    }

    return(0);
}
