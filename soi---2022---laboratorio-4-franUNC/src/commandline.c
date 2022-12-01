/*
* Author: Francisco Cabrera
* Date: 20/09/2022
* Description: In this file, we can find the functions in charge of get commands from the user, 
*	print the prompt and print the correpondig out of the command entered.
*			In case of error, print an error message and print the prompt again.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../include/commandline.h"
#include "../include/colors.h"


char* userName;
char* hostName;
char* userDirectory;

static void getUserName(char** userName){
	*userName = getenv("USERNAME");
	if(*userName == NULL)
		*userName = "user";
}

static void getHostName(char** hostName){
	if(gethostname(*hostName,32))
		*hostName = "host";
}

static void welcomeMessage(void){
	printf("..................................\n");
	printf(".            Wolf Shell          .\n");
	printf(". By: Fran Cabrera               .\n");
	printf("..................................\n");

	FILE* file;
	file = fopen("./Logo/Logo.txt","r");
	
	if(!file){
		file = fopen("../Logo/Logo.txt","r");
		if(!file)
			return;
	}
	char c;
	while(!feof(file)){
		c = getc(file);
		printf("%c",c);
	}
	printf("\n");
	fclose(file);	
}


/*
* This function initializes the variables of interest for
* the correct execution of the program such as username,
* hostname and user directory. It also print a welcome message.
* For this, it makes use of the above functions.
*
*/
void init(void){
	welcomeMessage();

	userName = (char*)malloc(sizeof(char)*32);
	getUserName(&userName);
	hostName = (char*)malloc(sizeof(char)*32);
	getHostName(&hostName);

	userDirectory = malloc(sizeof(char)*64);
	strcpy(userDirectory,"/home/");
	strcat(userDirectory,userName);
}


static void prompt(void){
	printf(GREEN "%s@%s" WHITE ":" RESET_COLOR,userName,hostName);
	char* pwd;
	pwd = getenv("PWD");

	char* aux = strstr(pwd,userDirectory);

	if(aux != NULL){
		int size = strlen(userDirectory)-1;
		int i = 1;
		aux[0] = '~';
		while(aux[i]!='\0'){
			aux[i] = aux[size+i];
			i++;
		}
	}
	printf(BLUE "%s$ " RESET_COLOR,pwd);

}


/*
* This function print the prompt and reads the commands entered bby the user
*
*/
char* getCommand(void){
	prompt();
	char* command = (char*)malloc(sizeof(char)*64);
	if(fgets(command,64,stdin)==NULL)
        exit(EXIT_SUCCESS);
	return command;
}