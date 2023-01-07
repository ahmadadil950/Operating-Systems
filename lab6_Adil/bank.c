/**
 * @file bank.c
 * @author Ahmad Adil
 * @brief   Identify the critical section and synchronize the program. You would need to use P(sem) 
            and V(sem) operations at the right places to solve the synchronization problem. You will 
            also need to find the logical flaw if there is any and try to solve it. To use P(sem) and 
            V(sem) include the provided “sem.h” file. Your solution should solve the following 
            problems:
            • Prevent race conditions
            • Prevent a son from withdrawing money when there is no balance.
            • Prevent undefined outputs like negative balance
            • Prevent a process from continuously requesting access to the shared 
            memory. Prevent unnecessary cpu cycle.
            • The problem should be solved with as few semaphore variables as 
            possible.
 * @date 2022-11-23
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "sem.h"

#define CHILD      			 0  			/* Return value of child process from fork call */
#define TRUE       			 0  
#define FALSE      			 1

#define NumOfDepositAttempt  5           /* How many times Dad will deposit money */
#define NumOfWithdrawAttempt 20          /* Total number of attempts SON_1 and SON_2 has */

#define DepositAmount        60         /* The amound of money Dad deposits at a time */
#define WithdrawAmount       20         /* The amount of money Son withdraws at a time */
#define initBalance          0

FILE *fp1, *fp2, *fp3, *fp4;			/* File Pointers */

