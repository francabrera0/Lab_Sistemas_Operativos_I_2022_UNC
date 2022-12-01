/*
* Author: Francisco Cabrera
* Date: 20/09/2022
* Description: This program file is responsible for making the correspondig
* function calls. Its only function is to be the launcher of the program.
*
*/
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "../include/commandline.h"
#include "../include/executecommands.h"

int main(int argc, char const *argv[])
{
	signal(SIGINT,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);

	if(argc>=2){
		FILE* file = fopen(argv[1],"r");
		if(file!=NULL){
			char* line = (char*)malloc(sizeof(char)*1024);

			while(fgets(line,1024,file)!=NULL){
				executeCommand(line);
			}
			fclose(file);
			free(line);
			exit(0);
		}
		else{
			perror("");
			exit(-1);
		}
	}
		

	init();


	
	while(1){
		char* command;
		command = getCommand();
		executeCommand(command);
		
	}
	return 0;
}