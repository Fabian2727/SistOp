#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#define MAXSIZE     128

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
main()
{

    int id1 = getSem(3333);
    controlSem(id1, 4);
    semP(id1);

    int msqid;
    key_t key;
    struct msgbuf rcvbuffer;

    key = 14;

    if ((msqid = msgget(key, 0666)) < 0)
      die("msgget()");


     //Receive an answer of message type 1.
    if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0) < 0)
      die("msgrcv");

    printf("%s\n", rcvbuffer.mtext);
    exit(0);
}
