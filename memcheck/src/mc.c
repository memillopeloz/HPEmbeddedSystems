#include <stdio.h>
#include <stdlib.h> //envs & excec
#include <string.h>
#include <unistd.h> // getopt & fork
#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait
//#include "test.h"

//extern void macarena(int a); //no sirve para funciones custom

int main (int argc, char** argv)
{
    printf("ESTAMOS EN MC PAPU, argv[1] es %s \n", argv[1]);
    char* dummy = NULL; // To get rid of atoi warning

    // New process for running the desired program
    pid_t pid=vfork();
    if (pid==0)
    { // Child process
        static char *args[]={NULL};
        execv(argv[1], args); // From this point forward nothing else will be executed in the child process
        //printf("Child: Pointer data -> [0]:%d  [1]: %d \n", dummy[0], dummy[1]);
        //printf("Count in child: %d \n", getpid());
    }
    else
    { // Parent process, wait for child to finish
        waitpid(pid,0,0);
        int mC = getpid();
        //int mC = 100;
        //macarena(0);
        int mF = atoi(dummy);
        //printf("Parent: Pointer data -> [0]:%d  [1]: %d \n", dummy[0], dummy[1]);
        //printf("Count in parent: %d \n", mC);
        printf("Analysis finished!\n"
            "Memory allocations: %d \n"
            "Memory frees: %d \n"
            "Total memory leaks found: %d \n", mC, mF, mC-mF);
    }
    printf("Count outside the shit: %d \n", getpid());

    return 0;
}