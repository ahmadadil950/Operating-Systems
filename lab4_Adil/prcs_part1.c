/**
 * @file prcs_part1.c
 * @author Ahmad Adil
 * @brief   Create two files namely, destination1.txt and destination2.txt with
            read, write,and execute permissions.
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
    int FD1, FD2;

    errno = 0;
    FD1 = open("destination1.txt", O_CREAT | O_RDWR, S_IRWXU);

    if(FD1 == -1)
    {
        printf("open() failed with error [%s]\n", strerror(errno));
    }
    else
    {
        printf("destination 1: open() sucessful\n");
    }

    close(FD1);

    FD2 = open("destination2.txt", O_CREAT | O_RDWR, S_IRWXU);

    if(FD2 == -1)
    {
        printf("open() failed with error [%s]\n", strerror(errno));
    }

    else
    {
        printf("destination 2: open() successful\n");
    }

    close(FD2);
    return 0;
}

