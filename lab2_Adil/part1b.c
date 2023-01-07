/**
 * @file part1b.c
 * @author Ahmad Adil 
 * CSc 332 OS Lab
 * Lab Professor: Sujoy Debnath
 * @brief Task 1 (part 1b): Write a C program where open system call creates a new file (say, destination.txt) 
 *        and then opens it. (Hint: use the bitwise OR flag)
 * @date 2022-09-17
 * 
 */


#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int file_Destination;

    argv[2] = "destination.txt";

    errno = 0;

    /**
     * O_CREAT == system create a file that doesn't exist
     * O_RDWR == to read and write
     * S_IRWXU == to read, write, and execute/search by owner
     */
    file_Destination = open(argv[2], O_CREAT | O_RDWR, S_IRWXU);
    printf ("destination.txt file created\n");

    if (file_Destination == -1) 
    {
        printf ("\nopen() failed with error [%s]\n", strerror(errno));
        return 1;
    }
    else 
    {
        printf ("\nopen() successful\n");
    }

    close(file_Destination);
    return 0;

}  