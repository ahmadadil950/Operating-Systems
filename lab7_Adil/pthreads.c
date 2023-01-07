/**
 * @file pthreads.c
 * @author Ahmad Adil
 * @brief Consider a system with 3 smoker processes and 1 agent process. Each smoker
        continuously rolls a cigarette and then smokes it. The smoker needs three ingredients: 
        tobacco, paper, and matches. One of the smokers has paper, another has tobacco, and 
        the third has matches. The agent has an infinite supply of all three materials and 
        (randomly) places two of the ingredients on the table each time. The smoker who has 
        the remaining ingredient then makes and smokes a cigarette, signaling the agent on 
        completion. The agent then puts out another two of the three ingredients, and the
        cycle repeats.
 * @version 0.1
 * @date 2022-12-03
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NumofCig 10

void *agent_T(void* arg)
{
	int SN = *(int*)arg;

	if(SN == 1)
		printf("Put paper and match on the table, Smoker # %d\n", SN);

	else if(SN == 2)
		printf("Put match and tobacco on the table, Smoker # %d\n", SN);

	else
	    printf("Put tobacco and paper on the table, Smoker # %d\n", SN);
}

void *tobacco_T(void* arg)
{
    int SN = *(int*)arg;
	printf("This is Smoker # %d, Smoker with TOBACCO picked up paper and match.\n", SN);
}

void *paper_T(void* arg)
{
	int SN = *(int*)arg;
	printf("This is Smoker # %d, Smoker with PAPER picked up match and tobacco.\n", SN);
}

void *match_T(void* arg)
{
	int SN = *(int*)arg;
	printf("This is Smoker # %d, Smoker with MATCH picked up tobacco and paper.\n", SN);
}

int main()
{
    srand(time(0)); // Setting randomized seed
    
    pthread_t Agent, Smoker_Paper, Smoker_Match, Smoker_Tobacco; //Threads

    for(int i = 0; i < NumofCig; ++i)       // Creating 10 senarios
    {
        int SmokerNUM = rand() % 3 + 1;

        pthread_create(&Agent, NULL, agent_T, (void*)(&SmokerNUM));
        pthread_join(Agent,NULL);

        if(SmokerNUM == 1)
        {
            pthread_create(&Smoker_Tobacco, NULL, tobacco_T,(void*)(&SmokerNUM));
            pthread_join(Smoker_Tobacco, NULL);
        }
        else if(SmokerNUM == 2)
        {
            pthread_create(&Smoker_Paper, NULL, paper_T, (void*)(&SmokerNUM));
            pthread_join(Smoker_Paper, NULL);
        }

        else
        {
            pthread_create(&Smoker_Match, NULL, match_T, (void*)(&SmokerNUM));
            pthread_join(Smoker_Match, NULL);
        }
        
    }

    pthread_exit(NULL);
    return 0;
}


