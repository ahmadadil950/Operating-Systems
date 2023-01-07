/**
 * @file part1.c
 * @author Ahmad Adil
 * @brief   Write a program where a child is created to execute command that tells you the date and time inUnix.
            Use execl(...).
            Note, you need to specify the full path of the file name that gives you date and time
            information.Announce the successful forking of child process by displaying its PID.
 * @version 0.1
 * @date 2022-10-15
 * 
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
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
        execl("/bin/date", "date", NULL);
        printf("EXECL Failed\n");
    }

    return 0;
    
}
