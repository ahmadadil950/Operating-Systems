/**
 * @file part3.c
 * @author Ahmad Adil 
 * CSc 332 OS Lab
 * Lab Professor: Sujoy Debnath
 * @brief Task 1 (part 3): The cp command copies the source file specified by the SourceFile parameter to the destination file specified by the DestinationFile parameter.
          Write a C program that mimics the cp command using open() system call to open source.txt file in read-only mode and copy the contents of it to destination.txt 
          using read() and write() system calls.
 * @date 2022-09-17
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main (int argc, char *argv[])
{
    int file_Destination, read_file, access_file, destination;
    errno = 0;

    //O_RDONLY == open for reading only
    file_Destination = open(argv[1], O_RDONLY);

    access_file = access(argv[2], F_OK);
    //checking if destination file exists and deletes(unlinks) it if it exists
    if (access_file == 0) 
    {
        unlink(argv[2]);
    }

    //O_CREAT == system create a file that doesn't exist
    //O_RDWR == to read and write
    //S_IRWXU == to read, write, and execute/search by owner
    destination = open(argv[2], O_CREAT | O_RDWR, S_IRWXU);
    printf ("DestinationFile %s opened\n", argv[2]);

    if (file_Destination == -1) 
    {
        printf ("\nError: [%s]\n", strerror(errno));
    }
    else 
    {
        char buffer[BUFSIZ];

        while ((read_file = read(file_Destination, buffer, BUFSIZ)) > 0) {
            write(destination, buffer, read_file);
        }
    }
    printf ("Contents copied successfully.\n");
    close(file_Destination);
    close(destination);
    return 0;
}