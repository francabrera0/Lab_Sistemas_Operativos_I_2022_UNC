/*
* Author: Francisco Cabrera
* Date: 22/09/2022
* Description: clear command
*
*/

#include <stdio.h>
#include <string.h>
#include "../../include/commands/clr.h"

/*
* This function clear the workspace using ansi escape commands
* In case of an invalid option after the command, print a warning.
*
* @param command
*/
void clr(char* command){
	command = strtok(NULL,"");
	if(command==NULL){
		fprintf(stdout, "\33[2J");
		fprintf(stdout, "\33[1;1H");
	}
	else
		printf("Invalid usage of clr\n");
}