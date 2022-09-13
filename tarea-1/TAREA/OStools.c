//Alumno: Fabian Concha Sifuentes 

#include <unistd.h>
#include <signal.h>

void
mykiller(int P, int S)
{
    kill(P, S);
}
