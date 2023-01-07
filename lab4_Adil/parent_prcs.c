/**
 * @file parent_prcs.c
 * @author Ahmad Adil
 * @brief   Write a C program and call it Parent_Prcs.c. Execute the files as per the following
            procedure using
            execv system call. Use sleep system calls to introduce delays.
            [Step 3] Using fork create a child process, say Child 1 that executes Prcs_P1. This
            will create two destinationfiles according to Step 1.
            [Step 4] After Child 1 finishes its execution, use fork to create another child process,
            say Child 2 and execute
            Prcs_P2that accomplishes the procedure described in Step 2.
 * @version 0.1
 * @date 2022-10-15
 * 
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(void)
{
    int PID1, PID2;
    PID1 = fork();
    if(PID1 == 0)
    {
        printf("Child 1\n");
        char *const argv[] = {"prcs_part1", NULL};
        execv(argv[0], argv);
        printf("EXECV Failed. Is prcs_part1.c compiled?\n");
    }
    else
    {
        sleep(1);
        PID2 = fork();
        if(PID2 == 0) {
            printf("Child 2\n");
            char *const argv[] = {"prcs_part2", NULL};
            execv(argv[0], argv);
            printf("EXECV Failed. Is prcs_part2.c compiled?\n");
    }
    }
    return 0;
}