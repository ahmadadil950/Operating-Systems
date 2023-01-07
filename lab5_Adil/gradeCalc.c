/**
 * @file gradeCalc.c
 * @author Ahmad Adil
 * @brief   To solve this, write program which has the main process as Director process, which 
            reads a file containing grades of all homeworks of all chapters and creates x number of 
            Manager processes. Each Manager process will take care of solving a chapter. Each 
            manager process will create y number of Worker process and pass marks of n students
            to each of them and they calculate and print the average.

 * @date 2022-11-03
 * 
 */

#include <stdio.h>
#include <unistd.h>


int main(int argc, char** argv)
{
    int a, b;
    printf("Number of Chapters: ");
    scanf("%d", &a);
    printf("Number of assignments: ");
    scanf("%d", &b);

    int total = a * b;

    int students[10][total], m_PID[a], w_PID[a][b];
    FILE *fp = fopen("quiz_grades.txt", "r");
    for(int i = 0; i< 10; i++)
    {
        for (int j = 0; j < total; j++)
        {
            fscanf(fp, "%d", &students[i][j]);
        }
    }

    fclose(fp);
    printf("Done reading file...\n");

    for(int i = 0; i<a; i++){
        m_PID[i] = fork();
        if(m_PID[i] > 0){
        }
        else
        {
            for(int j = 0; j < b; j++){
                w_PID[i][j] = fork();
                if(w_PID[i][j] > 0){
                }
                else
                {
                    int sum = 0;
                    float AVG;
                    for(int k = 0; k < 10; k++)
                    {
                        sum += students[k][i * a + j];
                    }
                    AVG = sum / 10.0;
                    printf("Manager Process: %d,\n Worker Process %d,\n Average: %f\n", i, j, AVG);
                    break;
                }
                
            }
            break;
        }
        
    }
    return 0;
}

