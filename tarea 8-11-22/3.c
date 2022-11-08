/*
 * shm-client - client program to demonstrate shared memory.
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE     128
#define SHMSZ     27

void die(char *s)
{
  perror(s);
  exit(1);
}

struct msgbuf
{
    long    mtype;
    char    mtext[MAXSIZE];
};

int
main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    key = 5678;

    /*
     * Locate the segment.
     */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now read what the server put in the memory.
     */
    //for (s = shm; *s != NULL; s++)
    //    putchar(*s);
    //putchar('\n');
    printf("%s\n", shm);

    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */

    int msqid;
    int msgflg = IPC_CREAT | 0666;
    struct msgbuf sbuf;
    size_t buflen;

    key = 14;

    if ((msqid = msgget(key, msgflg )) < 0)   //Get the message queue ID for the given key
      die("msgget");

    //Message Type
    sbuf.mtype = 1;

    // printf("Enter a message to add to message queue : ");
    // scanf("%[^\n]",sbuf.mtext);
    // getchar();
    
    strcpy(sbuf.mtext, shm);
    *shm = '*';

    buflen = strlen(sbuf.mtext) + 1 ;

    if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
    {
        printf ("%d, %ld, %s, %d \n", msqid, sbuf.mtype, sbuf.mtext, (int)buflen);
        die("msgsnd");
    }

    else
        printf("Message Sent\n");

    exit(0);
}
