#include <stdio.h>

int main(){

int pid;
pid = fork();

//Child proccess
if (pid == 0)
{
   system("echo 'hijo'");
   int pid = getpid();
   int ppid = getppid();
   system("echo 'hijo'");
   printf("Pdre ID: %d, PPID: %d /n",pid,ppid);
   sleep(100);
}
else{
   system("echo 'hijo'");
   int pid = getpid();
   int ppid = getppid();
   printf("Pdre ID: %d, PPID: %d /n",pid,ppid);
   sleep(100);
}
return 0;
}
