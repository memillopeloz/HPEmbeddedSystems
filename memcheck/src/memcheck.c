#include <stdio.h>
#include <stdlib.h> //envs & excec
#include <string.h>
#include <ctype.h> // isprint
#include <unistd.h> // getopt & fork
#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait

int main (int argc, char** argv)
{
    char* pname = NULL;
    //char* path = getenv("PWD");
    char* path = NULL;
//    char* soPath = getenv("PWD"); OJO NO USAR GETENV CON LA MISMA VAR 2 VECES
    char* soPath = "/home/maestria/Desktop/Empotrados/homework1/memcheck/lib/caquita.so";
    int c = 0, val = 1;
    pid_t pid;


    while ((c = getopt (argc, argv, "ahp:")) != -1)
    {
        val = 0;
        switch (c)
        {
            case 'a':
                printf("Author: Guillermo Lopez Navarro\n");
                break;
            case 'h':
                printf("***************\n*    Usage    * \n***************\n"
                  "\n./memcheck [ -p file ] [ -h ] [ -a ] \n"
                  "-p file ​ specifies the full path to a binary file to analyze for memory leaks.\n"
                  "-a \t ​displays the program's author.\n"
                  "-h​ \t displays this help message.\n \n");
                break;
            case 'p':
                // New process for running the desired program
                /*pid=fork();
                if (pid==0)
                { // Child process
                    pname = optarg;
                    path = getenv("PWD");
                    strcat(path, pname);
                    setenv("LD_PRELOAD", soPath, 1);

                    static char *args[]={NULL};
                    execv(path, args);

                    unsetenv("LD_PRELOAD");
                }
                else
                { // Parent process, wait for child to finish
                    waitpid(pid,0,0);
                }
                printf("Path: %s , name: %s \n", path, pname);*/
//-----------------------------------------------------------------------
                pid=fork();
                if (pid==0)
                { // Child process
                    pname = "/mc";
                    path = getenv("PWD");
                    strcat(path, pname);
                    setenv("LD_PRELOAD", soPath, 1);
                    printf("Path: %s \n", path);

                    char *args[]={"mc", optarg, NULL}; //  Call memcheck
                    execv(path, args);

                    unsetenv("LD_PRELOAD");
                    printf("Path: %s , name: %s \n", path, pname);
                }
                else
                { // Parent process, wait for child to finish
                    waitpid(pid,0,0);
                }
                printf("SALIMOS DE MC\n");
//-----------------------------------------------------------------------

                break;
            case '?':
                if (optopt == 'p')
                    fprintf (stderr, "Option -p requires the path to a C executable for memcheck.\n");
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option '-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character '\\x%x'.\n", optopt);
                return 1;
            default:
                abort ();
        }
    }
    if(val) // No parameter provided
        printf("A parameter must be provided. Run ./memcheck -h for usage.\n");

    return 0;
}
