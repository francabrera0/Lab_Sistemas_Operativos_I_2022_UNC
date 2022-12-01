/*
* Author: Francisco Cabrera
* Date: 22/09/2022
* Description: This program file contains the functions to decode and execute an external program
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "../include/externprogram.h"

#define BACKGROUNDTASK 4

int flags[BACKGROUNDTASK] = {0,0,0,0};
int jobId = 0;
int jobIdBg[BACKGROUNDTASK] = {0,0,0,0};
pid_t pidInBg[BACKGROUNDTASK] = {0,0,0,0};
pid_t fgPid = 0;


/*
*
* Obtain the path and arguments that will be pased like arguments to execv function.
*
*/
static char** decod (char* program){
	char** parameters;
	parameters = (char**)malloc(sizeof(char*));

	int i=0;

	while(program!=NULL){

		if(i!=0){
			void* reallocate = (char**)realloc(parameters,sizeof(char*)*(i+1));
			if(NULL==reallocate)
				perror("Could not reallocate memory");
			else
				parameters = reallocate;
		}

		if(program!=NULL)
			parameters[i] = program;

		program = strtok(NULL," ");
		i++;
	}

	return parameters;
}

void chldHandler(){
	pid_t pid;
	for(int i=0; i<BACKGROUNDTASK; i++){
		if((pid = waitpid(-1,NULL,WNOHANG))==pidInBg[i] && pidInBg[i]!=0){
			flags[i] = 1;
			break;
		}
	}
}

void intHandler(){
	if (fgPid>0){
		printf("\n");
		kill(fgPid,SIGINT);
	}
}

void stopHandler(int sig){
    SIG_IGN;
    if(fgPid>0){
    	printf("   STOP [%d]\n",fgPid);
		kill(fgPid,SIGTSTP);
    }
}

void quitHandler(int sig){
    if(fgPid>0){
    	printf("\n");
		kill(fgPid,SIGQUIT);
    }
}


/*
* Execution of external programm. 
*
*
* BUG: -Multiple background process. Not notice of completion of process.
*	   -SIGTSTP handler
*/
void programInvocation(char* program, int back){
	
	struct sigaction sa;
	sa.sa_handler = stopHandler;
	sigaction(SIGTSTP,&sa,NULL);

	sa.sa_handler = intHandler;
	sigaction(SIGINT,&sa,NULL);

	sa.sa_handler = quitHandler;
	sigaction(SIGINT,&sa,NULL);

	signal(SIGCHLD,chldHandler);


	char** parameters;
	parameters = decod(program);

	int forkSuccess = fork();
	switch(forkSuccess){
		case -1: //error creating a child
			perror("Could not create child");
			break;
			
		case 0: //children task
			if(execl(program,parameters[0],parameters[1],parameters[2],(char*)NULL)==-1){
				char* usr = (char*)malloc(sizeof(char)*64);
				strcat(usr,"/usr/bin/");
				strcat(usr,program);

				if(execl(usr,parameters[0],parameters[1],parameters[2],(char*)NULL)==-1)
					perror("Program not found");
				free(usr);	
			}
			
			exit(0);
			break;

		default: //parent task
			if(!back){	
				waitpid(forkSuccess,0,0);
				fgPid = forkSuccess;
			}
			else{
				jobId++;

				printf("[%d] [%d] %s\n",jobId,forkSuccess,program);
				
				for(int i=0; i<BACKGROUNDTASK; i++){
					if(pidInBg[i]==0){
						pidInBg[i] = forkSuccess;
						jobIdBg[i] = jobId;
						break;
					}
				}
			}

			for(int i=0; i<BACKGROUNDTASK; i++){
				if(flags[i] == 1){
					printf("Done [%d] [%d]\n",jobIdBg[i], pidInBg[i]);
					flags[i] = 0;
					pidInBg[i] = 0;
				}
			}
			
			break;
	}

	signal(SIGTSTP,SIG_IGN);
	signal(SIGINT,SIG_IGN);
	free(parameters);
	
}
