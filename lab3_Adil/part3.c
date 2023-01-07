/**
 * @file part3.c
 * @author Ahmad Adil
 * CSc 332 OS Lab
 * Lab Professor: Sujoy Debnath
 * @brief Task 3: Now write a program, where a parent process creates 2 child process
 *        and computes S1 and S2. And Parent process computes S3. The input argument for program 
 *        will be the end of series number for S3.
 * @version 0.1
 * @date 2022-09-24
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main (int argc, char *argv[])
{
    pid_t n1, n2;

    int num = atoi(argv[1]);

    /**
     * num is the limit
     * child process 1 gets created
     * calculates series (1+3+5+...+n)
     * prints child process 1
     * child process 2 is created
     */
    n1 = fork();
    if(n1 == 0)
    {
        int sum = 0;
        for(int i = 1; i < num; i += 2)
        {
            sum += i;
        }

        printf("S1 = %d\n", sum);
    }
    /**
     * child process 2 created
     * prints chld process 2
     * computes parents process
     * caluclates series (1+2+3+4+...+n)
     * then prints parent process
     */
    else
    {
        n2 = fork();                                
        if(n2 == 0) {
            int sum = 0;
            for(int i = 2; i <= num; i += 2) {      
                sum += i;
            }
            printf("S2 = %d\n", sum);               
        }
        else {                                      
            int sum = 0;
            for(int i = 1; i <= num; i++) {        
                sum += i;
            }
            printf("S3 = %d\n", sum);          
        }
    }
    
}