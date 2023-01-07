/**
 * @file semaphores.c
 * @author Ahmad Adil
 * @brief Consider a system with 3 smoker processes and 1 Agent process. Each smoker
        continuously rolls a cigarette and then smokes it. The smoker needs three ingredients: 
        tobacco, paper, and matches. One of the smokers has paper, another has tobacco, and 
        the third has matches. The Agent has an infinite supply of all three materials and 
        (randomly) places two of the ingredients on the table each time. The smoker who has 
        the remaining ingredient then makes and smokes a cigarette, signaling the Agent on 
        completion. The Agent then puts out another two of the three ingredients, and the
        cycle repeats.
 * @version 0.1
 * @date 2022-12-03
 * 
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include "sem.h"

#define NumofCig 10

static int SmokerNum;
static int stop = 0;

int main()
{
    srand(time(0));
    int PID;

    //Creating semaphores for each process
    int Lock = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);
    int Agent = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);
    int smoker_Tobacco = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);
    int smoker_Paper = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);
    int smoker_Match = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);

    //Initalization for the semaphores
    sem_create(Lock, 1);
    sem_create(Agent,0);
    sem_create(smoker_Tobacco, 0);
    sem_create(smoker_Paper, 0);
    sem_create(smoker_Match, 0);

    if((PID = fork()) == 0)
    {
        //Smoker Tobacco
        while (!stop)
        {
            P(smoker_Tobacco);
            P(Lock);
            printf("Smoker #1 with tobacco has picked up paper and match\n");
            V(Agent);
            V(Lock);
        }
    }

else
	{
		// Agent process
		if((PID = fork()) == 0)
		{
			// smoker_Paper
			while(!stop)
			{
				P(smoker_Paper);
				P(Lock);
				printf("Smoker #2 with paper has picked up match and tobacco!\n");
				V(Agent);
				V(Lock);
			}
		}
		else
		{
			// Agent process
			if((PID = fork()) == 0)
			{
				// smoker_Match
				while(!stop)
				{
					P(smoker_Match);
					P(Lock);
					printf("Smoker #3 with match has picked up tobacco and paper!\n");
					V(Agent);
					V(Lock);
				}
			}
			else
			{
				
				// Agent process
				for(int i = 0; i < NumofCig; ++i)
				{
					P(Lock);
					SmokerNum = rand()%3 + 1;
					if(SmokerNum == 1)
					{
						// paper and match
						printf("Put paper and match on the table, Smoker # %d\n", SmokerNum);
						V(smoker_Tobacco);
					}
					else if(SmokerNum == 2)
					{
						// match and tobacco
						printf("Put match and tobacco on the table, Smoker # %d\n", SmokerNum);
						V(smoker_Paper);
					}
					else
					{
						// tobacco and paper
						printf("Put tobacco and paper on the table, Smoker # %d\n", SmokerNum);
						V(smoker_Match);
					}
					if(i == NumofCig - 1)
						stop = 1;
					V(Lock);
					P(Agent);
				}
			}
		}
	}

	return 0;
}