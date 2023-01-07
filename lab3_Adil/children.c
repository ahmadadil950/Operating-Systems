/**
 * @file children.c
 * @author Ahmad Adil
 * CSc 332 OS Lab
 * Lab Professor: Sujoy Debnath
 * @brief Write a program children.c, and let the parent process produce two child processes. One prints 
 *        out "I am child one, my pid is: " PID, and the other prints out "I am child two, my pid is: " PID.
 *        Guarantee that the parent terminates after the children terminate (Note, you need to wait for two 
 *        child processes here). Use the getpid() function to retrieve the PID.
 * @version 0.1
 * @date 2022-09-24
 */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int stat, pid1, pid2;

    // Creating the first child
    pid1 = fork();
    wait(&stat);


    if(pid1 != 0)
    {
        printf("I am the parent, my PID is: %d\n", getpid());
    }
    else
    {
        // creating the second child
        printf("I am child one, my PID is: %d\n", getpid());
        pid2 = fork();
        wait(&stat);

        if(pid2 == 0) 
        {
            printf("I am child two, my PID is: %d\n", getpid());
        }
    }
    
    return 0;
    
}