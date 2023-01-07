/**
 * @file interperter.c
 * @author Ahmad Adil
 * @brief   Write a special simple command interpreter that takes a command and its arguments.
            This interpreter is a program where the main process creates a child process to execute 
            the command using exec() family functions. After executing the command, it asks for
            a new command input ( parent waits for child). The interpreter program will get
            terminated when the user enters exit.
 * @date 2022-11-03
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    pid_t PID;

    while(1)
    {
        char Command[100];
        printf(" >> ");
        scanf(" %[^\n]s", Command);

        if(!strcmp(Command, "exit"))
        {
            break;
        }

        char* arg[100];
        char* token;
        char* save = NULL;
        int i =0;

        for(token = strtok_r(Command, " ", &save); token != NULL; token = strtok_r(NULL, " ", &save)){
                arg[i] = token;
                i++;
            }
            arg[i] = NULL;
            PID = fork();

            if(PID == 0)
            {
                execvp(arg[0], arg);
                printf("file not found\n");
                return 0;
            }
            else
            {
                wait(NULL);
            }
            
    }
}