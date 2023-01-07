/**
 * @file part2.c
 * @author Ahmad Adil
 * CSc 332 OS Lab
 * Lab Professor: Sujoy Debnath
 * @brief Task 2: Consider the parent process as P. The program consists of fork() system 
 *        call statements placed at different points in the code to create new processes Q and R. 
 *        The program also shows three variables: a, b, and pid - with the print out of these 
 *        variables occurring from various processes. Show the values of pid, a, and b printed by 
 *        the processes P, Q, and R.
 * @version 0.1
 * @date 2022-09-24
 */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) 
{
    int a = 10, b = 25, fq = 0, fr = 0;
    fq = fork();        // fork a child - (process Q)

    if(fq == 0) {       // child fork successful
        a = a + b;
        printf("Value of a: %d, Value of b: %d, Value of PID: %d \n", a, b, getpid());
        fr = fork();    // fork a child (process R)

        if(fr != 0) {
            b = b + 20;
            printf("Value of a: %d, Value of b: %d, Value of PID: %d \n", a, b, getpid());
        }
        else {
            a = (a * b) + 30;
            printf("Value of a: %d, Value of b: %d, Value of PID: %d \n", a, b, getpid());
        }
    }

    else {
        b = a + b - 5;
        printf("Value of a: %d, Value of b: %d, Value of PID: %d \n", a, b, getpid());
    }
    return 0;
}