int main()
{
    int pid;						// Process ID after fork call
	int i;							// Loop index
	int N;							// Number of times dad does update
	int N_Att;						// Number of time sons allowed to do update
	int status;						// Exit status of child process
	int bal1, bal2;					// Balance read by processes
	int flag, flag1;				// End of loop variables
	srand(time(NULL));

    /**
     * creating three semaphores for the three processes:
     * each for dad, son_1 and son_2
     */

    int dad = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);
    int son_1 = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);
    int son_2 = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);

    // Initalizing the semaphores
    sem_create(dad,1);
    sem_create(son_1,1);
    sem_create(son_2, 1);

    // Initalizing the file to have $100
    fp1 = fopen("balance.txt", "w+");
    bal1 = initBalance;
    fprintf(fp1, "%d\n", bal1);
    fclose(fp1);

    //Initalize the number of withdraws
    fp4 = fopen("attempt.txt", "w+");
    N_Att = NumOfWithdrawAttempt;
    fprintf(fp4, "%d\n", N_Att);
    fclose(fp4);


    //Creating the child processes that will do the updates
	if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}

    if(pid == CHILD)
	{
        //First Child Process. Dad tries to do some updates.
	    printf("Dad's Pid: %d\n",getpid());
		N=NumOfDepositAttempt;

		for(i=1;i<=N; i++)
		{
			// DAD process
			P(son_1);
			P(son_2);
            //Dad is requesting to get hold of an ATM.
			printf("Dad is requesting to view the balance.\n");
            //Dad successfully got hold of the ATM.
			fp1 = fopen("balance.txt", "r+"); 
			fscanf(fp1, "%d", &bal2);
			printf("Dad reads balance = %d \n", bal2);
			int r = rand()%5+1;
			printf("Dad needs %d sec to prepare money\n", r); 		
            //Dad Process is sleeping for r sec. You need to make sure that other processes can work in the mean time.
			sleep(r);

			fseek(fp1,0L,0); //Dad will now deposit the money. For this Dad will access the ATM again. And update the current balance.
			bal2 += DepositAmount;
			fprintf(fp1, "%d \n", bal2);
			fclose(fp1);
			printf("Dad writes new balance = %d \n", bal2);
			printf("Dad will deposit %d more time\n",N-i); //Dad depostited the money. 
			sleep(rand()%10+1);	/* Dad will wait some time for requesting to see balance again.*/
			V(son_1);
			V(son_2);
		}
    }

    else
    {
        //Parent Process: Fork off another child process.
		if ((pid = fork()) == -1)
		{
			//Fork failed!
			perror("fork");
			exit(1);
		}

        if (pid == CHILD)
		{
			printf("First Son's Pid: %d\n",getpid());
			//Second child process. First poor son tries to do updates.
			flag = FALSE;
			while(flag == FALSE) 
			{
				printf("SON_1 is requesting to view the balance.\n"); //Son_1 is requesting to get hold of the ATM.
				fp3 = fopen("attempt.txt" , "r+"); //Son_1 successfully got hold of the ATM.
				fscanf(fp3, "%d", &N_Att); // Son_1 Checks if he has more than 0 attempt remaining.
				printf("Attempt remaining: %d.\n", N_Att);

				if(N_Att == 0)
				{
					fclose(fp3);
					flag = TRUE;
				}

				// SON_1 Process
                else
				{
					P(dad);
					P(son_2);
					fp2 = fopen("balance.txt", "r+");//Son_1 reads the balance. 
					fscanf(fp2,"%d", &bal2);
					printf("SON_1 reads balance. Available Balance: %d \n", bal2); 
					printf("SON_1 wants to withdraw money. "); //And if balance is greater than Withdraw amount, then son can withdraw money.
					fseek(fp2,0L, 0);

					if(bal2 >= WithdrawAmount)
						bal2 -= WithdrawAmount;

					else
						printf("Insufficient Funds\n");
						fprintf(fp2,"%d\n", bal2);
						fclose(fp2);
						printf("SON_1 withdrawed %d. New Balance: %d \n",WithdrawAmount, bal2);
						
					fseek(fp3,0L, 0); //SON_1 will write the number of  attempt remaining in the attampt.txt file.
					N_Att -=1;
					fprintf(fp3, "%d\n", N_Att);
					fclose(fp3);
					printf("Number of attempts remaining:%d \n", N_Att);
					V(dad);
					V(son_2);
				}

                sleep(rand()%10+1); //SON_1 will wait some time before the next request.
            }

        }

        else
		{
			
		//Parent Process. Fork off one more child process.
			if ((pid = fork()) == -1) 
			{
				//fork failed!
				perror("fork");
				exit(1);
			}

			if (pid == CHILD)
			{
				printf("Second Son's Pid: %d\n",getpid()); 
				//Third child process. Second poor son tries to do updates.
				flag1 = FALSE;
				while(flag1 == FALSE) 
				{
					printf("SON_2 is requesting to view the balance.\n"); //Son_2 is requesting to get hold of the ATM.
					fp3 = fopen("attempt.txt" , "r+"); //Son_2 successfully got hold of the ATM.
					fscanf(fp3, "%d", &N_Att); // Son_2 Checks if he has more than 0 attempt remaining.
					printf("Attempt remaining: %d.\n", N_Att);

					if(N_Att == 0)
					{
						fclose(fp3);
						flag1 = TRUE;
					}

					// SON_2 Process
					else
					{
						P(dad);
						P(son_1);
						//Son_2 reads the balance. 
						fp2 = fopen("balance.txt", "r+");
						fscanf(fp2,"%d", &bal2);
						printf("SON_2 reads balance. Available Balance: %d \n", bal2);
						//And if balance is greater than Withdraw amount, then son can withdraw money.
						printf("SON_2 wants to withdraw money. ");
						fseek(fp2,0L, 0);
						if(bal2 >= WithdrawAmount)
							bal2 -= WithdrawAmount;

						else
							printf("Insufficient Funds\n");
							fprintf(fp2,"%d\n", bal2);
							fclose(fp2);

						printf("SON_2 withdrawed %d. New Balance: %d \n",WithdrawAmount, bal2);
						fseek(fp3,0L, 0); //SON_2 will write the number of  attempt remaining in the attampt.txt file.
						N_Att -=1;
						fprintf(fp3, "%d\n", N_Att);
						fclose(fp3);
						printf("Number of attempts remaining: %d \n", N_Att);
						V(dad);
						V(son_1);
					}

					sleep(rand()%10+1);//SON_2 will wait some time before the next request.
				}
			}
			
			else
			{	
				//Now parent process waits for the child processes to finish
				
				pid = wait(&status);
              	printf("child(pid = %d) exited with the status %d. \n", pid, status);

              	pid = wait(&status);
              	printf("child(pid = %d) exited with the status %d. \n", pid, status);

              	pid = wait(&status);
              	printf("child(pid = %d) exited with the status %d. \n", pid, status);
			}
			exit(0);
		}
        exit(0);
    }
    exit(0);
}

    