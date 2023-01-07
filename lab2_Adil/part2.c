/**
 * @file part2.c
 * @author Ahmad Adil 
 * CSc 332 OS Lab
 * Lab Professor: Sujoy Debnath
 * @brief Task 1 (part 2): UNIX cat command has three functions with regard to text files: displaying them, combining copies of them and creating new ones.
          Write a C program to implement a command called displaycontent that takes a (text) file name as argument and display its contents. 
          Report an appropriate message if the file does not exist or can’t be opened (i.e. the file doesn’t have read permission). 
          You are to use open(), read(), write() and close() system calls.
 * @date 2022-09-17
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{

    int file_Destination, read_file;

    errno = 0;

    //O_RDWR == to read and write
    file_Destination = open(argv[1], O_RDWR);

    if (file_Destination == -1) {
        printf ("\nError: [%s]\n", strerror(errno));
    }
    else {
        char buffer[BUFSIZ];

        while ((read_file = read(file_Destination, buffer, BUFSIZ)) > 0) {
            write(1, buffer, read_file);
        }
    }
    close(file_Destination);
    return 0;
}