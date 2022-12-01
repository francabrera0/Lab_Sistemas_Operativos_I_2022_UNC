/*
* Author: Francisco Cabrera
* Date: 22/09/2022
* Description: echo command
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/commands/echo.h"


/*
* This function prints the comment entered by the user.
* 	-In case the comment is equal to null, print a "\n"
* 	-If the first symbol of the comment is '$', search a enviroment variable 
* 	 whit this name and prints it (if its exists).
*
* @param: command + comment
*/
void echo(char* command){
	command = strtok(NULL," ");

	if(command==NULL){
		printf("\n");
		return;
	}
	else if(command[0]=='$'){
		for(int i=0; i<strlen(command); i++)
			command[i] = command[i+1];
		char* env = getenv(command);
		if(env!=NULL)
			printf("%s\n",env);
		else
			printf("\n");
		return;
	}
	else{
		while(command!=NULL){
			printf("%s ",command);
			command = strtok(NULL," ");
		}
		printf("\n");
	}
}