#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/ioredirection.h"
#include "../include/executecommands.h"

static char* getProgram(char* command);
static char* filter(char* str, char* delim, char delim2);

int IORedirection(char* command){

	char* inputFile = filter(command,"<",'>');
	char* outputFile = filter(command,">",'<');
	char* program = getProgram(command);

	if(inputFile == NULL && outputFile == NULL){
		return 1;
	}


	pid_t pid;
	pid = fork();

	switch(pid){
		case -1:
			perror("Could not create child");
			break;

		case 0:

			if(inputFile != NULL){
				int fdIN = open(inputFile, O_RDONLY, 0777);
				if(fdIN == -1){
					perror("IORedirection fail");
				 	return -1;
				}

				dup2(fdIN, STDIN_FILENO);
				close(fdIN);
			}

			if(outputFile != NULL){
				int fdOut = open(outputFile, O_WRONLY | O_CREAT, 0777);
				if(fdOut == -1){
					perror("IORedirection fail");
				 	return -1;
				}

				dup2(fdOut, STDOUT_FILENO);
				close(fdOut);
			}

			executeCommand(program);
			exit(0);
			break;

		default:
			waitpid(pid,0,0);
			break;
	}


	free(inputFile);
	free(outputFile);
	free(program);
	return 0;
}

static char* getProgram(char* command){

	char* program = (char*)malloc(sizeof(char)*64);

	for(int i=0; command[i]!='<' && command[i]!='>' && command[i]!='\0'; i++)
		program[i] = command[i];

	return program;
}


static char* filter(char* str, char* delim, char delim2){
	
	char* fileName = (char*)malloc(sizeof(char)*64);

	int place = strcspn(str,delim);
	
	if(place==strlen(str)) 
		return NULL;

	for(int i = place+1; str[i]!=delim2 && str[i]!='\0'; i++)
		fileName[i-place-1] = str[i];

	return fileName;
}