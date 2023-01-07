/**
 * @file part2.c
 * @author Ahmad Adil
 * @brief   Write a program where a child is created to execute a command that shows all files
            (including hid-den files) in a directory with information such as permissions, owner,
            size, and when last modified.
            Use execvp(...).
            For the command to list directory contents with various options, refer the handout
            on Unix filesystem sent to you in the first class.
            Announce the successful forking of child process by displaying its PID.
 * @version 0.1
 * @date 2022-10-15
 * 
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    int stat, PID1;

    PID1 = fork();
    wait(&stat);

    if(PID1 != 0)
    {
        printf("I am the parent. My PID is: %d\n", getpid());
    }
    else
    {
        printf("I am child one. My PID is: %d\n", getpid());
        char* argv[] = {"ls", "-laxo", NULL};
        execvp(argv[0],argv);
        printf("EXECVP Failed\n");
    }

    return 0;
    
}