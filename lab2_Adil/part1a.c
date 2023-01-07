/**
 * @file part1a.c
 * @author Ahmad Adil 
 * CSc 332 OS Lab
 * Lab Professor: Sujoy Debnath
 * @brief Task 1 (part 1a): Extend code snippet 1 to check for read and write access permissions of a given file
 * @date 2022-09-17
 * 
 */


#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *filepath = argv[1];
    int returnval; 
    /**
     * Checking if the file
     * currently exists
     */
    returnval = access(filepath, F_OK);
    if (returnval == 0)
        printf("\n %s exists\n", filepath);
    else
    {
        if (errno == ENOENT)
            printf("%s does not exist\n", filepath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", filepath);
        return 0;
    }
    

    /**
     * Read access for the file
     */
    returnval = access(filepath, R_OK);

    if(returnval == 0)
    {
        printf("%s read file access \n", filepath);
    }
    else
    {
        printf("%s Can't read file access \n", filepath);
    }

    /**
     * Write access for the file
     * 
     */

    returnval = access(filepath, W_OK);

    if(returnval == 0)
    {
        printf("%s Write file access \n", filepath);
    }
    else
    {
        printf("\n %s write access denied \n", filepath);
    }

    return 0;
}
    



