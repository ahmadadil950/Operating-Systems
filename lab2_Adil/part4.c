/**
 * @file part4.c
 * @author Ahmad Adil 
 * CSc 332 OS Lab
 * Lab Professor: Sujoy Debnath
 * @brief Task 1 (part 4): Repeat part 3 (by writing a new C program) as per the following procedure:
          (a) Read the next 100 characters from source.txt, and among characters read, 
          replace each character `1` with character `L` and all characters are then written in destination.txt
          (b) Write characters "XYZ" into file destination.txt
          (c) Repeat the previous steps until the end of file source.txt. 
          The last read step may not have 100 characters.
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

    //open for reading only
    file_Destination = open(argv[1], O_RDONLY);

    access_file = access(argv[2], F_OK);

    if (access_file == 0) 
    {
        unlink(argv[2]);
    }

    destination = open(argv[2], O_CREAT | O_RDWR, S_IRWXU);
    printf ("DestinationFile %s opened\n", argv[2]);

    if (file_Destination == -1) {
        printf ("\nError: [%s]\n", strerror(errno));
    }
    else 
    {
        // creating a buffer for the characters
        char buffer[104];
        int read_file;

    // replacing all 1s with Ls
        while ((read_file = read(file_Destination, buffer, 101)) > 0) 
        {
            for (int i = 0; i < read_file; i++) 
            {
                if (buffer[i] == '1')
                    buffer[i] = 'L';
            }
            //print XYZ into destination.txt
            buffer[read_file] = 'X';
            buffer[read_file + 1] = 'Y';
            buffer[read_file + 2] = 'Z';

            write(destination, buffer, read_file + 3);
        }
    }
    printf ("All Procedures completed successfully.\n");
    close(file_Destination);
    close(destination);
    return 0;

}