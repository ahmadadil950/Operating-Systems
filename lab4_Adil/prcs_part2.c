/**
 * @file prcs_part2.c
 * @author Ahmad Adil
 * @brief   Copy the contents of source.txt1 into destination1.txtand
            destination2.txtasper the following procedure.
            1. Read the next 100 characters from source.txt, and among characters read, replace
            each character ’1’ with character ’L’ and all characters are then written in destination1.txt
            2. Then the next 50 characters are read from source.txt, and among characters read,
            replace each character ’3’ with character ’E’ and all characters are then written in
            destination2.txt.
            3. The previous steps are repeated until the end of file source.txt. The last read may
            not have100 or 50 characters.
            Once you’re done with successful creation of executables for the above two steps do the
            following.
            Write a C program and call it Parent_Prcs.c. Execute the files as per the following
            procedure using
            execv system call. Use sleep system calls to introduce delays.
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

int main()
{
    int source, RD, destination1, destination2;
    source = open("Source.txt", O_RDONLY);

    destination1 = open("destination1.txt", O_CREAT | O_RDWR, S_IRWXU);
    destination2 = open("destination2.txt", O_CREAT | O_RDWR, S_IRWXU);

    if(source == -1 && destination1 == -1 && destination2 == -1) {
        printf("Error: [%s}\n", strerror(errno));
    }
    else {
        char buffer[101];
        int n = 101;

        while((RD = read(source, buffer, n)) > 0) {
            if(n == 101) {
                for(int i = 0; i < sizeof(buffer); i++) {
                    if(buffer[i] == '1') {
                        buffer[i] = 'L';
                    }
                }
                write(destination1, buffer, RD);
                n = 51;
            }
            else {
                for(int i = 0; i < sizeof(buffer); i++) {
                    if(buffer[i] == '3') {
                        buffer[i] = 'E';
                    }
                }
                write(destination2, buffer, RD);
                n = 101;
            }
        }
    }
    close(source);
    close(destination1);
    close(destination2);
    return 0;
    
}