/**
 * @file part4.c
 * @author Ahmad Adil
 * CSc 332 OS Lab
 * Lab Professor: Sujoy Debnath
 * @brief Task 4: Open a file called readme.txt in the child process, read the contents and
          pass to the parent process. Parent process will write to readme.txt, “Parent is writing:” 
          and write the contents it received from the child to the readme.txt file. (Hint: Use Pipe)
 * @version 0.1
 * @date 2022-09-24
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>


#define MAX_READ 100

int main (int argc, char *argv[])
{

    /**
     * get file name
     * Open file in read and write mode
     * create a buffer array
     */
    char *filepath = argv[1];                          
    int fd = open(filepath, O_RDWR);                            
    char *buffer[MAX_READ + 1];                                 

    ssize_t num;                          // number of bits read

    int pipefd[2];
    pipe(pipefd);

    pid_t n1;
    n1 = fork();                         // child process created

    if(n1 == 0) 
    {
        close(pipefd[0]);
        while((num = read(fd, &buffer, MAX_READ + 1))) {
            write(pipefd[1], buffer, num);
        }
        close(pipefd[1]);               // read done
        exit(0);
    }
    else
    {
        wait(0);
        close(pipefd[1]);
        printf("Parent is writing...\n");
        while((num = read(pipefd[0], &buffer, MAX_READ + 1))) {
            write(fd, buffer, num);
        }
        close(pipefd[0]);              // write done
        exit(0);
    }
    
}