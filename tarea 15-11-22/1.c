#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/sem.h>
#define MAXSIZE     128

char *arg;

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

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

union semun u;

struct sembuf p = {0, -1, SEM_UNDO};
struct sembuf v = {0, +1, SEM_UNDO};

void semP(int id)
{
    if (semop(id, &p, 1) < 0)
    {
        perror("semop p");
        exit(13);
    }
}

void semV(int id)
{
    if (semop(id, &v, 1) < 0)
    {
        perror("semop p");
        exit(14);
    }
}

int getSem(const int KEY)
{
    int id = semget(KEY, 1, 0666 | IPC_CREAT);
    if (id < 0)
    {
        perror("semget");
        exit(11);
    }
    return id;
}

void controlSem(int id, int numRecursos)
{
    //union semun u;
    u.val = numRecursos;
    if (semctl(id, 0, SETVAL, u) < 0)
    {
        perror("semctl");
        exit(12);
    }
}

int
main(int argc, char *argv[])
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    struct msgbuf sbuf;
    size_t buflen;

    int id1 = getSem(1111);
    controlSem(id1, 4);

    key = 1234;

    if ((msqid = msgget(key, msgflg )) < 0)   //Get the message queue ID for the given key
      die("msgget");

    //Message Type
    sbuf.mtype = 1;

    strcpy(sbuf.mtext, argv[1]);

    buflen = strlen(sbuf.mtext) + 1 ;

    if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
    {
        printf ("%d, %ld, %s, %d \n", msqid, sbuf.mtype, sbuf.mtext, (int)buflen);
        die("msgsnd");
    }

    else
        printf("Message Sent\n");
     semV(id1);

    exit(0);
}
