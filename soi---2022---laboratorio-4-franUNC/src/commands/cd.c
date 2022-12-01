/*
* Author: Francisco Cabrera
* Date: 22/09/2022
* Description: cd command
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../include/commands/cd.h"

/*
* This function change the current directory to the entered by the user. It also update
* the values of the enviroment variables "PWD" and "OLDPWD".
* 
*	accepted abbreviations:
*   	".." --> target directory = OLDPWD
*		(null) --> target directory = /hom/username/
*
*@param: command + target directory
*
*/
void cd(char * directory){

	directory = strtok(NULL,"");

	if(directory == NULL)
		directory = getenv("HOME");	

	if(chdir(directory)==-1){
		perror("");
	}

	char* aux = malloc(sizeof(char)*1024);
	getcwd(aux,1024);
	setenv("OLDPWD",getenv("PWD"),1);
	setenv("PWD",aux,1);
	free(aux);
}